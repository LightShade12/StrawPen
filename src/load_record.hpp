/***************************************************************************************************************************
 * load_record.hpp
 * 16-04-2025
 ****************************************************************************************************************************/
#pragma once

#include "source_file.hpp"
//================================

#include <cstdint>
#include <unordered_set>
#include <utility>
#include <vector>

//================================

namespace StrawPen
{
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

		size_t getSize() const
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