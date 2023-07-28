#pragma once
#include <string>

struct GLFWwindow;

namespace EgorkaEngine
{
	class Window
	{
	private:
		unsigned int width;
		unsigned int height;
		std::string title;
		GLFWwindow* window;

		int init();
		int shutDown();
	public:
		Window(std::string _title,const unsigned int _height, const unsigned int _width);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		void on_update();

		unsigned int get_width() const { return width; };
		unsigned int get_height() const { return height; };

		~Window();
	};
}