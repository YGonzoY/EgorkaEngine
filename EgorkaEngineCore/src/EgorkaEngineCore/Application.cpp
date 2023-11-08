#include "EgorkaEngineCore/Log.hpp"
#include "EgorkaEngineCore/Application.hpp"
#include "EgorkaEngineCore//Window.hpp"
#include "EgorkaEngineCore/Event.hpp"
#include "EgorkaEngineCore/Input.hpp"

#include "EgorkaEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "EgorkaEngineCore/Camera.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "EgorkaEngineCore/Modules/UIModule.hpp"

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>

#include <iostream>


namespace EgorkaEngine
{

	GLfloat positions_colors[] = {
        0.0f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		0.0f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
		0.0f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
		0.0f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f
	};


	GLuint indexes[] = { 0, 1, 2, 3, 2, 1 };

	const char* vertex_shader =
		R"(#version 460
           layout(location = 0) in vec3 vertex_position;
           layout(location = 1) in vec3 vertex_color;
           uniform mat4 model_matrix;
           uniform mat4 view_projection_matrix;
           out vec3 color;
           void main() {
              color = vertex_color;
              gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
           }
        )";


	const char* fragment_shader =
		R"(#version 460
           in vec3 color;
           out vec4 frag_color;
           void main() {
              frag_color = vec4(color, 1.0);
           }
        )";


	std::unique_ptr<ShaderProgram> shader_program;
	std::unique_ptr<IndexBuffer> index_buffer;
	std::unique_ptr<VertexBuffer> positions_color_vbo;
	std::unique_ptr<VertexArray> vao;

	float scale[3] = { 1.f, 1.f, 1.f };
	float rotate = 0.f;
	float translate[3] = { 0.f, 0.f, 0.f };
	float background_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		Application::Application()
		{
			LOG_INFO("starting application");
		}

		Application::~Application()
		{
			LOG_INFO("closing application");
		}

		int Application::start(unsigned int window_w, unsigned int window_h, const char* title)
		{
			window = std::make_unique<Window>(title, window_w, window_h);
			
			event_dispatcher.add_event_listener<EventMouseMoved>(
				[](EventMouseMoved& event)
				{
					LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
				});


			event_dispatcher.add_event_listener<EventWindowClose>(
				[&](EventWindowClose& event)
					{
						LOG_INFO("window closed");
						CloseWindow = true;
					});

			event_dispatcher.add_event_listener<EventWindowResize>(
				[](EventWindowResize& event)
				{
					LOG_INFO("window resized to {0}x{1}", event.height, event.width);
				});

			event_dispatcher.add_event_listener<EventKeyPressed>(
				[](EventKeyPressed& event)
				{
					if (event.key_code <= KeyCodes::KEY_Z)
					{
						if (event.is_repeated)
						{
							LOG_INFO("Key pressed: {0}, repeated", static_cast<char>(event.key_code));
						}
						else
						{
							LOG_INFO("Key pressed: {0}", static_cast<char>(event.key_code));
						}
					}
					Input::PressKey(event.key_code);
				});

			event_dispatcher.add_event_listener<EventKeyReleased>(
				[](EventKeyReleased& event)
				{
					if (event.key_code <= KeyCodes::KEY_Z)
					{
						LOG_INFO("Released {0}", static_cast<char>(event.key_code));
					}
					Input::ReleaseKey(event.key_code);
				});

			event_dispatcher.add_event_listener<EventMouseButtonPressed>(
				[&](EventMouseButtonPressed& event)
				{
					LOG_INFO("[Mouse button pressed: {0}, at ({1}, {2})", static_cast<int>(event.mouse_button), event.x_pos, event.y_pos);
					Input::PressMouseButton(event.mouse_button);
					on_mouse_button_event(event.mouse_button, event.x_pos, event.y_pos, true);
				});

			event_dispatcher.add_event_listener<EventMouseButtonReleased>(
				[&](EventMouseButtonReleased& event)
				{
					LOG_INFO("[Mouse button released: {0}, at ({1}, {2})", static_cast<int>(event.mouse_button), event.x_pos, event.y_pos);
					Input::ReleaseMouseButton(event.mouse_button);
					on_mouse_button_event(event.mouse_button, event.x_pos, event.y_pos, false);
				});


			window->set_eventcallback(
				[&](BaseEvent& event)
				{
					event_dispatcher.dispatch(event);
				});

			shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
			if (!shader_program->isCompiled())
			{
				return false;
			}

			BufferLayout buffer_layout_1_vec_3
			{
				ShaderDataType::Float3
			};

			BufferLayout buffer_layout_2_vec_3
			{
				ShaderDataType::Float3,
				ShaderDataType::Float3
			};

			vao = std::make_unique<VertexArray>();
			positions_color_vbo = std::make_unique<VertexBuffer>(positions_colors, sizeof(positions_colors), buffer_layout_2_vec_3);
			index_buffer = std::make_unique<IndexBuffer>(indexes, sizeof(indexes) / sizeof(GLuint));

			vao->add_vertex_buffer(*positions_color_vbo);
			vao->set_index_buffer(*index_buffer);

			while (!CloseWindow)
			{
				OpenGLRenderer::set_clear_color(background_color[0], background_color[1], background_color[2], background_color[3]);
				OpenGLRenderer::clear();

				shader_program->bind();

				glm::mat4 scale_matrix(scale[0], 0, 0, 0,
					0, scale[1], 0, 0,
					0, 0, scale[2], 0,
					0, 0, 0, 1);

				float rotate_in_radians = glm::radians(rotate);
				glm::mat4 rotate_matrix(cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
					-sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);

				glm::mat4 translate_matrix(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					translate[0], translate[1], translate[2], 1);

				glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
				shader_program->setMatrix4("model_matrix", model_matrix);

				camera.set_projection_mode(perspective_camera ? Camera::Projection::Perspective : Camera::Projection::Orthographic);
				shader_program->setMatrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());


				OpenGLRenderer::draw(*vao);

				UIModule::on_draw_begining();
				bool show = true;
				UIModule::show_exsample_docking_space(&show);
				ImGui::ShowDemoWindow();

				ImGui::Begin("Background Color Window");
				ImGui::ColorEdit4("Background Color", background_color);
				ImGui::SliderFloat3("scale", scale, 0.f, 2.f);
				ImGui::SliderFloat("rotate", &rotate, 0.f, 360.f);
				ImGui::SliderFloat3("translate", translate, -1.f, 1.f);
				ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.f);
				ImGui::SliderFloat3("camera rotation", camera_rotation, 0, 360.f);
				ImGui::Checkbox("Perspective camera", &perspective_camera);
				ImGui::End();

				on_ui_draw();

				UIModule::on_draw_ending();

				window->on_update();
				on_update();
			}
			window = nullptr;
			return 0;
		}

		glm::vec2 Application::get_current_cursor_position() const
		{
			return window->get_current_cursor_position();
		}
}