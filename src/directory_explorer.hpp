/***************************************************************************************************************************
 * directory_explorer.hpp
 **************************************************************************************************************************/
#pragma once

#include "imgui.h"
#include "spdlog/spdlog.h"

// ======================
#include <filesystem>

namespace StrawPen
{

	class DirectoryExplorer
	{
	public:
		explicit DirectoryExplorer(std::filesystem::path working_dir) : m_working_dir(working_dir)
		{
			refreshDir();
		};

		void refreshDir()
		{
			int curr_lv_dir_items = 0;
			for (const auto& entry : std::filesystem::directory_iterator(m_working_dir))
			{
				curr_lv_dir_items++;
			}
			m_root_dir_items = curr_lv_dir_items;
		}

		void requestFileLoad(const std::filesystem::path& filepath)
		{
			spdlog::info("requesting file load {}", filepath.string().c_str());
		}

		bool recurseRenderDirectory(const std::filesystem::path& dir_path)
		{
			// dir folder
			if (ImGui::TreeNode(dir_path.filename().string().c_str()))
			{
				// listing
				int i = 0;
				for (const auto& entry : std::filesystem::directory_iterator(dir_path))
				{
					if (entry.is_directory())
					{
						recurseRenderDirectory(entry.path());
					}
					else
					{
						// file object
						ImGui::TreeNodeEx(
						    (void*)(intptr_t)i,
						    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, "%s",
						    entry.path().filename().string().c_str());
						if (ImGui::IsItemClicked() && ImGui::IsMouseDoubleClicked(0))
						{
							// spdlog::info("rcrs clicked {}", entry.path().string().c_str());
							requestFileLoad(entry.path());
						}
					}
					i++;
				}
				// end dir listing
				ImGui::TreePop();
				return true;
			}
			return false;  // folder not opened
		}

		void render()
		{
			ImGui::Begin("Directory");
			{
				// root
				if (ImGui::TreeNode(m_working_dir.filename().string().c_str()))
				{
					ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

					// listing
					int idx = 0;
					for (const auto& entry : std::filesystem::directory_iterator(m_working_dir))
					{
						if (entry.is_directory())
						{
							recurseRenderDirectory(entry.path());
						}
						else
						{
							// file object
							ImGui::TreeNodeEx(
							    (void*)(intptr_t)idx,
							    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, "%s",
							    entry.path().filename().string().c_str());
							if (ImGui::IsItemClicked() && ImGui::IsMouseDoubleClicked(0))
							{
								// spdlog::info("clicked {}", entry.path().string().c_str());
								requestFileLoad(entry.path());
							}
						}
						idx++;
					}
					// end root listing
					ImGui::TreePop();
				}
			}
			ImGui::End();
		}

		std::filesystem::path getCurrentDirectory() const { return m_working_dir; }

	private:
		std::filesystem::path m_working_dir;
		int32_t m_root_dir_items = 0;

	};  // DirectoryExplorer

}  // namespace StrawPen
