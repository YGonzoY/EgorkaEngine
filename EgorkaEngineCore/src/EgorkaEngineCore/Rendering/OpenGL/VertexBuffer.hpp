#pragma once

namespace EgorkaEngine
{
	class VertexBuffer
	{
	private:
		unsigned int id = 0;

	public:
		enum class EUsage
		{
			Static,
			Dynamic,
			Stream
		};

		VertexBuffer(const void* data, const size_t, const EUsage usage = VertexBuffer::EUsage::Static);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&& vertexbuffer) noexcept;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&& vertexbuffer) noexcept;

		void bind() const;
		static void unbind();
	};
}