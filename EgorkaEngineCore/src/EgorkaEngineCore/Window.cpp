#include "EgorkaEngineCore/Window.hpp"
#include "EgorkaEngineCore/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace EgorkaEngine
{
    static bool GLFW_initialized = false;

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

            Event event;
            event.width = width;
            event.height = height;

            data.eventCallBackF(event);
            }
        );

        return 0;

        glClearColor(0, 1, 0, 0);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            on_update();
        }
	}
	int Window::shutDown()
	{
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
	}

	void Window::on_update() 
	{
        glClearColor(0, 1, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}