#include <iostream>
#include <memory>
#include "EgorkaEngineCore/Application.hpp"
#include "EgorkaEngineCore/Input.hpp"
#include <imgui/imgui.h>

class Editor : public EgorkaEngine::Application
{
	virtual void on_update() override
	{
		if(EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_W))
		{
			camera_position[2] -= 0.01f;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_S))
		{
			camera_position[2] += 0.01f;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_D))
		{
			camera_position[0] += 0.01f;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_A))
		{
			camera_position[0] -= 0.01f;
		}

		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_R))
		{
			camera_position[1] += 0.01f;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_F))
		{
			camera_position[1] -= 0.01f;
		}


		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_UP))
		{
			camera_rotation[0] += 0.5f;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_DOWN))
		{
			camera_rotation[0] -= 0.5f;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_RIGHT))
		{
			camera_rotation[1] -= 0.5f;
		}
		if (EgorkaEngine::Input::IsKeyPressed(EgorkaEngine::KeyCodes::KEY_LEFT))
		{
			camera_rotation[1] += 0.5f;
		}
	}

	virtual void on_ui_draw() override
	{
		ImGui::Begin("Editor");
		ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.f);
		ImGui::SliderFloat3("camera rotation", camera_rotation, 0, 360.f);
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