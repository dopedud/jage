#include "JAGE/resources.h"

#include "log.h"

DISABLE_WARNING_PUSH
DISABLE_WARNING_GCC_CLANG("-Wmissing-field-initializers")

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define XXH_INLINE_ALL
#include <xxhash.h>

DISABLE_WARNING_POP

namespace JAGE
{
    std::string_view Resource::dir_path() { return "./resources/"; }
    std::string_view TextResource::dir_path() { return "shaders/"; }
    std::string_view ImageResource::dir_path() { return "images/"; }
    std::string_view ModelResource::dir_path() { return "models/"; }

    Resource::Resource(std::string_view path)
    : m_path { std::string{ dir_path() } + std::string{ path } } {}

    std::string_view Resource::path() const { return m_path; }

    template<typename T>
    ResourceHandle<T>::ResourceHandle(ResourceID id, T* resource)
    : m_id { id }, m_resource { resource } {}

    template<typename T> ResourceID ResourceHandle<T>::id() const { return m_id; }
    template<typename T> T* ResourceHandle<T>::resource() const { return m_resource; }

    ResourceManager::ResourceManager() : resources {}
    {
        load<TextResource>("default.vs");
        load<TextResource>("default.fs");
        load<ImageResource>("image.jpg");
    }

    ResourceManager& ResourceManager::instance()
    {
        std::lock_guard<std::mutex> lock { mutex };

        if (!m_instance) m_instance.reset(new ResourceManager());
        return *m_instance;
    }

    void ResourceManager::reset()
    {
        std::lock_guard<std::mutex> lock { mutex };
        m_instance.reset();
    }

    ResourceID ResourceManager::path_to_ID(std::string_view str) { return XXH3_64bits(str.data(), str.size()); }

    template<typename T>
    void ResourceManager::load(std::string_view filename) 
    {
        std::unique_ptr<Resource> resource { std::make_unique<T>(filename) };
        ResourceID id_hash { path_to_ID(resource->path()) };
        resources.emplace(id_hash, std::move(resource));
    }

    template<typename T>
    ResourceHandle<T> ResourceManager::get(std::string_view filename)
    {
        std::string path { std::string{ Resource::dir_path() } + std::string{ T::dir_path() } + std::string{ filename } };
        ResourceID id_hash { path_to_ID(path) };
        Resource* resource { resources.find(id_hash)->second.get() };
        return ResourceHandle<T>{ id_hash, static_cast<T*>(resource) };
    }

    template class ResourceHandle<TextResource>;
    template class ResourceHandle<ImageResource>;

    template void                           ResourceManager::load<TextResource>(std::string_view filename);
    template void                           ResourceManager::load<ImageResource>(std::string_view filename);
    template ResourceHandle<TextResource>   ResourceManager::get<TextResource>(std::string_view filename);
    template ResourceHandle<ImageResource>  ResourceManager::get<ImageResource>(std::string_view filename);

    TextResource::TextResource(std::string_view filename)
    : Resource{ std::string{ dir_path() } + std::string{ filename } }
    {
        std::ifstream file {};

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            file.open(m_path);

            std::stringstream sstream {};
            sstream << file.rdbuf();

            file.close();

            m_content = sstream.str();
        }

        catch (const std::ifstream::failure& e)
        {
            JAGE_LOG_ERROR("JAGE I/O error ({} - {}): {}.", e.code().value(), e.code().message(), e.what());
            JAGE_MSG_ERROR("Returning empty contents.");

            m_content = "";
        }
    }

    std::string_view TextResource::content() const { return m_content; }

    ImageResource::ImageResource(std::string_view filename)
    : Resource{ std::string{ dir_path() } + std::string{ filename } }
    , m_size {}, m_width {}, m_height {}
    {
        int width {};
        int height {};

        stbi_set_flip_vertically_on_load(true);
        m_data = stbi_load(m_path.c_str(), &width, &height, nullptr, 4);

        if (!m_data)
        {
            JAGE_LOG_ERROR("JAGE I/O error: failed to load image at path - {}", m_path);
            JAGE_MSG_ERROR("Returning empty contents.");
            return;
        }

        m_width = width;
        m_height = height;

        // literal 4 here indicates number of channels the image has
        // since desired channels was set to 4 upon loading the image via stbi_load, there is no need for variable
        // number of channels
        m_size = m_width * m_height * 4 * sizeof(ui8);
    }

    ImageResource::~ImageResource() { stbi_image_free(m_data); }

    ImageResource::ImageResource(const ImageResource& other)
    : Resource{ "" }
    , m_size { other.m_size }, m_width { other.m_width }, m_height { other.m_height }
    {
        m_path = other.m_path;

        if (other.m_data)
        {
            // data is allocated using C's malloc() to match stb_image's way of allocating image data
            // (which also uses C's malloc())
            m_data = static_cast<ui8*>(std::malloc(other.m_size));
            std::memcpy(m_data, other.m_data, other.m_size);
        }

        else m_data = nullptr;
    }

    ImageResource& ImageResource::operator=(const ImageResource& other)
    {
        if (this != &other)
        {
            ImageResource temp { other };
            std::swap(m_path, temp.m_path);
            std::swap(m_data, temp.m_data);
            std::swap(m_size, temp.m_size);
            std::swap(m_width, temp.m_width);
            std::swap(m_height, temp.m_height);
        }

        return *this;
    }

    ImageResource::ImageResource(ImageResource&& other) noexcept
    : Resource{ "" }
    , m_data { other.m_data }, m_size { other.m_size }, m_width { other.m_width }, m_height { other.m_height }
    {
        m_path = other.m_path;

        other.m_path = "";
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_width = 0;
        other.m_height = 0;
    }

    ImageResource& ImageResource::operator=(ImageResource&& other) noexcept
    {
        if (this != &other)
        {
            if (m_data) { stbi_image_free(m_data); }

            m_path = other.m_path;
            m_data = other.m_data;
            m_size = other.m_size;
            m_width = other.m_width;
            m_height = other.m_height;

            other.m_path = "";
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_width = 0;
            other.m_height = 0;
        }

        return *this;
    }

    ui8* ImageResource::data() const { return m_data; }

    unsigned ImageResource::size() const { return m_size; }
    unsigned ImageResource::width() const { return m_width; }
    unsigned ImageResource::height() const { return m_height; }

    struct ModelResource::ModelResource_Impl
    {
    };

    ModelResource::ModelResource(std::string_view filename)
    : Resource{ "models/" + std::string{ filename } }
    {
        Assimp::Importer importer;

        unsigned import_flags { aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded };

        const aiScene* scene { importer.ReadFile(m_path, import_flags) };

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            JAGE_LOG_ERROR("JAGE I/O error: {}", importer.GetErrorString());
            JAGE_MSG_ERROR("Returning empty contents.");
            return;
        }
    }
}