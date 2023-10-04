#pragma once
#include "VertexBuffer.hpp"

namespace EgorkaEngine
{
	class VertexArray
	{
	private:
		unsigned int id = 0;
		unsigned int elements_count = 0;

	public:
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&& vertex_buffer) noexcept;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&& vertex_buffer) noexcept;

		void add_buffer(const VertexBuffer& verteax_buffer);
		void bind() const;
		static void unbind();

	};
}