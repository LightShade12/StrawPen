#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

namespace StrawPen
{

	namespace process
	{

#if defined(_WIN32) || defined(_WIN64)

#define PROCOPEN(cmd, mode) _popen(cmd, mode)
#define PROCCLOSE(stream) _pclose(stream)

#elif defined(__linux__) || defined(__linux)

#define PROCOPEN(cmd, mod) popen(cmd, mode)
#define PROCCLOSE(stream) pclose(stream)

#else
#error UNSUPPORTED OS
#endif

		/*TODO : Uses unsafe system calls*/

		class Pipe
		{
		public:
			Pipe(const char* command, int* r_status_code)
			    : m_stream(PROCOPEN((std::string(command) + " 2>&1").c_str(), "rt")),
			      m_status_code(r_status_code)
			{
				if (m_stream == nullptr)
				{
					throw std::runtime_error("_popen() failed!");
				}
			}

			~Pipe()
			{
				try
				{
					const int exit_code = PROCCLOSE(m_stream);

					if (exit_code == -1)
					{
						std::cerr << "_pclose() failed.\n";
					}
					else
					{
						// The exit code from _pclose might need shifting
						// depending on the OS/compiler, but for simple
						// success/failure, 0 usually indicates success on
						// Windows.

						*m_status_code = exit_code;
						// std::cout << "Command exited with status: " <<
						// exit_code
						//          << "\n";
						if (exit_code != 0)
						{
							std::cerr << "Command may have encountered an error.\n";
						}
					}
					m_stream = nullptr;
				}
				catch (const std::exception& err)
				{
					(void)fprintf_s(stderr, "EXCEPTION: %s\n", err.what());
				}
			}

			[[nodiscard]] FILE* getStream() const { return m_stream; }

		private:
			FILE* m_stream = nullptr;
			int* m_status_code = nullptr;
		};

		struct CommandResult
		{
			std::string std_stream_read;
			int return_code = 0;
		};

		constexpr int BUFFER_SIZE = 8192 * 2;

		inline CommandResult executeCommand(const char* cmd, bool silent)
		{
			int ret_code = NULL;
			std::string output;

			{
				const Pipe proc(cmd, &ret_code);

				std::vector<char> buffer;
				buffer.resize(BUFFER_SIZE);

				while (fgets(buffer.data(), buffer.size(), proc.getStream()) != nullptr)
				{
					output += buffer.data();

					if (!silent)
					{
						std::cout << buffer.data();
					}
				}
			}

			return {output, ret_code};
		};

	}  // namespace process
}  // namespace StrawPen
