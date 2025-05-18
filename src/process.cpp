#include "process.hpp"

namespace StrawPen
{
	namespace process
	{
		CommandResult executeCommand(const char* cmd, bool silent, std::string* stream_buffer,
		                             std::mutex& bufferlock)

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
					{
						const std::lock_guard lock(bufferlock);
						(*stream_buffer) += buffer.data();
					}

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