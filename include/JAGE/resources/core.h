#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API Resource
    {
    public:
        Resource() : path { "./resources/" } {}
        virtual ~Resource() = default;
    protected:
        std::string path;
    };

    class JAGE_API ShaderResource : public Resource
    {
    public:
        ShaderResource(const std::string& vs_filepath_str, const std::string& fs_filepath_str);
        ~ShaderResource() = default;

        std::string_view vs() const { return vs_str; }
        std::string_view fs() const { return fs_str; }
    private:
        std::string vs_str;
        std::string fs_str;
    };

    class JAGE_API ImageResource : public Resource
    {
    public:
        ImageResource(const std::string& filepath_str);
        ~ImageResource() = default;

        unsigned width() const { return m_width; }
        unsigned height() const { return m_height; }
        unsigned channels() const { return m_channels; }
    private:
        unsigned m_width;
        unsigned m_height;
        unsigned m_channels;
    };

    class JAGE_API ResourceManager
    {
    public:
        static ResourceManager& instance();
        static void reset();

        ~ResourceManager() = default;
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager &operator=(const ResourceManager&) = delete;
    private:
        ResourceManager() {}
        inline static std::unique_ptr<ResourceManager> m_instance;
        inline static std::mutex mutex;
    };
}