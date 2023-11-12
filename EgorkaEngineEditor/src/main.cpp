#include <iostream>
#include <memory>
#include "EgorkaEngineCore/Application.hpp"
#include "EgorkaEngineCore/Input.hpp"
#include <imgui/imgui.h>

class Editor : public EgorkaEngine::Application
{
	double m_initial_mouse_pos_x = 0.0;
	double m_initial_mouse_pos_y = 0.0;

	virtual void on_update() override
	{
		//bool move_camera = false;
		glm::vec3 movement_delta{ 0, 0, 0 };
		glm::vec3 rotation_delta{ 0, 0, 0 };

		if(EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_W))
		{
			movement_delta.x += 0.05f;
			//move_camera = true;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_S))
		{
			movement_delta.x -= 0.05f;
			//move_camera = true;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_D))
		{
			movement_delta.y += 0.05f;
			//move_camera = true;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_A))
		{
			movement_delta.y -= 0.05f;
			//move_camera = true;
		}

		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_R))
		{
			movement_delta.z += 0.05f;
			//move_camera = true;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_F))
		{
			movement_delta.z -= 0.05f;
			//move_camera = true;
		}


		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_UP))
		{
			rotation_delta.y -= 0.5f;
			//move_camera = true;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_DOWN))
		{
			rotation_delta.y += 0.5f;
			//move_camera = true;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_RIGHT))
		{
			rotation_delta.z -= 0.5f;
			//move_camera = true;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_LEFT))
		{
			rotation_delta.z += 0.5f;
			//move_camera = true;

		}

		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_Q))
		{
			rotation_delta.x += 0.5f;
			//move_camera = true;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_E))
		{
			rotation_delta.x -= 0.5f;
			//move_camera = true;
		}

		//if (move_camera)
		//{
			//camera.add_movement_and_rotation(movement_delta, rotation_delta);
		//}

		if (EgorkaEngine::Input::IsMouseButtonPressed(EgorkaEngine::MouseButton::MOUSE_BUTTON_RIGHT))
		{
			glm::vec2 current_cursor_position = get_current_cursor_position();
			if (EgorkaEngine::Input::IsMouseButtonPressed(EgorkaEngine::MouseButton::MOUSE_BUTTON_LEFT))
			{
				camera.move_right(static_cast<float>(current_cursor_position.x - m_initial_mouse_pos_x) / 100.f);
				camera.move_up(static_cast<float>(m_initial_mouse_pos_y - current_cursor_position.y) / 100.f);
			}
			else
			{
				rotation_delta.z += static_cast<float>(m_initial_mouse_pos_x - current_cursor_position.x) / 5.f;
				rotation_delta.y -= static_cast<float>(m_initial_mouse_pos_y - current_cursor_position.y) / 5.f;
			}
			m_initial_mouse_pos_x = current_cursor_position.x;
			m_initial_mouse_pos_y = current_cursor_position.y;
		}

		if (EgorkaEngine::Input::IsScrolled())
		{
			movement_delta.x += 0.1f*EgorkaEngine::Input::ScrollZoom();
			EgorkaEngine::Input::StopScroll();
		}

		camera.add_movement_and_rotation(movement_delta, rotation_delta);
	}

	virtual void on_mouse_button_event(const EgorkaEngine::MouseButton button_code,
		const double x_pos,
		const double y_pos,
		const bool pressed) override
	{
		m_initial_mouse_pos_x = x_pos;
		m_initial_mouse_pos_y = y_pos;
	}

	virtual void on_ui_draw() override
	{
		camera_position[0] = camera.get_camera_position().x;
		camera_position[1] = camera.get_camera_position().y;
		camera_position[2] = camera.get_camera_position().z;
		camera_rotation[0] = camera.get_camera_rotation().x;
		camera_rotation[1] = camera.get_camera_rotation().y;
		camera_rotation[2] = camera.get_camera_rotation().z;

		ImGui::Begin("Editor");
		if (ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.f))
		{
			camera.set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
		}
		if (ImGui::SliderFloat3("camera rotation", camera_rotation, 0, 360.f))
		{
			camera.set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		}
		ImGui::Checkbox("Perspective camera", &perspective_camera);
		ImGui::End();
	}

	int frame = 0;
};



int main()
{
	auto editor = std::make_unique<Editor>();

	int returnCode = editor->start(1024, 768, "Editor");

	return returnCode;
}