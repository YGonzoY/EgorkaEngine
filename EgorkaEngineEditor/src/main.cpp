#include <iostream>
#include <memory>
#include "EgorkaEngineCore/Application.hpp"
#include <imgui/imgui.h>

class Editor : public EgorkaEngine::Application
{
	virtual void on_update() override
	{
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