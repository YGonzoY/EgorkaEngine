#include "EgorkaEngineCore/Window.hpp"
#include "EgorkaEngineCore/Log.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "EgorkaEngineCore/Camera.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/OpenGLRenderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include "EgorkaEngineCore//Rendering//OpenGL/ShaderProgram.hpp"

#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>

namespace EgorkaEngine
{
    static bool GLFW_initialized = false;

    /*JUST FOR TESTING*/
    /*FURTHER CHANGE THIS TO NORMAL CODE 
    WITH READING FROM FILES AND ETC*/

    GLfloat positions_colors[] = {
       -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
    };

    GLuint indexes[] = {0, 1, 2, 3, 2, 1};

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

    float camera_position[3] = { 0.f, 0.f, 1.f };
    float camera_rotation[3] = { 0.f, 0.f, 0.f };
    bool perspective_camera = false;
    Camera camera;

	Window::Window(std::string _title, const unsigned int _height, const unsigned int _width)
	{
        wData.title = _title;
        wData.height = _height;
        wData.width = _width;
		int result = init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
	}
	Window::~Window()
	{
		shutDown();
	}

	int Window::init()
	{

        glfwSetErrorCallback([](int error_code, const char* description) {LOG_CRITICAL("GLFW error: {0}", description); });
        //if (!GLFW_initialized)
        //{
        if (!glfwInit())
        {
            //return -1;
            LOG_CRITICAL("can not initialize GLFW");
            //static bool GLFW_initialized = true;
            return -1;
        //}
        }

        window = glfwCreateWindow(wData.width, wData.height, wData.title.c_str(), nullptr, nullptr);
        if (!window)
        {
            //glfwTerminate();
            return -2;
        }

        //glfwMakeContextCurrent(window);

        //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        if(!OpenGLRenderer::init(window))
        {
            LOG_CRITICAL("Can not initialize GLAD");
            return -3;
        }

        glfwSetWindowUserPointer(window, &wData);

        glfwSetWindowSizeCallback(window, 
            [](GLFWwindow* window, int width, int height)
            {

            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.width = width;
            data.height = height;

            EventWindowResize event(width, height);
            data.eventCallBackF(event);
            }
        );

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) 
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                EventMouseMoved event(x, y);
                data.eventCallBackF(event);
            }
        );

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                EventWindowClose event;
                data.eventCallBackF(event);
            }
        );

        glfwSetFramebufferSizeCallback(window,
            [](GLFWwindow* pWindow, int width, int height)
            {
                //glViewport(0, 0, width, height);
                OpenGLRenderer::set_viewport(width, height);
            }
        );


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


        return 0;

	}
	int Window::shutDown()
	{
        if (ImGui::GetCurrentContext())
        {
            ImGui::DestroyContext();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
	}

	void Window::on_update() 
	{
        //glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);
        //glClear(GL_COLOR_BUFFER_BIT);

        OpenGLRenderer::set_clear_color(background_color[0], background_color[1], background_color[2], background_color[3]);
        OpenGLRenderer::clear();

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_width());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Background Color Window");
        ImGui::ColorEdit4("Background Color", background_color);
        ImGui::SliderFloat3("scale", scale, 0.f, 2.f);
        ImGui::SliderFloat("rotate", &rotate, 0.f, 360.f);
        ImGui::SliderFloat3("translate", translate, -1.f, 1.f);

        ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.f);
        ImGui::SliderFloat3("camera rotation", camera_rotation, 0, 360.f);
        ImGui::Checkbox("Perspective camera", &perspective_camera);

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

        camera.set_position_rotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
            glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
        camera.set_projection_mode(perspective_camera ? Camera::Projection::Perspective : Camera::Projection::Orthographic);
        shader_program->setMatrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());

        //vao->bind();
        //glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vao->get_indexes_count()), GL_UNSIGNED_INT, nullptr);

        OpenGLRenderer::draw(*vao);

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}