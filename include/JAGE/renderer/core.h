#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API Renderer
    {
    };

    class JAGE_API Shader
    {
    public:
        static std::unique_ptr<Shader> Create(std::string_view vertex_str, std::string_view fragment_str);
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    protected:
        uint32_t rendererID;
    };

    class JAGE_API VertexBuffer
    {
    public:
        static std::unique_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    protected:
        uint32_t rendererID;
    };

    class JAGE_API IndexBuffer
    {
    public:
        static std::unique_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
        IndexBuffer(uint32_t count);
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        uint32_t count() const { return m_count; }
    protected:
        uint32_t rendererID;
        uint32_t m_count;
    };
}
