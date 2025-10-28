#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API Renderer
    {
    };

    class JAGE_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);

    private:
        uint32_t rendererID;
    };

    class JAGE_API IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        uint32_t count() const { return m_count; }

        static IndexBuffer* Create(uint32_t indices, uint32_t count);

    private:
        uint32_t rendererID;
        uint32_t m_count;
    };
}
