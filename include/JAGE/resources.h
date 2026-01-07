#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"

namespace JAGE
{
    using ResourceID = uint64_t;

    // NOTE: Resources could technically be instantiated directly from classes derived from Resource, but this should
    // be avoided and only get resources from ResourceManager, albeit ResourceManager and the resources do not enforce
    // this rule.

    class JAGE_API Resource
    {
    public:
        static std::string_view dir_path();

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
        ResourceHandle(ResourceID id, T* resource);

        ResourceID id() const;
        T* resource() const;
    private:
        ResourceID m_id;
        T* m_resource;
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

        ResourceID path_to_ID(std::string_view str);

        template<typename T> void load(std::string_view filename);
        template<typename T> ResourceHandle<T> get(std::string_view filename);
    private:
        ResourceManager();
        inline static std::unique_ptr<ResourceManager> m_instance;
        inline static std::mutex mutex;

        std::unordered_map<ResourceID, std::unique_ptr<Resource>> resources;
    };

    class JAGE_API TextResource final : public Resource
    {
    public:
        static std::string_view dir_path();

        TextResource(std::string_view filename);
        ~TextResource() = default;

        std::string_view content() const;
    private:
        std::string m_content;
    };

    class JAGE_API ImageResource final : public Resource
    {
    public:
        static std::string_view dir_path();

        ImageResource(std::string_view filename);
        ~ImageResource();

        ui8* data() const;
        unsigned size() const;
        unsigned width() const;
        unsigned height() const;
    private:
        ui8* m_data;
        unsigned m_size, m_width, m_height;
    };

    class JAGE_API ModelResource final : public Resource
    {
    public:
        static std::string_view dir_path();

        ModelResource(std::string_view filename);
        ~ModelResource() = default;
    private:
        
    };
}