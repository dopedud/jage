#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API Renderer
    {
    };

    enum class ShaderDataType : uint8_t
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        Bool
    };

    unsigned int JAGE_API shader_datatype_size(ShaderDataType type);

    struct JAGE_API BufferElement
    {
        ShaderDataType shader_datatype;
        std::string name;
        unsigned int size;
        unsigned int offset;

        BufferElement(ShaderDataType type, std::string_view name);
    };

    class JAGE_API BufferLayout
    {
    public:
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        const std::vector<BufferElement>& elements() const { return m_elements; };

        std::vector<BufferElement>::iterator elements_begin() { return m_elements.begin(); }
        std::vector<BufferElement>::iterator elements_end() { return m_elements.end(); }
    private:
        std::vector<BufferElement> m_elements;
        unsigned int stride;
    };

    class JAGE_API Shader
    {
    public:
        static std::unique_ptr<Shader> Create(std::string_view vertex_str, std::string_view fragment_str);
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    protected:
        unsigned int rendererID;
    };

    class JAGE_API VertexBuffer
    {
    public:
        static std::unique_ptr<VertexBuffer> Create(float* vertices, unsigned int size);
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        const BufferLayout& layout() { return m_layout; }
        void set_layout(const BufferLayout& layout) { m_layout = layout; }
    protected:
        unsigned int rendererID;
        BufferLayout m_layout;
    };

    class JAGE_API IndexBuffer
    {
    public:
        static std::unique_ptr<IndexBuffer> Create(unsigned int* indices, unsigned int count);
        IndexBuffer(unsigned int count);
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        unsigned int count() const { return m_count; }
    protected:
        unsigned int rendererID;
        unsigned int m_count;
    };
}
