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

#include <filesystem>
#include <string>

namespace StrawPen
{

	class SourceEditor : public Component
	{
	public:
		explicit SourceEditor(Mediator* mediator, std::filesystem::path file_path)
		    : Component(mediator), m_working_dir(file_path) {};

		void loadFile(std::filesystem::path filepath)
		{
			if (!filepath.has_filename())
			{
				spdlog::error("No file name in path");
				return;
			}
			const ASCIITextFile& file_load = ASCIITextFile::loadFromDisk(filepath);
			if (m_loadedfiles.fileExists(file_load))
			{
				spdlog::debug("File already loaded");
				return;
			}
			m_loadedfiles.add(file_load);
			m_current_file_index = m_loadedfiles.getSize() - 1;  // TODO: narrowing concersion
		}

		void createFile(std::filesystem::path filepath)
		{
			const ASCIITextFile& newfile = ASCIITextFile(filepath);
			// if (m_load_record.find(newfile) != m_load_record.end())
			// {
			// 	spdlog::info("File already exists");
			// 	return;
			// }
			m_loadedfiles.add(newfile);
			m_current_file_index = m_loadedfiles.getSize() - 1;  // TODO: narrowing concersion
		}

		void deleteFile(std::filesystem::path filepath) {}

		void renameFile(const std::filesystem::path& filepath, const std::string& new_name)
		{
			const int idx = m_loadedfiles.findFileIdx(filepath);
			const bool rename_target_loaded = idx >= 0;
			if (rename_target_loaded)
			{
				m_loadedfiles.renameFile(idx, new_name);
			}
			else
			{
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

				ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x -
				                        ImGui::CalcTextSize(":File Name	").x);

				if (ImGui::InputTextWithHint(":File Name", "main.cxx", &m_filename_input_buff,
				                             ImGuiInputTextFlags_EnterReturnsTrue))
				{
					// m_loadedfiles[m_current_file_index].first.rename(m_filename_input_buff);
					m_loadedfiles.renameFile(m_current_file_index, m_filename_input_buff);
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
							    ImGui::BeginTabItem(
							        file.first.getFileName().c_str(), &file.second,
							        (file.first.isUnsaved() || !file.first.existsOnDisk()) ?
							            ImGuiTabItemFlags_UnsavedDocument :
							            0))
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

			// spdlog::debug("loaded files:{}", m_loadedfiles.getSize());
		}

	private:
		std::string m_filename_input_buff;
		int m_current_file_index = 0;

		LoadedFileRecord m_loadedfiles;

		std::filesystem::path m_working_dir;
	};  // SourceEditor

}  // namespace StrawPen
