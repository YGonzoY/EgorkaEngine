#include "EgorkaEngineCore/Window.hpp"
#include "EgorkaEngineCore/Log.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/VertexArray.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include "EgorkaEngineCore//Rendering//OpenGL/ShaderProgram.hpp"

namespace EgorkaEngine
{
    static bool GLFW_initialized = false;

    /*JUST FOR TESTING*/
    /*FURTHER CHANGE THIS TO NORMAL CODE 
    WITH READING FROM FILES AND ETC*/
    GLfloat points[] = {
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    GLfloat positions_colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    const char* vertex_shader =
        "#version 460\n"
        "layout(location = 0) in vec3 vertex_position;"
        "layout(location = 1) in vec3 vertex_color;"
        "out vec3 color;"
        "void main() {"
        "   color = vertex_color;"
        "   gl_Position = vec4(vertex_position, 1.0);"
        "}";

    const char* fragment_shader =
        "#version 460\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main() {"
        "   frag_color = vec4(color, 1.0);"
        "}";


    std::unique_ptr<ShaderProgram> shader_program;
    std::unique_ptr<VertexBuffer> points_vbo;
    std::unique_ptr<VertexBuffer> color_vbo;
    std::unique_ptr<VertexArray> vao_2;

    std::unique_ptr<VertexBuffer> positions_color_vbo;
    std::unique_ptr<VertexArray> vao_1;

    /**/
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

        if (!GLFW_initialized)
        {
            if (!glfwInit())
                return -1;

            static bool GLFW_initialized = true;
        }

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(wData.width, wData.height, wData.title.c_str(), nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
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
                glViewport(0, 0, width, height);
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

        vao_2 = std::make_unique<VertexArray>();
        points_vbo = std::make_unique<VertexBuffer>(points, sizeof(points), buffer_layout_1_vec_3);
        color_vbo = std::make_unique<VertexBuffer>(colors, sizeof(colors), buffer_layout_1_vec_3);

        vao_2->add_buffer(*points_vbo);
        vao_2->add_buffer(*color_vbo);

        BufferLayout buffer_layout_2_vec_3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3
        };

        vao_1 = std::make_unique<VertexArray>();
        positions_color_vbo = std::make_unique<VertexBuffer>(positions_colors, sizeof(positions_colors), buffer_layout_2_vec_3);

        vao_1->add_buffer(*positions_color_vbo);

        return 0;

	}
	int Window::shutDown()
	{
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
	}

	void Window::on_update() 
	{
        glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        //shader_program->bind();
        //vao_2->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);


        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_width());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        ImGui::Begin("Background Color Window");
        ImGui::ColorEdit4("Background Color", background_color);

        static bool use_2_buffers = true;
        ImGui::Checkbox("2 Buffers", &use_2_buffers);
        if (use_2_buffers)
        {
            shader_program->bind();
            vao_2->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        else
        {
            shader_program->bind();
            vao_1->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}