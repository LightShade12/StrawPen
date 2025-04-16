/***************************************************************************************************************************
 * source_editor.hpp
 * 06-04-2025
 * sorry. I am retarded.
 **************************************************************************************************************************/

#pragma once

#include "load_record.hpp"
#include "mediator_system.hpp"

// ==========================

#include <filesystem>
#include <string>
// ==========================

namespace StrawPen
{

	class SourceEditor : public Component
	{
	public:
		explicit SourceEditor(Mediator* mediator) : Component(mediator) {};

		void loadFile(const std::filesystem::path& filepath);

		void createFile(const std::filesystem::path& filepath);

		void deleteFile(const std::filesystem::path& filepath);

		void renameFile(const std::filesystem::path& filepath, const std::string& new_name);

		void saveFile() { m_loadedfiles[m_current_file_index].first.writeToDisk(); }

		void render();

	private:
		std::string m_filename_input_buff;
		int32_t m_current_file_index = 0;
		LoadedFileRecord m_loadedfiles;

	};  // SourceEditor

}  // namespace StrawPen
