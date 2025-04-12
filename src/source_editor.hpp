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

namespace StrawPen
{

	class SourceEditor : public Component
	{
	public:
		explicit SourceEditor(Mediator* mediator, const std::filesystem::path& file_path)
		    : Component(mediator), m_working_dir(file_path) {};

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
			m_current_file_index = m_loadedfiles.getSize() - 1;  // TODO: narrowing concersion
		}

		void createFile(const std::filesystem::path& filepath)
		{
			const ASCIITextFile& newfile = ASCIITextFile(filepath);

			m_loadedfiles.add(newfile);
			m_current_file_index = m_loadedfiles.getSize() - 1;  // TODO: narrowing concersion
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
				static float scrolly = 0;
				ImGui::Text("DBG: ld fls: %zu| cfi: %d| scrly: %.3f", m_loadedfiles.getSize(),
				            m_current_file_index, scrolly);
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

					bool is_load_buf_empty = m_loadedfiles.getSize() <= 0;
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

							ImGuiTabItemFlags tab_flags =
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
								ImGui::SetNextWindowScroll(ImVec2(0, scrolly * -10));
								ImGui::BeginChild("lnx", ImVec2(30, 0), ImGuiChildFlags_None,
								                  ImGuiWindowFlags_NoScrollbar);
								{
									int cnt =
									    std::count(file.first.getCharBufferPtr()->begin(),
									               file.first.getCharBufferPtr()->end(), '\n');
									float cposy = ImGui::GetCursorPosY();
									cposy += 2;
									ImGui::SetCursorPosY(cposy);
									for (int i = 0; i < cnt + 3; i++)
									{
										ImGui::Text(" %d", i);
										cposy = ImGui::GetCursorPosY();
										cposy -= 4;
										ImGui::SetCursorPosY(cposy);
									}
								}
								ImGui::EndChild();
								ImGui::SameLine();
								ImGui::BeginChild("TextArea");
								{
									if (ImGui::InputTextMultiline("###srctextinput",
									                              file.first.getCharBufferPtr(),
									                              ImGui::GetContentRegionAvail()))
									{
										file.first.setIsUnsaved(true);
									}

									// scrolly = 0;
									if (ImGui::IsItemHovered())
									{
										scrolly += ImGui::GetIO().MouseWheel;
									}

									// spdlog::debug("scroll {}", ImGui::GetScrollY());
								}
								ImGui::EndChild();

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
		int m_current_file_index = 0;

		LoadedFileRecord m_loadedfiles;

		std::filesystem::path m_working_dir;
	};  // SourceEditor

}  // namespace StrawPen
