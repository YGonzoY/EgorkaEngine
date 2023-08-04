#pragma once

#include <memory>
#include "EgorkaEngineCore/Event.hpp"

namespace EgorkaEngine
{
	class Application
	{
	private:
		std::unique_ptr<class Window> window;

		EventDispatcher event_dispatcher;
		bool CloseWindow = false;
	public:
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

		virtual int start(unsigned int window_w, unsigned int window_h, const char* title);
		virtual void on_update() {}

		virtual ~Application();

		
	};
}