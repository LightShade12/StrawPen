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
#include <unordered_set>
#include <utility>
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

			in_file.seekg(0, std::ios::beg);

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

		void setFileName(const std::string& filename) { m_filename = filename; }

		std::string getFileName() const { return m_filename; }
		std::string* getFileNamePtr() { return &m_filename; }

		std::string getDirPath() const { return m_dir_path; }

		std::string* getCharBufferPtr() { return &m_source_char_buffer; }

	private:
		std::string m_filename = "unnamed";
		std::string m_dir_path = "./";
		std::string m_source_char_buffer;
	};  // SourceFile
}  // namespace StrawPen

namespace std
{
	template <>
	struct hash<StrawPen::SourceFile>
	{
		size_t operator()(const StrawPen::SourceFile& file) const
		{
			size_t h1 = std::hash<std::string> {}(file.getFileName());
			size_t h2 = std::hash<std::string> {}(file.getDirPath());
			return h1 ^ (h2 << 1);
		}
	};  // hash<StrawPen::SourceFile>

}  // namespace std

namespace StrawPen
{
	struct SourceFileHasher
	{
		size_t operator()(const SourceFile& file) const { return std::hash<SourceFile> {}(file); }
	};  // SourceFileHasher

	struct SourceFileEquality
	{
		bool operator()(const SourceFile& a, const SourceFile& b) const { return a == b; }
	};  // SourceFileEquality

	class LoadedFileRecord
	{
	public:
		LoadedFileRecord() = default;

	private:
		std::vector<std::pair<SourceFile, bool>> m_loadedfiles;
		std::unordered_set<SourceFile, SourceFileHasher, SourceFileEquality> m_load_record;
	};

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
			if (m_load_record.find(file_load) != m_load_record.end())
			{
				spdlog::info("File already loaded");
				return;
			}
			addFileToLoaded(file_load);
			m_current_file_index = m_loadedfiles.size() - 1;  // TODO: narrowing concersion
		}

		void createFile(std::filesystem::path filepath)
		{
			const SourceFile& newfile = SourceFile(filepath);
			// if (m_load_record.find(newfile) != m_load_record.end())
			// {
			// 	spdlog::info("File already exists");
			// 	return;
			// }
			addFileToLoaded(newfile);
			m_current_file_index = m_loadedfiles.size() - 1;  // TODO: narrowing concersion
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
						for (int i = 0; i < m_loadedfiles.size(); i++)
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
								m_load_record.erase(file.first);
								m_loadedfiles.erase(m_loadedfiles.begin() + i);
							}
						}
						ImGui::EndTabBar();
					}
				}
				ImGui::EndChild();
			}
			ImGui::End();
			spdlog::info("loaded files:{}", m_load_record.size());
		}

	private:
		void addFileToLoaded(const SourceFile& file)
		{
			m_loadedfiles.emplace_back(file, true);
			m_load_record.emplace(file);
		}

		std::string m_filename_input_buff;
		int m_current_file_index = 0;

		std::vector<std::pair<SourceFile, bool>> m_loadedfiles;
		std::unordered_set<SourceFile, SourceFileHasher, SourceFileEquality> m_load_record;

		std::filesystem::path m_working_dir;
	};  // SourceEditor

}  // namespace StrawPen
