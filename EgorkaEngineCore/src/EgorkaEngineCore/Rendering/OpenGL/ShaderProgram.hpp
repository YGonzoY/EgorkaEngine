#pragma once
#include <glm/mat4x4.hpp>

namespace EgorkaEngine
{
	class ShaderProgram
	{
	private:
		bool is_compiled = false;
		unsigned int id = 0;
	public:
		ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
		ShaderProgram(ShaderProgram&&);
		ShaderProgram& operator=(ShaderProgram&&);
		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		void setMatrix4(const char* name, const glm::mat4& matrix) const;
		void bind() const;
		static void unbind();
		bool isCompiled() const { return is_compiled; }
		void setInt(const char* name, const int value) const;
	};
}