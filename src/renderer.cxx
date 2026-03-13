#include "JAGE/renderer.h"

#include "platform/glfw/opengl3/renderer.h"
#include "log.h"

namespace JAGE
{
    GraphicsContext::GraphicsContext(Window* window) : m_window { window } {}

    std::unique_ptr<Shader> Shader::Create
    (
        std::string_view vertex_str,
        std::string_view fragment_str,
        std::string_view geometry_str
    )
    { return std::make_unique<OpenGLShader>(vertex_str, fragment_str, geometry_str); }

    unsigned Shader::datatype_size(Shader::DataType datatype)
    {
        switch (datatype)
        {
            case DataType::None:      return 0;
            case DataType::Float:     return 4;
            case DataType::Float2:    return 4 * 2;
            case DataType::Float3:    return 4 * 3;
            case DataType::Float4:    return 4 * 4;
            case DataType::Int:       return 4;
            case DataType::Int2:      return 4 * 2;
            case DataType::Int3:      return 4 * 3;
            case DataType::Int4:      return 4 * 4;
            case DataType::Mat3:      return 4 * 3 * 3;
            case DataType::Mat4:      return 4 * 4 * 4;
            case DataType::Bool:      return 1;
        }

        JAGE_MSG_ERROR("Shader error: unknown shader data type. Returning size 0.");

        return 0;
    }

    std::unique_ptr<Texture> Texture::Create(const Data::Image* imagedata)
    { return std::make_unique<OpenGLTexture>(imagedata); }

    Material::Material()
    : m_shader {}
    , m_materialdata {}
    , m_albedo_texture {}
    {}

    Material::Material(Shader* shader, const Data::Material* materialdata)
    : m_shader { shader }, m_materialdata { materialdata }
    {
        m_albedo_texture = Texture::Create(materialdata->albedo_map);
    }

    Shader* Material::shader() const { return m_shader; }
    const Data::Material* Material::materialdata() const { return m_materialdata; }
    Texture* Material::albedo_texture() const { return m_albedo_texture.get(); }
    Material::FaceCullingMode Material::face_culling_mode() const { return m_face_culling_mode; }
    void Material::set_face_culling_mode(Material::FaceCullingMode mode) { m_face_culling_mode = mode; }

    Mesh::Mesh(const Data::Mesh* meshdata) : m_meshdata { meshdata } {} 

    std::unique_ptr<Mesh> Mesh::Create(const Data::Mesh* meshdata)
    { return std::make_unique<OpenGLMesh>(meshdata); }

    Renderer::Renderer(Window* window) : m_window { window } {}

    std::unique_ptr<Renderer> Renderer::Create(Window* window)
    { return std::make_unique<OpenGLRenderer>(window); }

    void Renderer::set_vp(const glm::mat4& view, const glm::mat4& projection)
    { m_view = view; m_projection = projection; }

    const glm::mat4& Renderer::view() const { return m_view; }
    const glm::mat4& Renderer::projection() const { return m_projection; }

    DebugRenderer::DebugRenderer(Window* window) : m_window { window } {}

    std::unique_ptr<DebugRenderer> DebugRenderer::Create(Window* window)
    { return std::make_unique<OpenGLDebugRenderer>(window); }

    void DebugRenderer::set_vp(glm::mat4 view, glm::mat4 projection)
    { m_view = view; m_projection = projection; }

    BufferElement::BufferElement(Shader::DataType shader_datatype, std::string_view name, bool normalized)
    : shader_datatype   { shader_datatype }
    , name              { name }
    , size              { Shader::datatype_size(shader_datatype) }
    , normalized        { normalized } {}

    unsigned BufferElement::component_count() const
    {
        switch (shader_datatype)
        {
            case Shader::DataType::None:    return 0;
            case Shader::DataType::Float:   return 1;
            case Shader::DataType::Float2:  return 2;
            case Shader::DataType::Float3:  return 3;
            case Shader::DataType::Float4:  return 4;
            case Shader::DataType::Int:     return 1;
            case Shader::DataType::Int2:    return 2;
            case Shader::DataType::Int3:    return 3;
            case Shader::DataType::Int4:    return 4;
            case Shader::DataType::Mat3:    return 3 * 3;
            case Shader::DataType::Mat4:    return 4 * 4;
            case Shader::DataType::Bool:    return 1;
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

    const std::vector<BufferElement>& BufferLayout::elements() const { return m_elements; };
    unsigned BufferLayout::stride() const { return m_stride; }
}
