#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API Resource
    {
    public:
        Resource();
        virtual ~Resource() = default;
    protected:
        std::string path;
    };

    class JAGE_API ShaderResource : public Resource
    {
    public:
        ShaderResource(const std::string& vs_filename, const std::string& fs_filename);
        ~ShaderResource() = default;

        std::string_view get_vs() const { return vs_str; }
        std::string_view get_fs() const { return fs_str; }
    private:
        std::string vs_str;
        std::string fs_str;
    };

    class JAGE_API ResourceManager
    {
    public:
        static ResourceManager& instance();
        static void reset();

        ~ResourceManager() = default;
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager &operator=(const ResourceManager&) = delete;

        const ShaderResource& DefaultShader() const;
    private:
        ResourceManager();
        inline static std::unique_ptr<ResourceManager> m_instance;
        inline static std::mutex mutex;

        ShaderResource default_shader;
    };
}