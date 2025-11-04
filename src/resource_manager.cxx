#include "JAGE/resource_manager/core.h"

#include "log.h"

#include <tiny_gltf.h>

namespace JAGE
{
    Resource::Resource() : path { "./resources/" } {}

    ShaderResource::ShaderResource(const std::string& vs_filepath_str, const std::string& fs_filepath_str)
    {
        std::string vs_path_str { path + "shaders/" + vs_filepath_str };
        std::string fs_path_str { path + "shaders/" + fs_filepath_str };

        std::ifstream vs_file { vs_path_str, std::ios::in | std::ios::binary };
        std::ifstream fs_file { fs_path_str, std::ios::in | std::ios::binary };

        if (!vs_file)
        {
            JAGE_LOG_ERROR("JAGE I/O error: failed to open file with path - {}", vs_path_str);
            JAGE_MSG_ERROR("Returning empty contents.");

            vs_str = "";
        }

        if (!fs_file)
        {
            JAGE_LOG_ERROR("JAGE I/O error: failed to open file with path - {}", fs_path_str);
            JAGE_MSG_ERROR("Returning empty contents.");

            fs_str = "";
        }

        if (!vs_file || !fs_file) return;

        // tbh I don't know what the long part does to the VS and FS files, but it basically reads the whole file content
        // and stuff it into an std::string
        vs_str = std::string{ std::istreambuf_iterator<char>{ vs_file }, std::istreambuf_iterator<char>{} };
        fs_str = std::string{ std::istreambuf_iterator<char>{ fs_file }, std::istreambuf_iterator<char>{} };
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

    ResourceManager::ResourceManager() : default_shader { "default.vs", "default.fs" }
    {}

    const ShaderResource& ResourceManager::DefaultShader() const { return default_shader; }
}