#include "EgorkaEngineCore/Log.hpp"
#include "EgorkaEngineCore/Application.hpp"
#include "EgorkaEngineCore//Window.hpp"
#include "EgorkaEngineCore/Event.hpp"

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
			
			event_dispatcher.add_event_listener<EventMouseMoved>(
				[](EventMouseMoved& event)
				{
					LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
				});


			event_dispatcher.add_event_listener<EventWindowResize>(
				[](EventWindowResize& event)
					{
						LOG_INFO("window resized to {0}x{1}", event.height, event.width);
					});

			window->set_eventcallback(
				[&](BaseEvent& event)
				{
					event_dispatcher.dispatch(event);
				}
			);

			while (!CloseWindow)
			{
				window->on_update();
				on_update();
			}
			window = nullptr;
			return 0;
		}
}
