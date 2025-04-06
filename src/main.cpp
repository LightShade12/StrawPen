#include "editor.hpp"

// ======================
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

int main(int argc, char* argv[])
{
	try
	{
		StrawPlate::WindowSettings win_settings;
		win_settings.label = "StrawPen Editor";
		win_settings.width = 1920 * 0.5;
		win_settings.height = 1080 * 0.5;

		std::shared_ptr<StrawPlate::LayerMaker> layer_factory =
		    std::make_shared<
		        StrawPlate::ConcreteLayerMaker<StrawPen::EditorLayer>>();

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