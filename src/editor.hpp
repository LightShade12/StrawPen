/***************************************************************************************************************************
 * editor.hpp
 * 05-04-2025
 **************************************************************************************************************************/

#pragma once

#include "directory_explorer.hpp"
#include "mediator_system.hpp"
#include "output.hpp"
#include "source_editor.hpp"

// ========================

#include "strawplate/strawplate.hpp"
// =========================

#include <filesystem>
#include <string>
// ========================

namespace StrawPen
{
	// Set working directory here
	inline const char* starting_directory = "";

	/***
	 * @brief Editor core logic
	 */
	class EditorLayer : public StrawPlate::StrawPlateLayer, public Mediator
	{
	public:
		EditorLayer() : m_explorer(this, parsePath(starting_directory)), m_source_editor(this) {};
		~EditorLayer() override = default;

		// ========================

		EditorLayer(const EditorLayer& other) = default;
		EditorLayer(EditorLayer&& other) noexcept = default;

		EditorLayer& operator=(const EditorLayer& other) = default;
		EditorLayer& operator=(EditorLayer&& other) = default;

		// ========================

		/// @brief Handle events from components
		/// @param a_sender Component subclass
		/// @param a_event event id string
		void notify(Component* a_sender, std::string a_event) override;

		void onAttach() override;

		void onDetach() override {}

		void onRender(float a_timestep_secs) override;

		/// @brief Keybinds handling logic
		/// @param a_key
		/// @param a_scancode
		/// @param a_action
		/// @param a_mods
		void onInput(int a_key, int a_scancode, int a_action, int a_mods) override;

	private:
		void onEventCompileFile(const std::filesystem::path& filepath);
		void onEventExecuteFile(const std::filesystem::path& filepath);

		static std::filesystem::path parsePath(const char* filepath)
		{
			const std::string path = filepath;

			if (path.empty() || path == ".")
			{
				return std::filesystem::current_path();
			}

			if (std::filesystem::path filedir = path; std::filesystem::exists(filedir))
			{
				if (std::filesystem::is_regular_file(filedir))
				{
					return filedir.parent_path();
				}
				return filedir;
			}

			throw std::runtime_error("Invalid path");
		}

		bool m_open_file_dialog = false;
		bool m_open_about_dialog = false;
		bool m_open_dir_dialog = false;
		SourceEditor m_source_editor;
		DirectoryExplorer m_explorer;
		OutputViewer m_output;
		ImFont* m_custom_font = nullptr;
		// Prototyping
		std::string m_temp = R"([main] Building folder: d:/dev0/projects/StrawPen/build 
			[build] Starting build
			[proc] Executing command: "C:\Program Files\CMake\bin\cmake.EXE" --build d:/dev0/projects/StrawPen/build --config Debug --target all --
			[build] [1/2   0% :: 0.006] Re-checking globbed directories...
			[build] ninja: no work to do.
			[driver] Build completed: 00:00:00.076
			[build] Build finished with exit code 0)";
	};  // EditorLayer

}  // namespace StrawPen
