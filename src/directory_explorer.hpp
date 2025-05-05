/***************************************************************************************************************************
 * directory_explorer.hpp
 * 09-04-2025
 **************************************************************************************************************************/

#pragma once

#include "mediator_system.hpp"
// ======================

#include "spdlog/spdlog.h"
// ======================

#include <filesystem>
#include <utility>
// ======================

namespace StrawPen
{

	class DirectoryExplorer : public Component
	{
	public:
		explicit DirectoryExplorer(Mediator* mediator, std::filesystem::path working_dir)
		    : m_working_dir(std::move(working_dir)), Component(mediator) {};

		~DirectoryExplorer() override = default;

		//============================

		DirectoryExplorer(const DirectoryExplorer& other) = default;
		DirectoryExplorer(DirectoryExplorer&& other) = default;

		//============================

		DirectoryExplorer& operator=(DirectoryExplorer&& other) = default;
		DirectoryExplorer& operator=(const DirectoryExplorer& other) = default;

		//============================

		void render();

		void setWorkingDirectory(const std::filesystem::path& dir_path)
		{
			m_working_dir = dir_path;
		}

		[[nodiscard]] std::filesystem::path getWorkingDirectory() const { return m_working_dir; }

		[[nodiscard]] std::filesystem::path getSelectedFilePath() const
		{
			return m_selected_filepath;
		}
		[[nodiscard]] std::filesystem::path getAuxSelectedFilePath() const
		{
			return m_aux_selected_filepath;
		}
		[[nodiscard]] std::string getRenameInput() const { return m_rename_input_str; }

	private:
		/// @brief NOTE : call directly after TreeNodeEx()
		/// @param filepath
		/// @param r_filectxrequest
		void processFileClicks(const std::filesystem::path& filepath,
		                       std::pair<bool, std::filesystem::path>* r_filectxrequest);

		void requestFileLoad(const std::filesystem::path& filepath)
		{
			m_selected_filepath = filepath;
			spdlog::debug("requesting file load {}", m_selected_filepath.string().c_str());
			m_mediator->notify(this, "load_file");
		}

		void requestFileRename(const std::filesystem::path& filepath)
		{
			m_aux_selected_filepath = filepath;
			spdlog::debug("requesting file rename: {}", m_aux_selected_filepath.string().c_str());
			m_mediator->notify(this, "rename_file");
		}

		void requestFileDelete(const std::filesystem::path& filepath)
		{
			m_aux_selected_filepath = filepath;
			spdlog::debug("requesting file delete {}", m_aux_selected_filepath.string().c_str());
			m_mediator->notify(this, "delete_file");
		}

		void requestDirChange()
		{
			spdlog::debug("requesting dir change");
			m_mediator->notify(this, "change_dir");
		}

		bool recurseRenderDirectory(const std::filesystem::path& dir_path,
		                            std::pair<bool, std::filesystem::path>* r_filectxrequest);

		void recurseRenderSearchResults(const std::filesystem::path& dir_path,
		                                std::pair<bool, std::filesystem::path>* r_filectxrequest);

		//=============================

		std::filesystem::path m_working_dir;
		std::filesystem::path m_selected_filepath;
		std::filesystem::path m_aux_selected_filepath;
		std::string m_search_string_buff;
		std::string m_rename_input_str;

	};  // DirectoryExplorer

}  // namespace StrawPen
