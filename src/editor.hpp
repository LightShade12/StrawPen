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

namespace StrawPen
{

	class EditorLayer : public StrawPlate::StrawPlateLayer, public Mediator
	{
	public:
		EditorLayer()
		    : m_explorer(this, std::filesystem::current_path()),
		      m_source(this, std::filesystem::current_path()) {};
		~EditorLayer() override = default;

		EditorLayer(const EditorLayer& other) = default;
		EditorLayer(EditorLayer&& other) = default;

		EditorLayer& operator=(const EditorLayer& other) = default;
		EditorLayer& operator=(EditorLayer&& other) = default;

		void notify(Component* sender, std::string event) override
		{
			if (DirectoryExplorer* direxp = dynamic_cast<DirectoryExplorer*>(sender);
			    direxp != nullptr)
			{
				if (event == "load_file")
				{
					m_source.loadFile(direxp->getSelectedFilePath());
					spdlog::debug("Handled load_file");
				}
				if (event == "create_file")
				{
					auto path = direxp->getWorkingDirectory();
					m_source.createFile(path.append("unnamed"));
					spdlog::debug("Handled create_file");
				}
				if (event == "rename_file")
				{
					const std::string new_name = direxp->getRenameInput();
					m_source.renameFile(direxp->getAuxSelectedFilePath(), new_name);
					spdlog::debug("Handled rename_file");
				}
				if (event == "delete_file")
				{
					m_source.deleteFile(direxp->getAuxSelectedFilePath());
					spdlog::debug("Handled delete_file");
				}
			}
			if (SourceEditor* srcedit = dynamic_cast<SourceEditor*>(sender); srcedit != nullptr)
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
			if (m_custom_font)
			{
				ImGui::PushFont(m_custom_font);
			}
			// ================================================

			ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(),
			                             ImGuiDockNodeFlags_PassthruCentralNode);
			{
				ImGui::BeginMainMenuBar();
				if (ImGui::BeginMenu("File"))
				{
					ImGui::MenuItem("Open");
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("View"))
				{
					ImGui::MenuItem("Terminal");
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Settings"))
				{
					ImGui::MenuItem("ToolKit");
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Help"))
				{
					ImGui::MenuItem("About");
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}

			ImGui::ShowDemoWindow();

			m_source.render();

			m_explorer.render();

			static std::string output_buffer = "";

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

			if (m_custom_font)
			{
				ImGui::PopFont();
			}
		}

		void onInput(int key, int scancode, int action, int mods) override
		{
			if (glfwGetKeyScancode(GLFW_KEY_S) == scancode && (action == GLFW_PRESS) &&
			    (mods & GLFW_MOD_CONTROL))
			{
				m_source.saveFile();
			}
		}

	private:
		SourceEditor m_source;
		DirectoryExplorer m_explorer;
		ImFont* m_custom_font = nullptr;
	};  // EditorLayer

}  // namespace StrawPen
