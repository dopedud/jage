#include "JAGE/renderer.h"

#include "platform/glfw/opengl3/renderer.h"
#include "log.h"

namespace JAGE
{
    namespace ShaderData
    {
        unsigned size(Type type)
        {
            switch (type)
            {
                case Type::None:      return 0;
                case Type::Float:     return 4;
                case Type::Float2:    return 4 * 2;
                case Type::Float3:    return 4 * 3;
                case Type::Float4:    return 4 * 4;
                case Type::Int:       return 4;
                case Type::Int2:      return 4 * 2;
                case Type::Int3:      return 4 * 3;
                case Type::Int4:      return 4 * 4;
                case Type::Mat3:      return 4 * 3 * 3;
                case Type::Mat4:      return 4 * 4 * 4;
                case Type::Bool:      return 1;
            }

            JAGE_MSG_ERROR("Shader error: unknown shader data type. Returning size 0.");

            return 0;
        }
    }

    unsigned BufferElement::component_count() const
    {
        switch (shader_datatype)
        {
            case ShaderData::Type::None:      return 0;
            case ShaderData::Type::Float:     return 1;
            case ShaderData::Type::Float2:    return 2;
            case ShaderData::Type::Float3:    return 3;
            case ShaderData::Type::Float4:    return 4;
            case ShaderData::Type::Int:       return 1;
            case ShaderData::Type::Int2:      return 2;
            case ShaderData::Type::Int3:      return 3;
            case ShaderData::Type::Int4:      return 4;
            case ShaderData::Type::Mat3:      return 3 * 3;
            case ShaderData::Type::Mat4:      return 4 * 4;
            case ShaderData::Type::Bool:      return 1;
        }

        JAGE_MSG_ERROR("Shader error: unknown shader data type. Returning count 0.");

        return 0;
    }

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
    : m_elements { elements }, m_stride {}
    {
        unsigned offset {};

        for (auto& element : m_elements)
        {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

    std::unique_ptr<Texture> Texture::Create(unsigned char* data, unsigned width, unsigned height)
    {
        return std::make_unique<OpenGLTexture>(data, width, height);
    }

    std::unique_ptr<Texture> Texture::Create(const ImageResource& resource)
    {
        return std::make_unique<OpenGLTexture>(resource.data(), resource.width(), resource.height());
    }

    std::unique_ptr<Shader> Shader::Create(std::string_view vertex_str, std::string_view fragment_str)
    {
        return std::make_unique<OpenGLShader>(vertex_str, fragment_str);
    }

    std::unique_ptr<Shader> Shader::Create(const FileResource& vs_resource, const FileResource& fs_resource)
    {
        return std::make_unique<OpenGLShader>(vs_resource.content(), fs_resource.content());
    }

    std::unique_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned size)
    {
        return std::make_unique<OpenGLVertexBuffer>(vertices, size);
    }

    std::unique_ptr<IndexBuffer> IndexBuffer::Create(unsigned* indices, unsigned count)
    {
        return std::make_unique<OpenGLIndexBuffer>(indices, count);
    }

    std::unique_ptr<VertexArray> VertexArray::Create()
    {
        return std::make_unique<OpenGLVertexArray>();
    }
}
