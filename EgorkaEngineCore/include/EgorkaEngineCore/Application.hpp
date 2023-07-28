#pragma once

#include <memory>

namespace EgorkaEngine
{
	class Application
	{
	private:
		std::unique_ptr<class Window> window;
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