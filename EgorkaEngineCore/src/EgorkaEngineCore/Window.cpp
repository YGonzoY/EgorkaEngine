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

        UIModule::on_window_creation(window);


        return 0;

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