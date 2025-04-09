/***************************************************************************************************************************
 * source_file.hpp
 * 09-04-2025
 ****************************************************************************************************************************/

#pragma once

#include "spdlog/spdlog.h"
//=========================

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
//========================

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
			{  // can also use out_file.is_open() or check out_file.fail()
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
			size_t hsh1 = std::hash<std::string> {}(file.getFileName());
			size_t hsh2 = std::hash<std::string> {}(file.getDirPath());
			return hsh1 ^ (hsh2 << 1);
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
		bool operator()(const SourceFile& first, const SourceFile& second) const
		{
			return first == second;
		}
	};  // SourceFileEquality

	class LoadedFileRecord
	{
	public:
		LoadedFileRecord() = default;

		std::pair<SourceFile, bool> operator[](int idx) const { return m_loadedfiles[idx]; }
		std::pair<SourceFile, bool>& operator[](int idx) { return m_loadedfiles[idx]; }

		void add(const SourceFile& file)
		{
			if (fileExists(file))
			{
				return;
			}
			m_loadedfiles.emplace_back(file, true);
			m_load_record.emplace(file);
		}

		void erase(int idx)
		{
			const std::pair<SourceFile, bool> loadedfile = *(m_loadedfiles.begin() + idx);
			if (!fileExists(loadedfile.first))
			{
				throw std::runtime_error("erasing nonexistent element");
				return;
			}
			m_load_record.erase(loadedfile.first);
			m_loadedfiles.erase(m_loadedfiles.begin() + idx);
		}

		bool fileExists(const SourceFile& file)
		{
			return (m_load_record.find(file) != m_load_record.end());
		}

		size_t getSize()
		{
			if (m_load_record.size() != m_loadedfiles.size())
			{
				throw std::runtime_error("desynchronized file containers");
			}
			return m_load_record.size();
		}

	private:
		// TODO: make elements as pointers to map elements
		std::vector<std::pair<SourceFile, bool>> m_loadedfiles;
		std::unordered_set<SourceFile, SourceFileHasher, SourceFileEquality> m_load_record;
	};  // LoadedFileRecord

}  // namespace StrawPen
