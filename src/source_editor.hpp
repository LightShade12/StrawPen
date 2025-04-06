/***************************************************************************************************************************
 * source_editor.hpp
 **************************************************************************************************************************/
#pragma once

#include "imgui_stdlib.h"
#include "spdlog/spdlog.h"

// ======================
#include <filesystem>
#include <fstream>

namespace StrawPen
{

	class SourceEditor
	{
	public:
		explicit SourceEditor(const char* file_path) : m_dir_path(file_path) {};

		void loadFile(const char* file_path)
		{
			m_dir_path = file_path;
			std::ifstream in_file(file_path, std::ios::binary | std::ios::ate);
			auto len = in_file.tellg();
			if (!in_file)
			{
				throw std::runtime_error("file load error");
			}
			m_source_file_char_buff.resize(len);
			in_file.read(m_source_file_char_buff.data(), len);
			if (in_file.fail())
			{
				throw std::runtime_error("file reading error");
			}
		}

		void writeToFile(const char* file_path)
		{
			std::ofstream out_file(file_path, std::ios::binary);
			if (!out_file)
			{  // You can also use out_file.is_open() or check outFile.fail()
				throw std::runtime_error("file create error");
			}
			out_file.write(m_source_file_char_buff.data(), m_source_file_char_buff.size());
			if (out_file.fail())
			{
				throw std::runtime_error("file writing error");
			}
		}

		std::string getFullPath()
		{
			std::filesystem::path fullfilepath(m_dir_path);
			fullfilepath.append(m_file_name);
			return fullfilepath.string();
		}

		void render()
		{
			ImGui::Begin("Source Editor");
			{
				static bool is_f1open = true;

				if (ImGui::Button("Save"))
				{
					if (m_file_name.empty() || m_dir_path.empty())
					{
						spdlog::error("[SAVE] invalid path");
					}
					else
					{
						writeToFile(getFullPath().c_str());
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

				ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8);
				ImGui::InputTextWithHint(":File Name", "main.cxx", &m_file_name);

				// ================
				ImGui::BeginChild("filetabsys");
				{
					if (ImGui::BeginTabBar("filetabs", ImGuiTabBarFlags_None))
					{
						if (ImGui::BeginTabItem(m_file_name.c_str(), &is_f1open))
						{
							ImGui::Text("%s", getFullPath().c_str());  // FILEPATH

							ImGui::InputTextMultiline("###srctextinput", &(m_source_file_char_buff),
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
		std::string m_source_file_char_buff;
		std::string m_dir_path = "./";
		std::string m_file_name = "unnamed";
	};  // SourceEditor

}  // namespace StrawPen