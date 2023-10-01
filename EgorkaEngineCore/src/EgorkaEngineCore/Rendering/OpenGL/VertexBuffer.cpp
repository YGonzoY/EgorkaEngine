#include "VertexBuffer.hpp"
#include "EgorkaEngineCore/Log.hpp"
#include <glad/glad.h>

namespace EgorkaEngine
{
	constexpr GLenum usage_to_glenum(const VertexBuffer::EUsage usage)
	{
		switch (usage)
		{
		case VertexBuffer::EUsage::Static:
			return GL_STATIC_DRAW;

		case VertexBuffer::EUsage::Dynamic:
			return GL_DYNAMIC_DRAW;

		case VertexBuffer::EUsage::Stream:
			return GL_STREAM_DRAW;
		}
	}

	VertexBuffer::VertexBuffer(const void* data, const size_t size, const EUsage usage)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage_to_glenum(usage));
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
	{
		id = vertexBuffer.id;
		vertexBuffer.id = 0;
		return *this;
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
	{
		id = vertexBuffer.id;
		vertexBuffer.id = 0;
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}