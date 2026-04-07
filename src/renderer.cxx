#include "JAGE/renderer.h"

#include "platform/glfw/opengl3/renderer.h"
#include "log.h"

namespace JAGE
{
    GraphicsContext::GraphicsContext(Window* window) : m_window { window } {}

    // template<typename T>
    // static function

    namespace Resource
    {
        template<typename T>
        Handle<T>::Handle(ID id, T* resource)
        : m_id { id }, m_resource { resource } {}

        template<typename T> ID Handle<T>::id() const { return m_id; }
        template<typename T> const T* Handle<T>::resource() const { return m_resource; }

        template class Handle<Shader>;

        LogicalPath Base::dir_path() { return LogicalPath{ "resources" }; }
        LogicalPath Shader::dir_path() { return LogicalPath{ "shaders" }; }
        LogicalPath Material::dir_path() { return LogicalPath{ "materials" }; }
        // LogicalPath Texture::dir_path() { return LogicalPath{ "textures" }; }
        // LogicalPath Mesh::dir_path() { return LogicalPath{ "meshes" }; }

        Base::Base(Data::URI uri)
        : m_uri { uri }
        , m_valid {}
        {}

        Data::URI Base::uri() const { return m_uri; }
        bool Base::is_valid() const { return m_valid; }

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

        Material::Material()
        : Base{ URI::undefined() }
        , m_shader {}
        , m_materialdata {}
        , m_albedo_texture {}
        {}

        Material::Material(Shader* shader, const Data::Material* materialdata)
        : Base
        { 
            URI::Builder{ URI::Scheme::GPU }
            .path(Base::dir_path() / Material::dir_path() / "material1")
            .build()
        }
        , m_shader { shader }
        , m_materialdata { materialdata }
        {
            m_albedo_texture = Texture::Create(materialdata->albedo_map);
        }

        Material Material::Create(Shader* shader, const Data::Material* materialdata) { return Material{ shader, materialdata }; }

        Shader*                     Material::shader() const                                            { return m_shader; }
        const Data::Material*       Material::materialdata() const                                      { return m_materialdata; }
        Texture*                    Material::albedo_texture() const                                    { return m_albedo_texture.get(); }
        Material::FaceCullingMode   Material::face_culling_mode() const                                 { return m_face_culling_mode; }
        void                        Material::set_face_culling_mode(Material::FaceCullingMode mode)     { m_face_culling_mode = mode; }
    }


    std::unique_ptr<Texture> Texture::Create(const Data::Image* imagedata)
    { return std::make_unique<OpenGLTexture>(imagedata); }

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

    Resource::Handle<Resource::Shader> Renderer::CreateShader
    (
        std::string_view vertex_str,
        std::string_view fragment_str,
        std::string_view geometry_str = ""
    )
    {
        std::unique_ptr<Resource::Shader> resource
        { 
            Resource::Shader::Create
            (
                URI::undefined(),
                vertex_str,
                fragment_str,
                geometry_str
            )
        };
        return Resource::Handle<Resource::Shader>{ 0, std::move(resource) };
    }

    DebugRenderer::DebugRenderer(Window* window) : m_window { window } {}

    std::unique_ptr<DebugRenderer> DebugRenderer::Create(Window* window)
    { return std::make_unique<OpenGLDebugRenderer>(window); }

    void DebugRenderer::set_vp(glm::mat4 view, glm::mat4 projection)
    { m_view = view; m_projection = projection; }

    BufferElement::BufferElement(Resource::Shader::DataType shader_datatype, std::string_view name, bool normalized)
    : shader_datatype   { shader_datatype }
    , name              { name }
    , size              { Resource::Shader::datatype_size(shader_datatype) }
    , normalized        { normalized } {}

    unsigned BufferElement::component_count() const
    {
        switch (shader_datatype)
        {
            case Resource::Shader::DataType::None:    return 0;
            case Resource::Shader::DataType::Float:   return 1;
            case Resource::Shader::DataType::Float2:  return 2;
            case Resource::Shader::DataType::Float3:  return 3;
            case Resource::Shader::DataType::Float4:  return 4;
            case Resource::Shader::DataType::Int:     return 1;
            case Resource::Shader::DataType::Int2:    return 2;
            case Resource::Shader::DataType::Int3:    return 3;
            case Resource::Shader::DataType::Int4:    return 4;
            case Resource::Shader::DataType::Mat3:    return 3 * 3;
            case Resource::Shader::DataType::Mat4:    return 4 * 4;
            case Resource::Shader::DataType::Bool:    return 1;
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
