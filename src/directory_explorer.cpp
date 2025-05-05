/***************************************************************************************************************************
 * directory_explorer.cpp
 * 16-04-2025
 **************************************************************************************************************************/

#include "directory_explorer.hpp"
// ======================

#include "imgui.h"
#include "imgui_stdlib.h"
// ======================

#include <algorithm>
#include <cstdint>
// ======================

namespace
{
	std::string strToLower(const std::string& str)
	{
		std::string out = str;
		std::transform(out.begin(), out.end(), out.begin(),
		               [](unsigned char c) -> unsigned char { return std::tolower(c); });
		return out;
	}
}  // namespace

namespace StrawPen
{
	void DirectoryExplorer::render()
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
				if (ImGui::Button("Change directory"))
				{
					requestDirChange();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			static std::pair<bool, std::filesystem::path> file_ctx_data =
			    std::make_pair(false, "");  // TODO: rename var; make it into member field
			file_ctx_data.first = false;

			// file ctx popup menu
			if (ImGui::BeginPopup("file_ctx"))
			{
				if (ImGui::Button("rename file"))
				{
					m_rename_input_str = "";
					ImGui::OpenPopup("rename_dialog");
				};
				// rename dialog
				if (ImGui::BeginPopup("rename_dialog"))
				{
					ImGui::Text("Rename File");
					if (ImGui::InputTextWithHint("###renamefield", "new name", &m_rename_input_str,
					                             ImGuiInputTextFlags_EnterReturnsTrue))
					{
						requestFileRename(file_ctx_data.second);
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				if (ImGui::Button("delete file"))
				{
					requestFileDelete(file_ctx_data.second);
					ImGui::CloseCurrentPopup();
				};
				ImGui::EndPopup();
			}

			ImGui::Text("%s", m_working_dir.string().c_str());

			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x -
			                        ImGui::CalcTextSize("search").x - 5);
			ImGui::InputTextWithHint("search", "enter filename...", &m_search_string_buff);

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
						if (strToLower(entry.path().filename().string())
						        .find(strToLower(m_search_string_buff)) != std::string::npos)
						{
							// file object
							ImGui::TreeNodeEx(
							    reinterpret_cast<void*>(static_cast<intptr_t>(idx)),
							    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, "%s",
							    entry.path().filename().string().c_str());

							processFileClicks(entry.path(), &file_ctx_data);
						}
					}
					idx++;
				}
				ImGui::TreePop();
				// end root listing
			}

			// popups launchers ==============================

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

	void DirectoryExplorer::processFileClicks(
	    const std::filesystem::path& filepath,
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

	bool DirectoryExplorer::recurseRenderDirectory(
	    const std::filesystem::path& dir_path,
	    std::pair<bool, std::filesystem::path>* r_filectxrequest)
	{
		// dir folder
		if (ImGui::TreeNode(dir_path.filename().string().c_str()))
		{
			// listing
			int64_t i = 0;
			for (const auto& entry : std::filesystem::directory_iterator(dir_path))
			{
				if (entry.is_directory())
				{
					recurseRenderDirectory(entry.path(), r_filectxrequest);
				}
				else
				{
					if (entry.path().filename().string().find(m_search_string_buff) !=
					    std::string::npos)
					{
						// file entry
						ImGui::TreeNodeEx(
						    reinterpret_cast<void*>(i),
						    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, "%s",
						    entry.path().filename().string().c_str());

						processFileClicks(entry.path(), r_filectxrequest);
					}
				}
				i++;
			}
			// end dir listing
			ImGui::TreePop();
			return true;
		}
		return false;
	}

}  // namespace StrawPen