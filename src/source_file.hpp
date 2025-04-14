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
	 * @brief An handle object associating text string content with a filepath
	 */
	class ASCIITextFile
	{
	public:
		explicit ASCIITextFile(const std::filesystem::path& p_filepath)
		    : m_filename(p_filepath.filename().string()),
		      m_dir_path(p_filepath.parent_path().string()) {};

		/// @brief Instantiate from existing filepath
		/// @param p_file_path file path
		/// @return loaded SourceFile
		static ASCIITextFile loadFromDisk(const std::filesystem::path& p_file_path)
		{
			ASCIITextFile loaded_file(p_file_path);
			if (!loaded_file.existsOnDisk())
			{
				throw std::runtime_error("[LOAD] file does not exist on disk");
			}

			std::ifstream in_file_strm;
			in_file_strm.open(p_file_path, std::ios::binary | std::ios::ate | std::ios::in);
			if (!in_file_strm.is_open())
			{
				throw std::runtime_error("[LOAD] file stream open error");
			}

			const size_t source_char_len = in_file_strm.tellg();
			if (const size_t max_size = std::numeric_limits<std::streamsize>::max();
			    source_char_len > max_size)
			{
				throw std::runtime_error("[LOAD] file content too long for reading");
			}
			loaded_file.m_source_string.resize(source_char_len);

			in_file_strm.seekg(0, std::ios::beg);
			in_file_strm.read(loaded_file.m_source_string.data(),
			                  static_cast<std::streamsize>(source_char_len));
			if (in_file_strm.fail())
			{
				throw std::runtime_error("[LOAD] file reading error");
			}

			return loaded_file;
		}

		bool operator==(const ASCIITextFile& p_other) const
		{
			return m_filename == p_other.m_filename && m_dir_path == p_other.m_dir_path;
		}

		void writeToDisk()
		{
			if (m_filename.empty() || m_dir_path.empty())
			{
				spdlog::error("{}:{}:[WRITE] empty path/name", __FILE__, __LINE__);
				throw std::runtime_error("[WRITE] empty path/name");
			}

			std::ofstream out_file;
			out_file.open(constructFilePath(), std::ios::binary | std::ios::out);  // create
			if (!out_file.is_open())
			{  // can also check out_file.fail()
				throw std::runtime_error("[WRITE] filestream open/file create error");
			}

			if (const size_t max_size = std::numeric_limits<std::streamsize>::max();
			    m_source_string.size() > max_size)
			{
				throw std::runtime_error("[WRITE] file content too long for writing");
			}

			out_file.write(m_source_string.data(), static_cast<int64_t>(m_source_string.size()));
			if (out_file.fail())
			{
				throw std::runtime_error("[WRITE] file writing error");
			}

			setIsUnsaved(false);
		}

		void rename(const std::string& p_new_filename)
		{
			if (existsOnDisk())
			{
				// disk item rename
				auto old_filepath = constructFilePath();
				std::filesystem::path new_filepath = m_dir_path;
				new_filepath.append(p_new_filename);

				spdlog::debug("renaming src: {} to {}", old_filepath.string().c_str(),
				              new_filepath.string().c_str());

				std::filesystem::rename(old_filepath, new_filepath);
			}
			// memory item rename
			m_filename = p_new_filename;
		}

		void deleteFromDisk() const
		{
			if (!existsOnDisk())
			{
				spdlog::warn("[DELETE] File does not exist on disk");
				return;
			}
			if (!std::filesystem::remove(constructFilePath()))
			{
				throw std::runtime_error("File deletion failed");
			}
		}

		[[nodiscard]] bool existsOnDisk() const
		{
			return std::filesystem::is_regular_file(constructFilePath());
		}

		// ===================================================================

		[[nodiscard]] std::filesystem::path constructFilePath() const
		{
			std::filesystem::path fullfilepath(m_dir_path);
			fullfilepath.append(m_filename);
			return fullfilepath;
		}

		[[nodiscard]] std::string* getFileNamePtr() { return &m_filename; }
		[[nodiscard]] std::string getFileName() const { return m_filename; }
		void setFileName(const std::string& p_filename) { m_filename = p_filename; }

		[[nodiscard]] std::string getDirPath() const { return m_dir_path; }
		void setDirPath(const std::string& p_path) { m_dir_path = p_path; }

		std::string* getCharBufferPtr() { return &m_source_string; }
		[[nodiscard]] std::string getCharContent() const { return m_source_string; }
		void setCharContent(const std::string& p_data) { m_source_string = p_data; }

		void setIsUnsaved(bool p_is_unsaved) { m_unsaved = p_is_unsaved; }
		[[nodiscard]] bool isUnsaved() const { return m_unsaved; }

	private:
		bool m_unsaved = false;
		std::string m_filename = "unnamed";
		std::string m_dir_path = "./";
		std::string m_source_string;
	};  // TextFile
}  // namespace StrawPen

// for hashing
namespace std
{
	template <>
	struct hash<StrawPen::ASCIITextFile>
	{
		size_t operator()(const StrawPen::ASCIITextFile& p_file) const
		{
			const size_t hsh1 = std::hash<std::string> {}(p_file.getFileName());
			const size_t hsh2 = std::hash<std::string> {}(p_file.getDirPath());
			return hsh1 ^ (hsh2 << 1);
		}
	};  // hash<StrawPen::SourceFile>

}  // namespace std

namespace StrawPen
{

	struct SourceFileHasher
	{
		size_t operator()(const ASCIITextFile& p_file) const
		{
			return std::hash<ASCIITextFile> {}(p_file);
		}
	};  // SourceFileHasher

	struct SourceFileEquality
	{
		bool operator()(const ASCIITextFile& p_first, const ASCIITextFile& p_second) const
		{
			return p_first == p_second;
		}
	};  // SourceFileEquality

	class LoadedFileRecord
	{
	public:
		LoadedFileRecord() = default;

		std::pair<ASCIITextFile, bool> operator[](int p_idx) const { return m_loadedfiles[p_idx]; }
		std::pair<ASCIITextFile, bool>& operator[](int p_idx) { return m_loadedfiles[p_idx]; }

		void add(const ASCIITextFile& p_file)
		{
			// indempotent file load handling
			if (IsFileLoaded(p_file))
			{
				spdlog::debug("file already loaded");
				return;
			}
			m_loadedfiles.emplace_back(p_file, true);
			m_load_record.emplace(p_file);
		}

		void renameFile(int32_t p_idx, const std::string& p_new_filename)
		{
			ASCIITextFile& file = m_loadedfiles[p_idx].first;
			m_load_record.erase(file);

			file.rename(p_new_filename);
			m_load_record.emplace(file);
		}

		void renameFile(const std::filesystem::path& p_filepath, const std::string& p_new_filename)
		{
			const int idx = findFileIdx(p_filepath);
			if (idx < 0)
			{
				spdlog::warn("rename target file not found in MEMORY");
				return;
			}
			ASCIITextFile& file = m_loadedfiles[idx].first;
			m_load_record.erase(file);

			file.rename(p_new_filename);
			m_load_record.emplace(file);
		}

		void erase(int p_idx)
		{
			const std::pair<ASCIITextFile, bool> loadedfile = *(m_loadedfiles.begin() + p_idx);
			if (!IsFileLoaded(loadedfile.first))
			{
				throw std::runtime_error("erasing nonexistent element");
				return;
			}
			m_load_record.erase(loadedfile.first);
			m_loadedfiles.erase(m_loadedfiles.begin() + p_idx);
		}

		bool IsFileLoaded(const ASCIITextFile& p_file)
		{
			return (m_load_record.find(p_file) != m_load_record.end());
		}

		bool IsFileLoaded(const std::filesystem::path& p_filepath)
		{
			if (!p_filepath.has_filename())
			{
				throw std::runtime_error("[Load query] invalid filepath; no filename");
			}
			return (m_load_record.find(ASCIITextFile(p_filepath)) != m_load_record.end());
		}

		int32_t findFileIdx(const std::filesystem::path& p_filepath)
		{
			for (size_t i = 0; i < getSize(); i++)
			{
				if (m_loadedfiles[i].first.constructFilePath() == p_filepath)
				{
					return static_cast<int32_t>(i);
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
