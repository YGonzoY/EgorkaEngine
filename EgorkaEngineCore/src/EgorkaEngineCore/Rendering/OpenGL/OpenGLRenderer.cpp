
#include "OpenGLRenderer.hpp"
#include "VertexArray.hpp"
#include "EgorkaEngineCore/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace EgorkaEngine
{
	bool OpenGLRenderer::init(GLFWwindow* _window)
	{
		glfwMakeContextCurrent(_window);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			LOG_CRITICAL("Failed to initialize GLAD");
			return false;
		}

		LOG_INFO("OpenGL context initialized:");
		LOG_INFO("\t Vendor: {0}", get_vendor_str());
		LOG_INFO("\t Renderer: {0}", get_renderer_str());
		LOG_INFO("\t Version: {0}", get_version_str());

		return true;
	}

    void OpenGLRenderer::draw(const VertexArray& _vertexArray)
    {
        _vertexArray.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_vertexArray.get_indexes_count()), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::set_clear_color(const float r, const float g, const float b, const float a)
    {
        glClearColor(r, g, b, a);
    }

    void OpenGLRenderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::set_viewport(const unsigned int _width, const unsigned int _height, const unsigned int _left_offset, const unsigned int _bottom_offset)
    {
        glViewport(_left_offset, _bottom_offset, _width, _height);
    }

    void OpenGLRenderer::enable_depth_test()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::disable_depth_test()
    {
        glDisable(GL_DEPTH_TEST);
    }

    const char* OpenGLRenderer::get_vendor_str()
    {
        return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    }

    const char* OpenGLRenderer::get_renderer_str()
    {
        return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    }

    const char* OpenGLRenderer::get_version_str()
    {
        return reinterpret_cast<const char*>(glGetString(GL_VERSION));
    }

}