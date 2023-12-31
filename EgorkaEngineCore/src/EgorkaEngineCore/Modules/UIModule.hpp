
#pragma once

struct GLFWwindow;


namespace EgorkaEngine
{
	class UIModule
	{
	public:
		static void on_window_creation(GLFWwindow* _window);
		static void on_window_closing();
		static void on_draw_begining();
		static void on_draw_ending();
	};
}