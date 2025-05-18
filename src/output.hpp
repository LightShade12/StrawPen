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
			process::CommandResult res = process::executeCommand(
			    "clang++ --version", true, &m_buffer, std::ref(m_buffer_mutex));

			res = process::executeCommand("ninja --version", true, &m_buffer,
			                              std::ref(m_buffer_mutex));
			res = process::executeCommand("cmake --version", true, &m_buffer,
			                              std::ref(m_buffer_mutex));
		};

		void executeCommand(const char* command)
		{
			m_proc_future = std::async(std::launch::async, process::executeCommand, command, true,
			                           &m_buffer, std::ref(m_buffer_mutex));
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

		void clear() { m_buffer.clear(); }

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
					std::lock_guard lock(m_buffer_mutex);
					ImGui::TextWrapped("%s", m_buffer.c_str());
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}

	private:
		std::string m_buffer;
		inline static std::future<process::CommandResult> m_proc_future;
		inline static std::mutex m_buffer_mutex;
	};

}  // namespace StrawPen
