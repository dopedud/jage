#pragma once

#include "JAGE/core.h"
#include "JAGE/resources/core.h"

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

        unsigned JAGE_API size(Type type);
    }

    class JAGE_API Texture
    {
    public:
        static Texture* Create(unsigned char* data, unsigned width, unsigned height);
        // static Texture* Create(const ImageResource& resource);
        virtual ~Texture() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    protected:
        unsigned textureID;
    };

    class JAGE_API Shader
    {
    public:
        static Shader* Create(std::string_view vertex_str, std::string_view fragment_str);
        // static Shader* Create(const ShaderResource& resource);
        virtual ~Shader() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    protected:
        unsigned shaderID;
    };

    struct JAGE_API BufferElement
    {
        ShaderData::Type shader_datatype;
        std::string name;
        unsigned size;
        unsigned offset;
        bool normalized;

        BufferElement() = default;
        BufferElement(ShaderData::Type shader_datatype, std::string_view name, bool normalized = false)
        : shader_datatype   { shader_datatype }
        , name              { name }
        , size              { ShaderData::size(shader_datatype) }
        , normalized        { normalized }
        {}

        unsigned component_count() const;
    };

    class JAGE_API BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        const std::vector<BufferElement>& elements() const { return m_elements; };
        unsigned stride() const { return m_stride; }
    private:
        std::vector<BufferElement> m_elements;
        unsigned m_stride;
    };

    class JAGE_API VertexBuffer
    {
    public:
        static VertexBuffer* Create(float* vertices, unsigned size);
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        const BufferLayout& layout() const { return m_layout; }
        void set_layout(const BufferLayout& layout) { m_layout = layout; }
    protected:
        unsigned rendererID;
        BufferLayout m_layout;
    };

    class JAGE_API IndexBuffer
    {
    public:
        static IndexBuffer* Create(unsigned* indices, unsigned count);
        IndexBuffer(unsigned count) : m_count { count } {}
        virtual ~IndexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        unsigned count() const { return m_count; }
    protected:
        unsigned rendererID;
        unsigned m_count;
    };

    class JAGE_API VertexArray
    {
    public:
        static VertexArray* Create();
        virtual ~VertexArray() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void add_vbuffer(const std::shared_ptr<VertexBuffer>& vbuffer) = 0;
        virtual void set_ibuffer(const std::shared_ptr<IndexBuffer>& ibuffer) = 0;
    protected:
        unsigned rendererID;

        std::vector<std::shared_ptr<VertexBuffer>> vbuffers {};
        std::shared_ptr<IndexBuffer> ibuffer;
    };
}
