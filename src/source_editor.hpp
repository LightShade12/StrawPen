/***************************************************************************************************************************
 * source_editor.hpp
 * 06-04-2025
 * sorry. I am retarded.
 **************************************************************************************************************************/

#pragma once

#include "imgui.h"
#include "imgui_stdlib.h"
#include "spdlog/spdlog.h"
// ==========================

#include "source_file.hpp"
// ==========================

#include <filesystem>
#include <string>

namespace StrawPen
{

	class SourceEditor
	{
	public:
		explicit SourceEditor(std::filesystem::path file_path) : m_working_dir(file_path) {};

		// TODO: reload file
		void loadFile(std::filesystem::path filepath)
		{
			if (!filepath.has_filename())
			{
				spdlog::error("No file name in path");
				return;
			}
			const SourceFile& file_load = SourceFile::loadFromFile(filepath);
			if (m_loadedfiles.fileExists(file_load))
			{
				spdlog::info("File already loaded");
				return;
			}
			m_loadedfiles.add(file_load);
			m_current_file_index = m_loadedfiles.getSize() - 1;  // TODO: narrowing concersion
		}

		void createFile(std::filesystem::path filepath)
		{
			const SourceFile& newfile = SourceFile(filepath);
			// if (m_load_record.find(newfile) != m_load_record.end())
			// {
			// 	spdlog::info("File already exists");
			// 	return;
			// }
			m_loadedfiles.add(newfile);
			m_current_file_index = m_loadedfiles.getSize() - 1;  // TODO: narrowing concersion
		}

		void saveFile() { m_loadedfiles[m_current_file_index].first.writeToFile(); }

		void render()
		{
			ImGui::Begin("Source Editor");
			{
				if (ImGui::Button("Save"))
				{
					saveFile();
				}
				ImGui::SameLine();

				if (ImGui::Button("Reload"))
				{
					m_loadedfiles[m_current_file_index].first = SourceFile::loadFromFile(
					    m_loadedfiles[m_current_file_index].first.getFullPath());
				}
				ImGui::SameLine();

				if (ImGui::Button("Compile"))
				{
				}
				ImGui::SameLine();

				if (ImGui::Button("Execute"))
				{
				}
				ImGui::SameLine();

				ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x -
				                        ImGui::CalcTextSize(":File Name	").x);

				if (ImGui::InputTextWithHint(":File Name", "main.cxx", &m_filename_input_buff,
				                             ImGuiInputTextFlags_EnterReturnsTrue))
				{
					m_loadedfiles[m_current_file_index].first.setFileName(m_filename_input_buff);
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
							if (file.second &&
							    ImGui::BeginTabItem(file.first.getFileName().c_str(), &file.second))
							{
								m_filename_input_buff = file.first.getFileName();
								m_current_file_index = i;
								ImGui::Text("%s",
								            file.first.getFullPath().string().c_str());  // FILEPATH

								ImGui::InputTextMultiline("###srctextinput",
								                          file.first.getCharBufferPtr(),
								                          ImGui::GetContentRegionAvail());

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

			// spdlog::info("loaded files:{}", m_loadedfiles.getSize());
		}

	private:
		std::string m_filename_input_buff;
		int m_current_file_index = 0;

		LoadedFileRecord m_loadedfiles;

		std::filesystem::path m_working_dir;
	};  // SourceEditor

}  // namespace StrawPen
