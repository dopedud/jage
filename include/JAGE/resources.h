#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"

namespace JAGE
{
    using ResourceID = uint64_t;

    // TODO: transform resource path to ID

    class JAGE_API Resource
    {
    public:
        Resource(std::string_view path);
        virtual ~Resource() = default;

        std::string_view path() const; 
    protected:
        std::string m_path;
    };

    template<typename T>
    class ResourceHandle
    {
    public:
        ResourceHandle(T* asset, ResourceID id);
        T* asset() const;
        ResourceID id() const;
    private:
        T* m_asset;
        ResourceID m_id;
    };

    class JAGE_API ResourceManager
    {
    public:
        static ResourceManager& instance();
        static void reset();

        ~ResourceManager() = default;

        // ResourceManager is a singleton, cannot be copied
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager &operator=(const ResourceManager&) = delete;

        template<typename T> ResourceHandle<T> Load(std::string_view filename);
    private:
        ResourceManager() = default;
        inline static std::unique_ptr<ResourceManager> m_instance;
        inline static std::mutex mutex;

        std::unordered_map<ResourceID, std::unique_ptr<Resource>> resources;
    };

    class JAGE_API TextResource final : public Resource
    {
    public:
        TextResource(std::string_view filename);
        ~TextResource() = default;

        std::string_view content() const;
    private:
        std::string m_content;
    };

    class JAGE_API ImageResource final : public Resource
    {
    public:
        ImageResource(std::string_view filename);
        ~ImageResource();

        unsigned char* data() const;
        unsigned size() const;
        unsigned width() const;
        unsigned height() const;
    private:
        unsigned char* m_data;
        unsigned m_size, m_width, m_height;
    };

    class JAGE_API ModelResource final : public Resource
    {
    public:
        ModelResource(std::string_view filename);
        ~ModelResource() = default;
    private:
        
    };
}