/***************************************************************************************************************************
 * editor.hpp
 * 05-04-2025
 **************************************************************************************************************************/

#pragma once

#include "directory_explorer.hpp"
#include "mediator_system.hpp"
#include "source_editor.hpp"
#include "theme.hpp"
// ========================

#include "strawplate/strawplate.hpp"
// =========================

#include <filesystem>
#include <string>
// ========================

namespace
{
	inline void setCentreWindow(ImVec2 padding_ratio = ImVec2(0.8, 0.5))
	{
		auto wnd = StrawPlate::GLFWAppWindow::get();
		int width = 0, height = 0;
		wnd->getSize(&width, &height);
		auto size = ImVec2(width - (width * padding_ratio.x), height - (height * padding_ratio.y));
		ImGui::SetNextWindowSize(size);
		ImGui::SetNextWindowPos(
		    ImVec2((width * padding_ratio.x) / 2.0f, 30 + (height * padding_ratio.y) / 2.0f));
	}

	inline void setItemToParentCenter(float item_width)
	{
		auto parent_avail_size = ImGui::GetContentRegionAvail();
		float offset_x = (parent_avail_size.x - item_width) / 2;
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset_x);
	}
}  // namespace

namespace StrawPen
{

	class EditorLayer : public StrawPlate::StrawPlateLayer, public Mediator
	{
	public:
		EditorLayer() : m_explorer(this, std::filesystem::current_path()), m_source_editor(this) {};
		~EditorLayer() override = default;

		EditorLayer(const EditorLayer& other) = default;
		EditorLayer(EditorLayer&& other) noexcept = default;

		EditorLayer& operator=(const EditorLayer& other) = default;
		EditorLayer& operator=(EditorLayer&& other) = default;

		void notify(Component* sender, std::string event) override
		{
			if (auto* direxp = dynamic_cast<DirectoryExplorer*>(sender); direxp != nullptr)
			{
				if (event == "load_file")
				{
					m_source_editor.loadFile(direxp->getSelectedFilePath());
					spdlog::debug("Handled load_file");
				}
				if (event == "create_file")
				{
					auto path = direxp->getWorkingDirectory();
					m_source_editor.createFile(path.append("unnamed"));
					spdlog::debug("Handled create_file");
				}
				if (event == "rename_file")
				{
					const std::string new_name = direxp->getRenameInput();
					m_source_editor.renameFile(direxp->getAuxSelectedFilePath(), new_name);
					spdlog::debug("Handled rename_file");
				}
				if (event == "delete_file")
				{
					m_source_editor.deleteFile(direxp->getAuxSelectedFilePath());
					spdlog::debug("Handled delete_file");
				}
				if (event == "change_dir")
				{
					m_open_dir_dialog = true;
					spdlog::debug("Handled change_dir");
				}
			}
			if (auto* srcedit = dynamic_cast<SourceEditor*>(sender); srcedit != nullptr)
			{
				if (event == "execute_test")
				{
					spdlog::debug("Handled test execution");
				}
			}
		}

		void onAttach() override { m_custom_font = ImGuiThemes::Dark(); }

		void onDetach() override {}

		void onRender(float timestep_secs) override
		{
			if (m_custom_font != nullptr)
			{
				ImGui::PushFont(m_custom_font);
			}
			// ================================================

			ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(),
			                             ImGuiDockNodeFlags_PassthruCentralNode);

			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open"))
					{
						m_open_file_dialog = true;
					}
					if (ImGui::MenuItem("Change Directory"))
					{
						m_open_dir_dialog = true;
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("View"))
				{
					ImGui::BeginDisabled();
					ImGui::MenuItem("Terminal");
					ImGui::SetItemTooltip("Not implemented yet");
					ImGui::EndDisabled();

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Settings"))
				{
					ImGui::BeginDisabled();
					ImGui::MenuItem("ToolKit");
					ImGui::SetItemTooltip("Not implemented yet");
					ImGui::EndDisabled();
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Help"))
				{
					if (ImGui::MenuItem("About"))
					{
						m_open_about_dialog = true;
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}

#ifdef DEBUG_BUILD
			ImGui::ShowDemoWindow();
#endif

			m_source_editor.render();

			m_explorer.render();

			const static std::string output_buffer;

			ImGui::Begin("Output");
			{
				ImGui::Button("Clear");
				ImGui::SameLine();
				ImGui::Button("To top");

				ImGui::BeginChild("txtout", ImVec2(0, 0), ImGuiChildFlags_Borders);
				{
					ImGui::TextWrapped("%s", output_buffer.c_str());
				}
				ImGui::EndChild();
			}
			ImGui::End();

			// ================================================

			bool popenf = true;
			bool popend = true;
			bool popena = true;
			{
				if (m_open_file_dialog)
				{
					ImGui::OpenPopup("open_new_file");
					m_open_file_dialog = false;
					setCentreWindow(ImVec2(0.7, 0.9));
				}
				if (ImGui::BeginPopupModal("open_new_file", &popenf))
				{
					std::string filepath;
					ImGui::Text("Open new file");
					if (ImGui::InputTextWithHint(": file path", "C:/File/file.txt...", &filepath,
					                             ImGuiInputTextFlags_EnterReturnsTrue))
					{
						spdlog::debug("new file load");
						if (!std::filesystem::is_regular_file(filepath))
						{
							spdlog::error("invalid filepath!");
						}
						else
						{
							m_source_editor.loadFile(std::filesystem::path(filepath));
						}
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}

			{
				if (m_open_dir_dialog)
				{
					ImGui::OpenPopup("open_new_dir");
					m_open_dir_dialog = false;
					setCentreWindow(ImVec2(0.7, 0.9));
				}
				if (ImGui::BeginPopupModal("open_new_dir", &popend))
				{
					std::string dir_path;
					ImGui::Text("Open new directory");
					if (ImGui::InputTextWithHint(": file path", "C:/File/MyDir...", &dir_path,
					                             ImGuiInputTextFlags_EnterReturnsTrue))
					{
						spdlog::debug("new dir load");
						std::filesystem::path dirpth(dir_path);
						if (!std::filesystem::is_directory(dirpth))
						{
							spdlog::error("invalid dir!");
						}
						else
						{
							m_explorer.setWorkingDirectory(std::filesystem::path(dir_path));
						}
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}

			{
				if (m_open_about_dialog)
				{
					ImGui::OpenPopup("About");
					m_open_about_dialog = false;
					setCentreWindow(ImVec2(0.6, 0.8));
				}
				if (ImGui::BeginPopupModal("About", &popena))
				{
					const char* ln1 = "StrawPen Text Editor";
					const char* ln2 = VERSION_STRING;
					const char* ln3 = "Author: Subham Swastik Pradhan @LightShade12";

					setItemToParentCenter(ImGui::CalcTextSize(ln1).x);
					ImGui::Text("%s", ln1);
					setItemToParentCenter(ImGui::CalcTextSize(ln2).x);
					ImGui::Text("%s", ln2);
					setItemToParentCenter(ImGui::CalcTextSize(ln3).x);
					ImGui::Text("%s", ln3);

					setItemToParentCenter(ImGui::CalcTextSize("close").x);
					if (ImGui::Button("close"))
					{
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}
			}

			if (m_custom_font != nullptr)
			{
				ImGui::PopFont();
			}
		}

		void onInput(int key, int scancode, int action, int mods) override
		{
			if (glfwGetKeyScancode(GLFW_KEY_S) == scancode && (action == GLFW_PRESS) &&
			    (mods & GLFW_MOD_CONTROL))
			{
				m_source_editor.saveFile();
			}

			if (glfwGetKeyScancode(GLFW_KEY_O) == scancode && (action == GLFW_PRESS) &&
			    (mods & GLFW_MOD_CONTROL))
			{
				m_open_file_dialog = true;
			}
		}

	private:
		bool m_open_file_dialog = false;
		bool m_open_about_dialog = false;
		bool m_open_dir_dialog = false;
		SourceEditor m_source_editor;
		DirectoryExplorer m_explorer;
		ImFont* m_custom_font = nullptr;
		std::string m_temp = R"([main] Building folder: d:/dev0/projects/StrawPen/build 
			[build] Starting build
			[proc] Executing command: "C:\Program Files\CMake\bin\cmake.EXE" --build d:/dev0/projects/StrawPen/build --config Debug --target all --
			[build] [1/2   0% :: 0.006] Re-checking globbed directories...
			[build] ninja: no work to do.
			[driver] Build completed: 00:00:00.076
			[build] Build finished with exit code 0)";
	};  // EditorLayer

}  // namespace StrawPen
