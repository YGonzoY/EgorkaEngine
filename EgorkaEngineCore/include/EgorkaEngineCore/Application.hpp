#pragma once

#include <memory>
#include "EgorkaEngineCore/Event.hpp"
#include "EgorkaEngineCore/Camera.hpp"

namespace EgorkaEngine
{
	class Application
	{
	private:
		std::unique_ptr<class Window> window;

		EventDispatcher event_dispatcher;
		bool CloseWindow = false;

		void draw();

	public:
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

		virtual int start(unsigned int window_w, unsigned int window_h, const char* title);

		void close();

		virtual void on_update() {}

		virtual void on_ui_draw() {}

		virtual ~Application();

		virtual void on_mouse_button_event(const MouseButton button_code, const double x_pos, const double y_pos, const bool pressed) {}

		glm::vec2 get_current_cursor_position() const;

		float camera_position[3] = { 0.0f, 0.0f,1.0f };
		float camera_rotation[3] = { 0.0f, 0.0f,0.0f };
		float camera_field_of_view = 60.f;
		float camera_near_plane = 0.1f;
		float camera_far_plane = 100.f;
		bool perspective_camera = true;
		
		Camera camera{ glm::vec3(-5.f, 0.f, 0.f) };
		
	};
}