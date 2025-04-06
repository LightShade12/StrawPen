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
	};

	class SourceEditor
	{
	public:
		explicit SourceEditor(std::filesystem::path file_path)
		    : m_current_file(file_path.append("unnamed")) {};

		void loadFile(const std::filesystem::path& file_path)
		{
			m_current_file = SourceFile(file_path);
			std::ifstream in_file(file_path, std::ios::binary | std::ios::ate);
			auto source_char_len = in_file.tellg();
			if (!in_file)
			{
				throw std::runtime_error("file load error");
			}
			m_current_file.getCharBufferPtr()->resize(source_char_len);
			in_file.read(m_current_file.getCharBufferPtr()->data(), source_char_len);
			if (in_file.fail())
			{
				throw std::runtime_error("file reading error");
			}
		}

		void writeToFile(const std::filesystem::path& file_path)
		{
			std::ofstream out_file(file_path, std::ios::binary);
			if (!out_file)
			{  // You can also use out_file.is_open() or check outFile.fail()
				throw std::runtime_error("file create error");
			}
			out_file.write(m_current_file.getCharBufferPtr()->data(),
			               static_cast<int64_t>(m_current_file.getCharBufferPtr()->size()));
			if (out_file.fail())
			{
				throw std::runtime_error("file writing error");
			}
		}

		void render()
		{
			ImGui::Begin("Source Editor");
			{
				static bool is_f1open = true;

				if (ImGui::Button("Save"))
				{
					if (m_current_file.getFileName().empty() || m_current_file.getDirPath().empty())
					{
						spdlog::error("[SAVE] invalid path");
					}
					else
					{
						writeToFile(m_current_file.getFullPath());
					}
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
				ImGui::InputTextWithHint(":File Name", "main.cxx", m_current_file.getFileNamePtr());

				// ================
				ImGui::BeginChild("filetabsys");
				{
					if (ImGui::BeginTabBar("filetabs", ImGuiTabBarFlags_None))
					{
						if (ImGui::BeginTabItem(m_current_file.getFileName().c_str(), &is_f1open))
						{
							ImGui::Text("%s",
							            m_current_file.getFullPath().string().c_str());  // FILEPATH

							ImGui::InputTextMultiline("###srctextinput",
							                          m_current_file.getCharBufferPtr(),
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
		SourceFile m_current_file;
	};  // SourceEditor

}  // namespace StrawPen