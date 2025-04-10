/***************************************************************************************************************************
 * directory_explorer.hpp
 * 09-04-2025
 **************************************************************************************************************************/

#pragma once

#include "mediator_system.hpp"
// ======================

#include "imgui.h"
#include "imgui_stdlib.h"
#include "spdlog/spdlog.h"
// ======================

#include <filesystem>
#include <utility>
// ======================

namespace StrawPen
{

	class DirectoryExplorer : public Component
	{
	public:
		explicit DirectoryExplorer(Mediator* mediator, std::filesystem::path working_dir)
		    : m_working_dir(std::move(working_dir)), Component(mediator) {};

		~DirectoryExplorer() override = default;

		DirectoryExplorer(const DirectoryExplorer& other) = default;
		DirectoryExplorer(DirectoryExplorer&& other) = default;

		DirectoryExplorer& operator=(DirectoryExplorer&& other) = default;
		DirectoryExplorer& operator=(const DirectoryExplorer& other) = default;

		void render()
		{
			ImGui::Begin("Directory");
			{
				// dir ctx popup menu
				if (ImGui::BeginPopup("dir_ctx"))
				{
					if (ImGui::Button("Add file"))
					{
						m_mediator->notify(this, "create_file");
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				static std::pair<bool, std::filesystem::path> file_ctx_data =
				    std::make_pair(false, "");  // TODO: rename var; make it into member field
				file_ctx_data.first = false;

				static std::string rename_input;

				// file ctx popup menu
				if (ImGui::BeginPopup("file_ctx"))
				{
					if (ImGui::Button("rename file"))
					{
						rename_input = "";
						ImGui::OpenPopup("rename_dialog");
					};
					// rename dialog
					if (ImGui::BeginPopup("rename_dialog"))
					{
						ImGui::Text("Rename");
						if (ImGui::InputTextWithHint("###renamefield", "new name", &rename_input,
						                             ImGuiInputTextFlags_EnterReturnsTrue))
						{
							std::filesystem::path new_file =
							    file_ctx_data.second.parent_path().append(rename_input);
							spdlog::debug("renaming src: {} to {}",
							              file_ctx_data.second.string().c_str(),
							              new_file.string().c_str());
							try
							{
								std::filesystem::rename(file_ctx_data.second, new_file);
							}
							catch (const std::exception& e)
							{
								spdlog::error("EXCEPTION CAUGHT: {}", e.what());
							}
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndPopup();
					}

					if (ImGui::Button("delete file"))
					{
						if (std::filesystem::remove(file_ctx_data.second))
						{
							spdlog::debug("deleted file: {}",
							              file_ctx_data.second.string().c_str());
						}
						else
						{
							spdlog::debug("delete FAILED: {}",
							              file_ctx_data.second.string().c_str());
						}
						ImGui::CloseCurrentPopup();
					};
					ImGui::EndPopup();
				}

				// root cwd listing
				if (ImGui::TreeNode(m_working_dir.filename().string().c_str()))
				{
					ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

					// listing
					int idx = 0;
					for (const auto& entry : std::filesystem::directory_iterator(m_working_dir))
					{
						if (entry.is_directory())
						{
							recurseRenderDirectory(entry.path(), &file_ctx_data);
						}
						else
						{
							// file object
							ImGui::TreeNodeEx(
							    (void*)(intptr_t)idx,
							    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, "%s",
							    entry.path().filename().string().c_str());

							processFileClicks(entry.path(), &file_ctx_data);
						}
						idx++;
					}
					ImGui::TreePop();
					// end root listing
				}

				// popups launch ==============================

				if (file_ctx_data.first)
				{
					spdlog::debug("file ctx for {}", file_ctx_data.second.string().c_str());
					ImGui::OpenPopup("file_ctx");
				}
				else if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1))
				{
					ImGui::OpenPopup("dir_ctx");
				}
			}
			ImGui::End();
		}

		std::filesystem::path getWorkingDirectory() const { return m_working_dir; }
		std::filesystem::path getSelectedFilePath() const { return m_selected_filepath; }

	private:
		/// @brief NOTE : call directly after TreeNodeEx()
		/// @param filepath
		/// @param r_filectxrequest
		void processFileClicks(const std::filesystem::path& filepath,
		                       std::pair<bool, std::filesystem::path>* r_filectxrequest)
		{
			if (ImGui::IsItemHovered())
			{
				if (ImGui::IsMouseClicked(1))
				{
					r_filectxrequest->first = true;
					r_filectxrequest->second = filepath;
				}
			}

			if (ImGui::IsItemClicked())
			{
				if (ImGui::IsMouseDoubleClicked(0))
				{
					requestFileLoad(filepath);
				}
				else if (ImGui::IsMouseClicked(0))
				{
					// select file
					spdlog::debug("file selected {}", filepath.string().c_str());
				}
			}
		}

		void requestFileLoad(const std::filesystem::path& filepath)
		{
			m_selected_filepath = filepath;
			spdlog::debug("requesting file load {}", m_selected_filepath.string().c_str());
			m_mediator->notify(this, "load_file");
		}

		bool recurseRenderDirectory(const std::filesystem::path& dir_path,
		                            std::pair<bool, std::filesystem::path>* r_filectxrequest)
		{
			// dir folder
			if (ImGui::TreeNode(dir_path.filename().string().c_str()))
			{
				// listing
				int64_t i = 0;  // ignoring 32-bit systems
				for (const auto& entry : std::filesystem::directory_iterator(dir_path))
				{
					if (entry.is_directory())
					{
						recurseRenderDirectory(entry.path(), r_filectxrequest);
					}
					else
					{
						// file entry
						ImGui::TreeNodeEx(
						    reinterpret_cast<void*>(i),
						    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, "%s",
						    entry.path().filename().string().c_str());

						processFileClicks(entry.path(), r_filectxrequest);
					}
					i++;
				}
				// end dir listing
				ImGui::TreePop();
				return true;
			}
			return false;  // folder not opened
		}

		std::filesystem::path m_working_dir;
		std::filesystem::path m_selected_filepath;

	};  // DirectoryExplorer

}  // namespace StrawPen
