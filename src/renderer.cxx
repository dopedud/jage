#include "JAGE/renderer.h"

#include "platform/glfw/opengl3/renderer.h"
#include "log.h"

namespace JAGE
{
    GraphicsContext::GraphicsContext(Window* window) : m_window { window } {}

    template<typename T>
    static u64 instance_counter() { static u64 counter; return counter++; }

    namespace Resource
    {
        template<typename T>
        Handle<T>::Handle(ID id, T* resource) : m_id { id }, m_resource { resource } {}

        template<typename T> ID Handle<T>::id() const { return m_id; }
        template<typename T> T* Handle<T>::resource() const { return m_resource; }
        template<typename T> bool Handle<T>::is_valid() const { return m_resource != nullptr; }

        template class Handle<Shader>;

        LogicalPath Base::dir_path()        { return LogicalPath{ "resources" }; }
        LogicalPath Shader::dir_path()      { return LogicalPath{ "shaders" }; }
        LogicalPath Texture::dir_path()     { return LogicalPath{ "textures" }; }
        LogicalPath Material::dir_path()    { return LogicalPath{ "materials" }; }
        // LogicalPath Mesh::dir_path() { return LogicalPath{ "meshes" }; }

        Base::Base(Data::URI uri)
        : m_uri { uri }
        , m_valid {}
        {}

        Data::URI Base::uri() const { return m_uri; }
        bool Base::is_valid() const { return m_valid; }

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

        Shader::Shader(Data::URI uri) : Base{ uri } {}

        std::unique_ptr<Shader> Shader::Create
        (
            Data::URI uri,
            std::string_view vs_str,
            std::string_view fs_str,
            std::string_view gs_str
        )
        { return std::make_unique<OpenGLShader>(uri, vs_str, fs_str, gs_str); }

        Texture::Texture(Data::URI uri) : Base{ uri } {}

        std::unique_ptr<Texture> Texture::Create(Data::URI uri, const Data::Image* imagedata)
        { return std::make_unique<OpenGLTexture>(uri, imagedata); }

        Material::Material(Data::URI uri, Handle<Shader> shader, const Data::Material* materialdata)
        : Base{ uri }
        , m_shader { shader }
        , m_materialdata { materialdata }
        , m_albedo_texture {} {}

        std::unique_ptr<Material> Material::Create(Data::URI uri, Handle<Shader> shader, const Data::Material* materialdata)
        { return std::make_unique<Material>(uri, shader, materialdata); }

        Handle<Shader>              Material::shader() const                                            { return m_shader; }
        const Data::Material*       Material::materialdata() const                                      { return m_materialdata; }
        Handle<Texture>             Material::albedo_texture() const                                    { return m_albedo_texture; }
        Material::FaceCullingMode   Material::face_culling_mode() const                                 { return m_face_culling_mode; }
        void                        Material::set_face_culling_mode(Material::FaceCullingMode mode)     { m_face_culling_mode = mode; }

        Mesh::Mesh(Data::URI uri, const Data::Mesh* meshdata) : Base{ uri }, m_meshdata { meshdata } {} 

        std::unique_ptr<Mesh> Mesh::Create(Data::URI uri, const Data::Mesh* meshdata)
        { return std::make_unique<OpenGLMesh>(uri, meshdata); }
    }

    Renderer::Renderer(Window* window) : m_window { window } {}

    std::unique_ptr<Renderer> Renderer::Create(Window* window)
    { return std::make_unique<OpenGLRenderer>(window); }

    void Renderer::set_vp(const glm::mat4& view, const glm::mat4& projection)
    { m_view = view; m_projection = projection; }

    const glm::mat4& Renderer::view() const { return m_view; }
    const glm::mat4& Renderer::projection() const { return m_projection; }

    Resource::Handle<Resource::Shader> Renderer::CreateShader
    (
        Asset::Handle<Asset::Text> vs_asset,
        Asset::Handle<Asset::Text> fs_asset,
        Asset::Handle<Asset::Text> gs_asset
    )
    {
        LogicalPath path { Resource::Base::dir_path() / Resource::Shader::dir_path() / ("shader" + instance_counter<Resource::Shader>()) };
        Data::URI uri { URI::Builder{ URI::Scheme::GPU }.path(path).build() };
        Resource::ID id { str_to_ID(uri.string()) };

        std::string_view vs_str { vs_asset.asset()->content() };
        std::string_view fs_str { fs_asset.asset()->content() };
        std::string_view gs_str {};
        if (gs_asset.is_valid()) gs_str = gs_asset.asset()->content();

        std::unique_ptr<Resource::Shader> resource
        { 
            Resource::Shader::Create(uri, vs_str, fs_str, gs_str)
        };

        Resource::Shader* raw { resource.get() };
        shader_resources.emplace(id, std::move(resource));
        return Resource::Handle<Resource::Shader>{ id, raw };
    }

    Resource::Handle<Resource::Texture> Renderer::CreateTexture(Asset::Handle<Asset::Image> image_asset)
    {
        LogicalPath path { Resource::Base::dir_path() / Resource::Texture::dir_path() / ("texture" + instance_counter<Resource::Texture>()) };
        Data::URI uri { URI::Builder{ URI::Scheme::GPU }.path(path).build() };
        Resource::ID id { str_to_ID(uri.string()) };

        std::unique_ptr<Resource::Texture> resource { Resource::Texture::Create(uri, image_asset.asset()->data()) };

        Resource::Texture* raw { resource.get() };
        texture_resources.emplace(id, std::move(resource));
        return Resource::Handle<Resource::Texture>{ id, raw };
    }

    Resource::Handle<Resource::Material> Renderer::CreateMaterial
    (
        Resource::Handle<Resource::Shader> shader,
        Asset::Handle<Asset::Model> model_asset,
        unsigned mat_index
    )
    {
        LogicalPath path { Resource::Base::dir_path() / Resource::Material::dir_path() / ("material" + instance_counter<Resource::Material>()) };
        Data::URI uri { URI::Builder{ URI::Scheme::GPU }.path(path).build() };
        Resource::ID id { str_to_ID(uri.string()) };

        std::unique_ptr<Resource::Material> resource
        {
            Resource::Material::Create(uri, shader, model_asset.asset()->materialdata(mat_index))
        };

        Resource::Material* raw { resource.get() };
        material_resources.emplace(id, std::move(resource));
        return Resource::Handle<Resource::Material>{ id, raw };
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
