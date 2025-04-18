/***********************************************************************************************************************************
 * main.cpp
 * 05-04-2025
 **********************************************************************************************************************************/

#include "editor.hpp"
#include "strawplate/strawplate.hpp"
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

	return EXIT_SUCCESS;
}