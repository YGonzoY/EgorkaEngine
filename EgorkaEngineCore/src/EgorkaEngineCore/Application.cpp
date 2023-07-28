#include "EgorkaEngineCore/Log.hpp"
#include "EgorkaEngineCore/Application.hpp"
#include "EgorkaEngineCore//Window.hpp"

#include <iostream>

namespace EgorkaEngine
{
		Application::Application()
		{
			LOG_INFO("starting application");
		}

		Application::~Application()
		{
			LOG_INFO("closing application");
		}

		int Application::start(unsigned int window_w, unsigned int window_h, const char* title)
		{
			window = std::make_unique<Window>(title, window_w, window_h);
			while (true)
			{
				window->on_update();
				on_update();
			}
			return 0;
		}
}
