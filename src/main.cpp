/***********************************************************************************************************************************
 * main.cpp
 * 05-04-2025
 **********************************************************************************************************************************/

#include "editor.hpp"
#include "strawplate/strawplate.hpp"
// ======================

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <memory>
// ======================

int main(int argc, char* argv[])
{
#ifdef DEBUG_BUILD
	printf("[THIS IS A DEBUG BUILD]\n\n");
#endif
#ifdef NDEBUG
	printf("[THIS IS A NON-DEBUG BUILD]\n\n");
#endif

	try
	{
		StrawPlate::WindowSettings win_settings;
#ifdef DEBUG_BUILD
		win_settings.label = "StrawPen Editor Debug";
		spdlog::set_level(spdlog::level::debug);
#endif
#ifdef NDEBUG
		win_settings.label = "StrawPen Editor Release";
#endif
		win_settings.width = 1920 * 0.5;
		win_settings.height = 1080 * 0.5;

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