/***************************************************************************************************************************
 * source_editor.hpp
 * 06-04-2025
 * sorry. I am retarded.
 **************************************************************************************************************************/
#pragma once

#include "imgui.h"
#include "imgui_stdlib.h"
#include "spdlog/spdlog.h"
// ======================
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace StrawPen
{

	class SourceFile
	{
	public:
		explicit SourceFile(const std::filesystem::path& filepath)
		    : m_filename(filepath.filename().string()),
		      m_dir_path(filepath.parent_path().string()) {};

		bool operator==(const SourceFile& other) const
		{
			return m_filename == other.m_filename && m_dir_path == other.m_dir_path;
		}

		void writeToFile()
		{
			if (m_filename.empty() || m_dir_path.empty())
			{
				spdlog::error("{}:{}:[WRITE] invalid path", __FILE__, __LINE__);
				return;
			}

			std::ofstream out_file(getFullPath(), std::ios::binary);
			if (!out_file)
			{  // You can also use out_file.is_open() or check out_file.fail()
				throw std::runtime_error("file create error");
			}
			out_file.write(m_source_char_buffer.data(),
			               static_cast<int64_t>(m_source_char_buffer.size()));
			if (out_file.fail())
			{
				throw std::runtime_error("file writing error");
			}
		}

		static SourceFile loadFromFile(const std::filesystem::path& file_path)
		{
			SourceFile src_file(file_path);
			std::ifstream in_file(file_path, std::ios::binary | std::ios::ate);
			if (!in_file)
			{
				throw std::runtime_error("file load error");
			}
			const size_t source_char_len = in_file.tellg();
			src_file.m_source_char_buffer.resize(source_char_len);
			in_file.read(src_file.m_source_char_buffer.data(),
			             source_char_len);  // TODO: fix narrowing conversion

			if (in_file.fail())
			{
				throw std::runtime_error("file reading error");
			}

			return src_file;
		}

		std::filesystem::path getFullPath() const
		{
			std::filesystem::path fullfilepath(m_dir_path);
			fullfilepath.append(m_filename);
			return fullfilepath;
		}

		std::string getFileName() const { return m_filename; }
		std::string* getFileNamePtr() { return &m_filename; }

		std::string getDirPath() const { return m_dir_path; }

		std::string* getCharBufferPtr() { return &m_source_char_buffer; }

	private:
		std::string m_filename = "unnamed";
		std::string m_dir_path = "./";
		std::string m_source_char_buffer;
	};  // SourceFile

	class SourceEditor
	{
	public:
		explicit SourceEditor(std::filesystem::path file_path) : m_working_dir(file_path)
		{
			m_loadedfiles.emplace_back(file_path.append("unnamed"));
			m_current_file_index = 0;
		};

		void saveFile() { m_loadedfiles[m_current_file_index].writeToFile(); }

		void render()
		{
			ImGui::Begin("Source Editor");
			{
				static bool is_f1open = true;

				if (ImGui::Button("Save"))
				{
					m_loadedfiles[m_current_file_index].writeToFile();
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
				ImGui::InputTextWithHint(":File Name", "main.cxx",
				                         m_loadedfiles[m_current_file_index].getFileNamePtr());

				// ================
				ImGui::BeginChild("filetabsys");
				{
					if (ImGui::BeginTabBar("filetabs", ImGuiTabBarFlags_None))
					{
						if (ImGui::BeginTabItem(
						        m_loadedfiles[m_current_file_index].getFileName().c_str(),
						        &is_f1open))
						{
							ImGui::Text("%s",
							            m_loadedfiles[m_current_file_index]
							                .getFullPath()
							                .string()
							                .c_str());  // FILEPATH

							ImGui::InputTextMultiline(
							    "###srctextinput",
							    m_loadedfiles[m_current_file_index].getCharBufferPtr(),
							    ImGui::GetContentRegionAvail());

							ImGui::EndTabItem();
						}
						ImGui::EndTabBar();
					}
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}

	private:
		int m_current_file_index = 0;
		std::vector<SourceFile> m_loadedfiles;
		std::filesystem::path m_working_dir;
	};  // SourceEditor

}  // namespace StrawPen