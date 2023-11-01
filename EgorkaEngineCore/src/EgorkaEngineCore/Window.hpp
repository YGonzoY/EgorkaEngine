#pragma once
#include <string>
#include <functional>

#include "EgorkaEngineCore/Event.hpp"

struct GLFWwindow;

namespace EgorkaEngine
{
	class Window
	{
	public:
		using EventCallBackF = std::function<void(BaseEvent&)>;

		Window(std::string _title,const unsigned int _height, const unsigned int _width);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		void on_update();

		unsigned int get_width() const { return wData.width; };
		unsigned int get_height() const { return wData.height; };

		~Window();

		void  set_eventcallback(const EventCallBackF& callback)
		{
			wData.eventCallBackF = callback;
		}

	private:
		struct WindowData
		{
			unsigned int width;
			unsigned int height;
			std::string title;
			EventCallBackF eventCallBackF;
		};
		WindowData wData;

		GLFWwindow* window = nullptr;

		int init();
		int shutDown();
	};
}