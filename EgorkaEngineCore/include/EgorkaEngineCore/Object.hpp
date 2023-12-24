#pragma once

#include "EgorkaEngineCore/Rendering/OpenGL/Texture.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "EgorkaEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

namespace EgorkaEngine
{
	class Object
	{
	private:
		GLfloat* positions_normals_uvs;
		GLuint* indexes;
		const char* vertex_shader;
		const char* fragment_shader;

		std::unique_ptr<ShaderProgram> shader_program;
		std::unique_ptr<IndexBuffer> index_buffer;
		std::unique_ptr<VertexBuffer> positions_color_vbo;
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<Texture2D>* textures;

	public:
		Object(GLfloat* positions_normals_uvs, GLuint* indexes, std::unique_ptr<Texture2D>* textures);
		~Object();
		void set_texture(std::unique_ptr<Texture2D>* textures);
		void transform();
		void rotate();
		void move();
	};
}