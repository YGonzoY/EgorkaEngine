#include "EgorkaEngineCore/Window.hpp"
#include "EgorkaEngineCore/Log.hpp"

#include "EgorkaEngineCore/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "EgorkaEngineCore/Modules/UIModule.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>


namespace EgorkaEngine
{

	Window::Window(std::string _title, const unsigned int _height, const unsigned int _width)
	{
        wData.title = _title;
        wData.height = _height;
        wData.width = _width;
		int result = init();
	}
	Window::~Window()
	{
		shutDown();
	}

	int Window::init()
	{

        glfwSetErrorCallback([](int error_code, const char* description) {LOG_CRITICAL("GLFW error: {0}", description); });
        if (!glfwInit())
        {
            LOG_CRITICAL("can not initialize GLFW");
            return -1;
        }

        window = glfwCreateWindow(wData.width, wData.height, wData.title.c_str(), nullptr, nullptr);
        if (!window)
        {
            return -2;
        }

        if(!OpenGLRenderer::init(window))
        {
            LOG_CRITICAL("Can not initialize GLAD");
            return -3;
        }

        glfwSetWindowUserPointer(window, &wData);

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int code, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                switch (action)
                {
                case GLFW_PRESS:
                {
                    EventKeyPressed event(static_cast<KeyCodes>(key), false);
                    data.eventCallBackF(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    EventKeyReleased event(static_cast<KeyCodes>(key));
                    data.eventCallBackF(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    EventKeyPressed event(static_cast<KeyCodes>(key), true);
                    data.eventCallBackF(event);
                    break;
                }
                default:
                    break;
                }
            }
        );

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
                OpenGLRenderer::set_viewport(width, height);
            }
        );

        glfwSetMouseButtonCallback(window,
            [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                double x_pos;
                double y_pos;
                glfwGetCursorPos(window, &x_pos, &y_pos);
                switch (action)
                {
                case GLFW_PRESS:
                {
                    EventMouseButtonPressed event(static_cast<MouseButton>(button), x_pos, y_pos);
                    data.eventCallBackF(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    EventMouseButtonReleased event(static_cast<MouseButton>(button), x_pos, y_pos);
                    data.eventCallBackF(event);
                    break;
                }
                }
            }
        );

        glfwSetScrollCallback(window, 
            [](GLFWwindow* window, double xoffset, double yoffset)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                EventScrolled event(xoffset, yoffset);
                data.eventCallBackF(event);
            }
        );


        UIModule::on_window_creation(window);


        return 0;

	}

    glm::vec2 Window::get_current_cursor_position() const
    {
        double x_pos;
        double y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);
        return { x_pos, y_pos };
    }

	int Window::shutDown()
	{
        UIModule::on_window_closing();
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
	}

	void Window::on_update() 
	{
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}