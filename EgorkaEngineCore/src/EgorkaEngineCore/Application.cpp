#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include "EgorkaEngineCore/Application.hpp"

namespace EgorkaEngine
{
		Application::Application()
		{

		}

		Application::~Application()
		{

		}

		int Application::start(unsigned int window_w, unsigned int window_h, const char* title)
		{
            std::cout << "Hello from Core";

            GLFWwindow* window;

            /* Initialize the library */
            if (!glfwInit())
                return -1;

            /* Create a windowed mode window and its OpenGL context */
            window = glfwCreateWindow(window_w, window_h, title, NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                return -1;
            }

            /* Make the window's context current */
            glfwMakeContextCurrent(window);

            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                /* Render here */
                //glClear(GL_COLOR_BUFFER_BIT);

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();

                on_update();
            }

            glfwTerminate();
            return 0;
		}
}
