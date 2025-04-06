/***************************************************************************************************************************
 * editor.hpp
 **************************************************************************************************************************/
#pragma once

#include "directory_explorer.hpp"
#include "source_editor.hpp"
// ====================
#include "strawplate/strawplate.hpp"
// ====================
#include <filesystem>
#include <string>

namespace StrawPen
{

	class EditorLayer : public StrawPlate::StrawPlateLayer
	{
	public:
		EditorLayer()
		    : m_explorer(std::filesystem::current_path().string().c_str()),
		      m_source(std::filesystem::current_path()) {};
		~EditorLayer() override = default;

		EditorLayer(const EditorLayer& other) = default;
		EditorLayer(EditorLayer&& other) = default;

		EditorLayer& operator=(const EditorLayer& other) = default;
		EditorLayer& operator=(EditorLayer&& other) = default;

		void onAttach() override {}

		void onDetach() override {}

		void onRender(float timestep_secs) override
		{
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

			m_source.render();

			m_explorer.render();

			ImGui::ShowDemoWindow();

			ImGui::Begin("Output");
			ImGui::End();
		}

		void onInput(int key, int scancode, int action, int mods) override
		{
			if (glfwGetKeyScancode(GLFW_KEY_S) == scancode && (action == GLFW_PRESS) &&
			    (mods & GLFW_MOD_CONTROL))
			{
				m_source.writeToFile(m_explorer.getCurrentDirectory().c_str());
			}
		}

	private:
		SourceEditor m_source;
		DirectoryExplorer m_explorer;

	};  // EditorLayer

}  // namespace StrawPen
