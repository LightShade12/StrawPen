/*
MIT License

Copyright (c) 2025 Subham Swastik Pradhan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/***********************************************************************************************************************************
 * main.cpp
 * 05-04-2025
 **********************************************************************************************************************************/

#include "editor.hpp"
#include "strawplate/strawplate.hpp"
#include "version_info.h"
// ======================

#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
// ======================

#if !defined(DEBUG_BUILD) && !defined(NDEBUG)
#error "UNPECIFIED BUILD CONFIGURATION"
#endif

int main(int argc, char* argv[])
{
	try
	{
		std::cout << VERSION_STRING << "\n";
#if defined(DEBUG_BUILD)
		std::cout << "[THIS IS A DEBUG BUILD]\n\n";
#elif defined(NDEBUG)
		std::cout << "[THIS IS A NON-DEBUG BUILD]\n\n";
#else
#error "UNPECIFIED BUILD CONFIGURATION"
#endif

		StrawPlate::WindowSettings win_settings;
#if defined(DEBUG_BUILD)
		win_settings.label = "StrawPen Editor Debug";
		win_settings.width = 1920 * 0.5;
		win_settings.height = 1080 * 0.5;
		spdlog::set_level(spdlog::level::debug);
#elif defined(NDEBUG)
		win_settings.label = "StrawPen Editor Release";
		win_settings.width = 1920;
		win_settings.height = 1080;
		win_settings.fullscreen = true;
#else
#error "UNPECIFIED BUILD CONFIGURATION"
#endif
		win_settings.icon_filepath = "./assets/icons/icon.png";
		win_settings.gui_settings.font_ttf_filepath = "./assets/fonts/JetBrainsMono-Regular.ttf";
		StrawPen::starting_directory = "D:/dev0/test/main_cxx";
		const std::shared_ptr<StrawPlate::LayerMaker> layer_factory =
		    std::make_shared<StrawPlate::ConcreteLayerMaker<StrawPen::EditorLayer>>();

		StrawPlate::GLFWApplication app(win_settings, layer_factory);
		app.run();
	}
	catch (const std::exception& e)
	{
		spdlog::critical("EXCEPTION: {}\n", e.what());
		return EXIT_FAILURE;
	}
	catch (...)
	{
		fprintf(stderr, "UNKNOWN EXCEPTION CAUGHT");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}