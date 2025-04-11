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
#include <numbers>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

//========================

namespace StrawPen
{

	/***
	 * @brief An object associating text content with a filepath
	 */
	class ASCIITextFile
	{
	public:
		explicit ASCIITextFile(const std::filesystem::path& filepath)
		    : m_filename(filepath.filename().string()),
		      m_dir_path(filepath.parent_path().string()) {};

		/// @brief Instantiate from existing filepath
		/// @param file_path
		/// @return loaded SourceFile
		static ASCIITextFile loadFromDisk(const std::filesystem::path& file_path)
		{
			ASCIITextFile loaded_file(file_path);
			std::ifstream in_file_strm;
			in_file_strm.open(file_path, std::ios::binary | std::ios::ate | std::ios::in);
			if (!in_file_strm.is_open())
			{
				throw std::runtime_error("file open error");
			}
			const size_t source_char_len = in_file_strm.tellg();
			in_file_strm.seekg(0, std::ios::beg);

			if (const size_t max_size = std::numeric_limits<std::streamsize>::max();
			    source_char_len > max_size)
			{
				throw new std::runtime_error("file content too long for reading");
			}

			loaded_file.m_source_string.resize(source_char_len);
			in_file_strm.read(loaded_file.m_source_string.data(),
			                  static_cast<std::streamsize>(source_char_len));

			if (in_file_strm.fail())
			{
				throw std::runtime_error("file reading error");
			}

			return loaded_file;
		}

		bool operator==(const ASCIITextFile& other) const
		{
			return m_filename == other.m_filename && m_dir_path == other.m_dir_path;
		}

		void writeToDisk()
		{
			if (m_filename.empty() || m_dir_path.empty())
			{
				spdlog::error("{}:{}:[WRITE] empty path", __FILE__, __LINE__);
				throw std::runtime_error("empty path");
			}
			std::ofstream out_file;
			out_file.open(constructFilePath(), std::ios::binary | std::ios::out);  // create
			if (!out_file.is_open())
			{  // can also check out_file.fail()
				throw std::runtime_error("file open/create error");
			}
			out_file.write(m_source_string.data(), static_cast<int64_t>(m_source_string.size()));
			if (out_file.fail())
			{
				throw std::runtime_error("file writing error");
			}
			setIsUnsaved(false);
		}

		void rename(const std::string& new_filename)
		{
			if (existsOnDisk())
			{
				auto old_filepath = constructFilePath();
				std::filesystem::path new_filepath = m_dir_path;
				new_filepath.append(new_filename);

				spdlog::debug("renaming src: {} to {}", old_filepath.string().c_str(),
				              new_filepath.string().c_str());

				std::filesystem::rename(old_filepath, new_filepath);
			}
			m_filename = new_filename;
		}

		bool existsOnDisk() const { return std::filesystem::is_regular_file(constructFilePath()); }
		// ===================================================================

		std::filesystem::path constructFilePath() const
		{
			std::filesystem::path fullfilepath(m_dir_path);
			fullfilepath.append(m_filename);
			return fullfilepath;
		}

		std::string* getFileNamePtr() { return &m_filename; }
		std::string getFileName() const { return m_filename; }
		void setFileName(const std::string& filename) { m_filename = filename; }

		std::string getDirPath() const { return m_dir_path; }
		void setDirPath(const std::string& path) { m_dir_path = path; }

		std::string* getCharBufferPtr() { return &m_source_string; }
		std::string getCharContent() const { return m_source_string; }
		void setCharContent(const std::string& data) { m_source_string = data; }

		void setIsUnsaved(bool is_unsaved) { m_unsaved = is_unsaved; }
		bool isUnsaved() const { return m_unsaved; }

	private:
		bool m_unsaved = false;
		std::string m_filename = "unnamed";
		std::string m_dir_path = "./";
		std::string m_source_string;
	};  // TextFile
}  // namespace StrawPen

namespace std
{
	template <>
	struct hash<StrawPen::ASCIITextFile>
	{
		size_t operator()(const StrawPen::ASCIITextFile& file) const
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
		size_t operator()(const ASCIITextFile& file) const
		{
			return std::hash<ASCIITextFile> {}(file);
		}
	};  // SourceFileHasher

	struct SourceFileEquality
	{
		bool operator()(const ASCIITextFile& first, const ASCIITextFile& second) const
		{
			return first == second;
		}
	};  // SourceFileEquality

	class LoadedFileRecord
	{
	public:
		LoadedFileRecord() = default;

		std::pair<ASCIITextFile, bool> operator[](int idx) const { return m_loadedfiles[idx]; }
		std::pair<ASCIITextFile, bool>& operator[](int idx) { return m_loadedfiles[idx]; }

		void add(const ASCIITextFile& file)
		{
			if (fileExists(file))
			{
				return;
			}
			m_loadedfiles.emplace_back(file, true);
			m_load_record.emplace(file);
		}

		void renameFile(int32_t idx, const std::string& new_filename)
		{
			ASCIITextFile& file = m_loadedfiles[idx].first;
			m_load_record.erase(file);

			file.rename(new_filename);
			m_load_record.emplace(file);
		}

		void renameFile(const std::filesystem::path& filepath, const std::string& new_filename)
		{
			int idx = findFileIdx(filepath);
			if (idx < 0)
			{
				spdlog::warn("rename target file not found in MEMORY");
				return;
			}
			ASCIITextFile& file = m_loadedfiles[idx].first;
			m_load_record.erase(file);

			file.rename(new_filename);
			m_load_record.emplace(file);
		}

		void erase(int idx)
		{
			const std::pair<ASCIITextFile, bool> loadedfile = *(m_loadedfiles.begin() + idx);
			if (!fileExists(loadedfile.first))
			{
				throw std::runtime_error("erasing nonexistent element");
				return;
			}
			m_load_record.erase(loadedfile.first);
			m_loadedfiles.erase(m_loadedfiles.begin() + idx);
		}

		bool fileExists(const ASCIITextFile& file)
		{
			return (m_load_record.find(file) != m_load_record.end());
		}

		int32_t findFileIdx(const std::filesystem::path& filepath)
		{
			for (size_t i = 0; i < getSize(); i++)
			{
				if (m_loadedfiles[i].first.constructFilePath() == filepath)
				{
					return i;
				}
			}
			return -1;
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
		std::vector<std::pair<ASCIITextFile, bool>> m_loadedfiles;
		std::unordered_set<ASCIITextFile, SourceFileHasher, SourceFileEquality> m_load_record;
	};  // LoadedFileRecord

}  // namespace StrawPen
