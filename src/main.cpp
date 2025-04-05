#include "strawplate/strawplate.hpp"
//======
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

		std::shared_ptr<StrawPlate::LayerMaker> layer_factory =
		    std::make_shared<
		        StrawPlate::ConcreteLayerMaker<StrawPlate::SampleLayer>>();

		StrawPlate::GLFWApplication app(win_settings, layer_factory);
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "CAUGHT EXCEPTION:" << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}