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

    Resource::Resource(std::string_view path)
    {
        std::filesystem::path canonical_path { "./resources/" + std::string{ path } };
        canonical_path = std::filesystem::weakly_canonical(canonical_path);
        m_path = canonical_path.lexically_normal().string();
    }

    std::string_view Resource::path() const { return m_path; }

    ResourceHandle::ResourceHandle(ResourceID id, Resource* asset)
    : m_id { id }, m_asset { asset } {}

    ResourceID ResourceHandle::id() const { return m_id; }
    Resource* ResourceHandle::asset() const { return m_asset; }

    ResourceManager::ResourceManager() : resources {}
    {

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

    template<typename T> ResourceHandle ResourceManager::Load(std::string_view filename) 
    {
        std::unique_ptr<Resource> resource { std::make_unique<T>(filename) };
        ResourceID id_hash { XXH3_64bits(resource->path().data(), resource->path().size())};
        ResourceHandle result { id_hash, resource.get() };
        resources.emplace(id_hash, std::move(resource));
        return result;
    }

    template ResourceHandle ResourceManager::Load<TextResource>(std::string_view filename);
    template ResourceHandle ResourceManager::Load<ImageResource>(std::string_view filename);

    TextResource::TextResource(std::string_view filename)
    : Resource{ "shaders/" + std::string{ filename } }
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
    : Resource{ "images/" + std::string{ filename } }, m_size {}, m_width {}, m_height {}
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
        m_size = m_width * m_height * 4 * sizeof(unsigned char);
    }

    ImageResource::~ImageResource() { stbi_image_free(m_data); }

    unsigned char* ImageResource::data() const { return m_data; }

    unsigned ImageResource::size() const { return m_size; }
    unsigned ImageResource::width() const { return m_width; }
    unsigned ImageResource::height() const { return m_height; }

    ModelResource::ModelResource(std::string_view filename)
    : Resource{ "models/" + std::string{ filename } }
    {
        Assimp::Importer importer;

        unsigned import_flags { aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded };

        const aiScene* scene { importer.ReadFile(m_path, import_flags) };

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            JAGE_LOG_ERROR("{}", importer.GetErrorString());
            JAGE_MSG_ERROR("Returning empty contents.");
            return;
        }

        aiMesh* mesh { scene->mMeshes[scene->mRootNode->mMeshes[0]] };

        // JAGE_LOG_DEBUG("{}", model.defaultScene);
    }
}