
struct GLFWwindow;

namespace EgorkaEngine
{
	class VertexArray;

	class OpenGLRenderer
	{
	public:
		static bool init(GLFWwindow* _window);
		static void draw(const VertexArray& _vertexArray);
		static void set_clear_color(const float r, const float g, const float b, const float a);
		static void clear();
		static void set_viewport(const unsigned int _width, const unsigned int height, const unsigned int _left_offset = 0, const unsigned int bottom_offset = 0);

		static void enable_depth_test();
		static void disable_depth_test();

		static const char* get_vendor_str();
		static const char* get_renderer_str();
		static const char* get_version_str();
	};
}