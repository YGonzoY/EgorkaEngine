#include "VertexArray.hpp"
#include "EgorkaEngineCore/Log.hpp"
#include <glad/glad.h>

namespace EgorkaEngine
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	VertexArray& VertexArray::operator=(VertexArray&& vertex_array) noexcept
	{
		id = vertex_array.id;
		elements_count = vertex_array.elements_count;
		vertex_array.id = 0;
		vertex_array.elements_count = 0;
		return *this;
	}

	VertexArray::VertexArray(VertexArray&& vertex_array) noexcept : id(vertex_array.id), elements_count(vertex_array.elements_count)
	{
		vertex_array.id = 0;
		vertex_array.elements_count = 0;
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::add_buffer(const VertexBuffer& vertex_buffer)
	{
		bind();
		vertex_buffer.bind();


		glEnableVertexAttribArray(elements_count);
		glVertexAttribPointer(elements_count, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		elements_count++;
	}
}