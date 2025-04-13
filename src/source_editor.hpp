/***************************************************************************************************************************
 * source_editor.hpp
 * 06-04-2025
 * sorry. I am retarded.
 **************************************************************************************************************************/

#pragma once

#include "imgui_stdlib.h"
#include "spdlog/spdlog.h"
// ==========================

#include "mediator_system.hpp"
#include "source_file.hpp"
// ==========================

#include <algorithm>
#include <filesystem>
#include <string>
#include <utility>

namespace StrawPen
{

	class SourceEditor : public Component
	{
	public:
		explicit SourceEditor(Mediator* mediator, std::filesystem::path file_path)
		    : Component(mediator), m_working_dir(std::move(file_path)) {};

		void loadFile(const std::filesystem::path& filepath)
		{
			if (!filepath.has_filename())
			{
				throw std::runtime_error("no filename in path");
			}
			if (m_loadedfiles.IsFileLoaded(filepath))
			{
				spdlog::debug("File already loaded");
				return;
			}
			const ASCIITextFile& file_load = ASCIITextFile::loadFromDisk(filepath);
			m_loadedfiles.add(file_load);
			m_current_file_index = static_cast<int>(m_loadedfiles.getSize() - 1);
		}

		void createFile(const std::filesystem::path& filepath)
		{
			const ASCIITextFile& newfile = ASCIITextFile(filepath);

			m_loadedfiles.add(newfile);
			m_current_file_index = static_cast<int>(m_loadedfiles.getSize() - 1);
		}

		void deleteFile(const std::filesystem::path& filepath)
		{
			const int idx = m_loadedfiles.findFileIdx(filepath);
			const bool is_delete_target_loaded = idx >= 0;
			if (is_delete_target_loaded)
			{
				m_loadedfiles[idx].first.deleteFromDisk();
				m_loadedfiles.erase(idx);  // should we unload the file?
			}
			else
			{
				if (!std::filesystem::remove(filepath))
				{
					throw std::runtime_error("[DEL] File deletion failed");
				}
			}
		}

		void renameFile(const std::filesystem::path& filepath, const std::string& new_name)
		{
			const int idx = m_loadedfiles.findFileIdx(filepath);
			const bool is_rename_target_loaded = idx >= 0;  // is target in memory as well

			if (is_rename_target_loaded)
			{
				// disk and memory item rename
				m_loadedfiles.renameFile(idx, new_name);
			}
			else
			{
				// manual disk item rename
				auto newpath = filepath.parent_path();
				std::filesystem::rename(filepath, newpath.append(new_name));
				spdlog::debug("renamed NON-LOADED file: {} to {}", filepath.string().c_str(),
				              newpath.string().c_str());
			}
		}

		void saveFile() { m_loadedfiles[m_current_file_index].first.writeToDisk(); }

		void render()
		{
			ImGui::Begin("Source Editor");
			{
				ImGui::Text("DBG: ld fls: %zu| cfi: %d", m_loadedfiles.getSize(),
				            m_current_file_index);
				if (ImGui::Button("Save"))
				{
					saveFile();
				}
				ImGui::SameLine();

				if (ImGui::Button("Reload"))
				{
					m_loadedfiles[m_current_file_index].first = ASCIITextFile::loadFromDisk(
					    m_loadedfiles[m_current_file_index].first.constructFilePath());
				}
				ImGui::SameLine();

				if (ImGui::Button("Compile"))
				{
				}
				ImGui::SameLine();

				if (ImGui::Button("Execute"))
				{
					m_mediator->notify(this, "execute_test");
				}
				ImGui::SameLine();

				{
					ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x -
					                        ImGui::CalcTextSize(":File Name	").x);

					const bool is_load_buf_empty = m_loadedfiles.getSize() <= 0;
					if (is_load_buf_empty)
					{
						m_filename_input_buff = "";
						ImGui::BeginDisabled();
					}
					if (ImGui::InputTextWithHint(":File Name", "main.cxx...",
					                             &m_filename_input_buff,
					                             ImGuiInputTextFlags_EnterReturnsTrue))
					{
						m_loadedfiles.renameFile(m_current_file_index, m_filename_input_buff);
					}
					if (is_load_buf_empty)
					{
						ImGui::SetItemTooltip("create/open a file to rename");
						ImGui::EndDisabled();
					}
				}

				// =================================================================

				ImGui::BeginChild("filetabsys");
				{
					if (ImGui::BeginTabBar("filetabs", ImGuiTabBarFlags_None))
					{
						for (int i = 0; i < m_loadedfiles.getSize(); i++)
						{
							ImGui::PushID(i);
							auto& file = m_loadedfiles[i];

							const ImGuiTabItemFlags tab_flags =
							    (file.first.isUnsaved() || !file.first.existsOnDisk()) ?
							        ImGuiTabItemFlags_UnsavedDocument :
							        0;
							// tab_flags |=
							//     (i == m_current_file_index) ? ImGuiTabItemFlags_SetSelected : 0;

							if (file.second && ImGui::BeginTabItem(file.first.getFileName().c_str(),
							                                       &file.second, tab_flags))
							{
								m_filename_input_buff = file.first.getFileName();
								m_current_file_index = i;
								ImGui::Text(
								    "%s",
								    file.first.constructFilePath().string().c_str());  // FILEPATH

								if (ImGui::InputTextMultiline("###srctextinput",
								                              file.first.getCharBufferPtr(),
								                              ImGui::GetContentRegionAvail()))
								{
									file.first.setIsUnsaved(true);
								}

								// spdlog::debug("scroll {}", ImGui::GetScrollY());

								ImGui::EndTabItem();
							}
							ImGui::PopID();
							if (!file.second)
							{
								m_loadedfiles.erase(i);
							}
						}
						ImGui::EndTabBar();
					}
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}

	private:
		std::string m_filename_input_buff;
		int32_t m_current_file_index = 0;

		LoadedFileRecord m_loadedfiles;

		std::filesystem::path m_working_dir;
	};  // SourceEditor

}  // namespace StrawPen
