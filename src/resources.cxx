#include "JAGE/resources/core.h"

#include "log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <tiny_gltf.h>

namespace JAGE
{
    ImageResource::ImageResource(const std::string& filepath_str)
    {
        std::string path_str { path + "images/" + filepath_str };

        stbi_set_flip_vertically_on_load(true);
        m_data = stbi_load(path_str.c_str(), &m_width, &m_height, &m_channels, 0);

        if (!m_data)
        {
            JAGE_LOG_ERROR("JAGE I/O error: failed to load image at path - {}", path_str);
            JAGE_MSG_ERROR("Returning empty contents.");
        }
    }

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

    FileResource::FileResource(std::string_view filepath_str)
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