#pragma once

#include <vector>

namespace EgorkaEngine
{
	enum class ShaderDataType
	{
		Float,
			Float2,
			Float3,
			Float4,
			Int,
			Int2,
			Int3,
			Int4,
	};

	struct BufferElement
	{
		ShaderDataType type;
		uint32_t component_type;
		size_t components_count;
		size_t size;
		size_t offset;

		BufferElement(const ShaderDataType type);
	};


	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<BufferElement> _elements)
			: elements(std::move(_elements))
		{
			size_t offset = 0;
			stride = 0;
			for (auto& element : elements)
			{
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}

		const std::vector<BufferElement>& get_elements() const { return elements; }
		size_t get_stride() const { return stride; }

	private:
		std::vector<BufferElement> elements;
		size_t stride = 0;
	};


	class VertexBuffer
	{
	private:
		unsigned int id = 0;
		BufferLayout buffer_layout;

	public:
		enum class EUsage
		{
			Static,
			Dynamic,
			Stream
		};

		VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout, const EUsage usage = VertexBuffer::EUsage::Static);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&& vertexbuffer) noexcept;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&& vertexbuffer) noexcept;

		void bind() const;
		static void unbind();

		const BufferLayout& get_layout() const { return buffer_layout; }
	};
}