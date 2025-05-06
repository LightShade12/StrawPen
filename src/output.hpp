#pragma once

#include "process.hpp"
//----
#include "imgui.h"
//----
#include <string>

namespace StrawPen
{

	class OutputViewer
	{
	public:
		OutputViewer(/* args */)
		{
			print("[Status]");
			process::CommandResult res = process::executeCommand("clang++ --version", true);
			print(res.std_stream_read);
			res = process::executeCommand("ninja --version", true);
			print(res.std_stream_read);
			res = process::executeCommand("cmake --version", true);
			print(res.std_stream_read);
		};

		void executeCommand(const char* command)
		{
			const process::CommandResult res = process::executeCommand(command, true);
			print(res.std_stream_read);
		};

		void print(const char* message)
		{
			m_buffer.append(message);
			m_buffer.append("\n");
		}
		void print(const std::string& message)
		{
			m_buffer.append(message);
			m_buffer.append("\n");
		}

		void render()
		{
			ImGui::Begin("Output");
			{
				if (ImGui::Button("Clear"))
				{
					m_buffer.clear();
				}
				ImGui::SameLine();
				ImGui::Button("To top");

				ImGui::BeginChild("txtout", ImVec2(0, 0), ImGuiChildFlags_Borders);
				{
					ImGui::TextWrapped("%s", m_buffer.c_str());
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}

	private:
		std::string m_buffer;
	};

}  // namespace StrawPen
