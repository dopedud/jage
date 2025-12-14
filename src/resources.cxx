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

DISABLE_WARNING_POP

namespace JAGE
{
    Resource::Resource() : path { "./resources/" } {}

    TextResource::TextResource(std::string_view filepath_str)
    {
        std::string path_str { path + "shaders/" + std::string{ filepath_str } };

        std::ifstream file {};

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            file.open(path_str);

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

    ImageResource::ImageResource(const std::string& filepath_str)
    : m_size {}, m_width {}, m_height {}
    {
        std::string path_str { path + "images/" + filepath_str };

        int width {};
        int height {};

        stbi_set_flip_vertically_on_load(true);
        m_data = stbi_load(path_str.c_str(), &width, &height, nullptr, 4);

        if (!m_data)
        {
            JAGE_LOG_ERROR("JAGE I/O error: failed to load image at path - {}", path_str);
            JAGE_MSG_ERROR("Returning empty contents.");
            return;
        }

        m_width = width;
        m_height = height;
        m_size = m_width * m_height * 4 * sizeof(unsigned char);
    }

    ImageResource::~ImageResource() { stbi_image_free(m_data); }

    ImageResource::ImageResource(ImageResource&& other) noexcept
    : m_data { other.m_data }
    , m_size { other.m_size }
    , m_width { other.m_width }
    , m_height { other.m_height }
    {
        other.m_data = nullptr;
    }

    ImageResource& ImageResource::operator=(ImageResource&& other) noexcept
    {
        if (this != &other)
        {
            stbi_image_free(m_data);
            m_data = other.m_data;
            m_size = other.m_size;
            m_width = other.m_width;
            m_height = other.m_height;
            other.m_data = nullptr;
        }

        return *this;
    }

    unsigned char* ImageResource::data() const { return m_data; }

    unsigned ImageResource::size() const { return m_size; }
    unsigned ImageResource::width() const { return m_width; }
    unsigned ImageResource::height() const { return m_height; }

    ModelResource::ModelResource(std::string_view filepath_str)
    {
        std::string path_str { path + "models/" + std::string{ filepath_str } };

        Assimp::Importer importer;

        unsigned import_flags { aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded };

        const aiScene* scene { importer.ReadFile(path_str, import_flags) };

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            JAGE_LOG_ERROR("{}", importer.GetErrorString());
            JAGE_MSG_ERROR("Returning empty contents.");
            return;
        }

        aiMesh* mesh { scene->mMeshes[scene->mRootNode->mMeshes[0]] };

        // JAGE_LOG_DEBUG("{}", model.defaultScene);
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
}