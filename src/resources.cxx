#include "JAGE/resources/core.h"

#include "log.h"

#include <tiny_gltf.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace JAGE
{
    ImageResource::ImageResource(const std::string& filepath_str)
    {
        std::string path_str { path + "images/" + filepath_str };

        m_data = stbi_load(path_str.c_str(), &m_width, &m_height, &m_channels, 0);

        if (!m_data)
        {
            JAGE_LOG_ERROR("JAGE I/O error: failed to load image at path - {}", path_str);
            JAGE_MSG_ERROR("Returning empty contents.");
        }
    }

    ImageResource::

    ImageResource::ImageResource(ImageResource&& other) noexcept
    : m_data { other.m_data }
    , m_width { other.m_width }
    , m_height { other.m_height }
    , m_channels { other.m_channels }
    {
        other.m_data = nullptr;
    }

    ImageResource& ImageResource::operator=(ImageResource&& other) noexcept
    {
        if (this != &other)
        {
            stbi_image_free(m_data);
            m_data = other.m_data;
            m_width = other.m_width;
            m_height = other.m_height;
            m_channels = other.m_channels;
            other.m_data = nullptr;
        }

        return *this;
    }

    ImageResource::~ImageResource()
    {
        stbi_image_free(m_data);
    }

    ShaderResource::ShaderResource(const std::string& vs_filepath_str, const std::string& fs_filepath_str)
    {
        std::string vs_path_str { path + "shaders/" + vs_filepath_str };
        std::string fs_path_str { path + "shaders/" + fs_filepath_str };

        std::ifstream vs_file {};
        std::ifstream fs_file {};

        vs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vs_file.open(vs_path_str);
            fs_file.open(fs_path_str);

            std::stringstream vs_sstream {};
            std::stringstream fs_sstream {};

            vs_sstream << vs_file.rdbuf();
            fs_sstream << fs_file.rdbuf();

            vs_file.close();
            fs_file.close();

            vs_str = vs_sstream.str();
            fs_str = fs_sstream.str();
        }

        catch (const std::ifstream::failure& e)
        {
            JAGE_LOG_ERROR("JAGE I/O error ({} - {}): {}.", e.code().value(), e.code().message(), e.what());
            JAGE_MSG_ERROR("Returning empty contents.");

            vs_str = "";
            fs_str = "";
        }
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