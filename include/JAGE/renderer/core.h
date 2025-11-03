#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API Renderer
    {
    public:
        void static Render();
    };

    namespace ShaderData
    {
        enum class Type : uint8_t
        {
            None = 0,
            Float, Float2, Float3, Float4,
            Int, Int2, Int3, Int4,
            Mat3, Mat4,
            Bool
        };

        unsigned int JAGE_API size(Type type);
    }

    class JAGE_API Shader
    {
    public:
        static Shader* Create(std::string_view vertex_str, std::string_view fragment_str);
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
    protected:
        unsigned int rendererID;
    };

    struct JAGE_API BufferElement
    {
        ShaderData::Type shader_datatype;
        std::string name;
        unsigned int size;
        unsigned int offset;
        bool normalized;

        BufferElement() = default;
        BufferElement(ShaderData::Type shader_datatype, std::string_view name, bool normalized = false);

        unsigned int component_count() const;
    };

    class JAGE_API BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        const std::vector<BufferElement>& elements() const { return m_elements; };
        unsigned int stride() const { return m_stride; }
    private:
        std::vector<BufferElement> m_elements;
        unsigned int m_stride;
    };

    class JAGE_API VertexBuffer
    {
    public:
        static VertexBuffer* Create(float* vertices, unsigned int size);
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        const BufferLayout& layout() { return m_layout; }
        void set_layout(const BufferLayout& layout) { m_layout = layout; }
    protected:
        unsigned int rendererID;
        BufferLayout m_layout;
    };

    class JAGE_API IndexBuffer
    {
    public:
        static IndexBuffer* Create(unsigned int* indices, unsigned int count);
        IndexBuffer(unsigned int count);
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        unsigned int count() const { return m_count; }
    protected:
        unsigned int rendererID;
        unsigned int m_count;
    };

    class JAGE_API VertexArray
    {
    public:
        static VertexArray* Create();
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void add_vbuffer(const std::shared_ptr<VertexBuffer>& vbuffer) = 0;
        virtual void set_ibuffer(const std::shared_ptr<IndexBuffer>& ibuffer) = 0;
    protected:
        unsigned int rendererID;

        std::vector<std::shared_ptr<VertexBuffer>> vbuffers {};
        std::shared_ptr<IndexBuffer> ibuffer;
    };
}
