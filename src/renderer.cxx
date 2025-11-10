#include "JAGE/renderer.h"

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
}
