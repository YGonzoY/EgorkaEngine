#pragma once
#include "VertexBuffer.hpp"

namespace EgorkaEngine {

    class IndexBuffer
    {
    private:
        unsigned int id = 0;
        size_t count;

    public:

        IndexBuffer(const void* data, const size_t count, const VertexBuffer::EUsage usage = VertexBuffer::EUsage::Static);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer&& index_buffer) noexcept;
        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer& operator=(IndexBuffer&& index_buffer) noexcept;

        void bind() const;
        static void unbind();
        size_t get_count() const { return count; }
    };

}