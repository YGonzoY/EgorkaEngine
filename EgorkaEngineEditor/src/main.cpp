#include <iostream>
#include <memory>
#include "EgorkaEngineCore/Application.hpp"
#include "EgorkaEngineCore/Input.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

class Editor : public EgorkaEngine::Application
{

	float camera_position[3] = { 0.0f, 0.0f,1.0f };
	float camera_rotation[3] = { 0.0f, 0.0f,0.0f };
	float camera_field_of_view = 60.f;
	float camera_near_plane = 0.1f;
	float camera_far_plane = 100.f;
	bool perspective_camera = true;

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

	void setup_dockspace_menu()
	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton;
		static ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		window_flags |= ImGuiWindowFlags_NoBackground;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", nullptr, window_flags);
		ImGui::PopStyleVar(3);

		ImGuiIO& io = ImGui::GetIO();
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene...", NULL))
				{

				}
				if (ImGui::MenuItem("Open Scene...", NULL))
				{

				}
				if (ImGui::MenuItem("Save Scene...", NULL))
				{

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Exit", NULL))
				{
					close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::End();
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
		setup_dockspace_menu();

		camera_position[0] = camera.get_camera_position().x;
		camera_position[1] = camera.get_camera_position().y;
		camera_position[2] = camera.get_camera_position().z;
		camera_rotation[0] = camera.get_camera_rotation().x;
		camera_rotation[1] = camera.get_camera_rotation().y;
		camera_rotation[2] = camera.get_camera_rotation().z;

		camera_field_of_view = camera.get_field_of_view();
		camera_near_plane = camera.get_near_clip_plane();
		camera_far_plane = camera.get_far_clip_plane();

		ImGui::Begin("Editor");
		ImGui::SliderFloat3("light source position", light_src_position, -10.f, 10.f);
		ImGui::ColorEdit3("light source color", light_src_color);
		if (ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.f))
		{
			camera.set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
		}
		if (ImGui::SliderFloat3("camera rotation", camera_rotation, 0, 360.f))
		{
			camera.set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		}
		if (ImGui::SliderFloat("camera field of view", &camera_field_of_view, 1.f, 120.f))
		{
			camera.set_field_of_view(camera_field_of_view);
		}
		if (ImGui::SliderFloat("camera near clip plane", &camera_near_plane, 0.1f, 10.f))
		{
			camera.set_near_clip_plane(camera_near_plane);
		}
		if (ImGui::SliderFloat("camera far clip plane", &camera_far_plane, 1.f, 100.f))
		{
			camera.set_far_clip_plane(camera_far_plane);
		}
		if (ImGui::Checkbox("Perspective camera", &perspective_camera))
		{
			camera.set_projection_mode(perspective_camera ? EgorkaEngine::Camera::Projection::Perspective : EgorkaEngine::Camera::Projection::Orthographic);
		}
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