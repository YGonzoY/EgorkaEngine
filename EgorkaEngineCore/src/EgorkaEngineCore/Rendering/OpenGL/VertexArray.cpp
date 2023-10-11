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

	void VertexArray::add_vertex_buffer(const VertexBuffer& vertex_buffer)
	{
		bind();
		vertex_buffer.bind();


		for (const BufferElement& current_element : vertex_buffer.get_layout().get_elements())
		{
			glEnableVertexAttribArray(elements_count);
			glVertexAttribPointer(
				elements_count,
				static_cast<GLint>(current_element.components_count),
				current_element.component_type,
				GL_FALSE,
				static_cast<GLsizei>(vertex_buffer.get_layout().get_stride()),
				reinterpret_cast<const void*>(current_element.offset)
			);
			++elements_count;
		}
	}

	void VertexArray::set_index_buffer(const IndexBuffer& index_buffer)
	{
		bind();
		index_buffer.bind();
		indexes_count = index_buffer.get_count();
	}
}