#pragma once
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

namespace EgorkaEngine
{
	class VertexArray
	{
	private:
		unsigned int id = 0;
		unsigned int elements_count = 0;
		size_t indexes_count = 0;

	public:
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&& vertex_buffer) noexcept;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&& vertex_buffer) noexcept;

		void add_vertex_buffer(const VertexBuffer& vertex_buffer);
		void set_index_buffer(const IndexBuffer& index_buffer);
		void bind() const;
		static void unbind();

		size_t get_indexes_count() const { return indexes_count; }

	};
}