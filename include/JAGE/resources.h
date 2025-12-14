#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"

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

    class JAGE_API TextResource final : public Resource
    {
    public:
        TextResource(std::string_view filepath_str);
        ~TextResource() = default;

        std::string_view content() const;
    private:
        std::string m_content;
    };

    class JAGE_API ImageResource final : public Resource
    {
    public:
        ImageResource(const std::string& filepath_str);
        ~ImageResource();

        // for now, delete copy constructor/assignment operator since image loader backend's (stb_image) internal
        // memory allocator doesn't support copying image data
        ImageResource(const ImageResource& other) = delete;
        ImageResource& operator=(const ImageResource& other) = delete;

        ImageResource(ImageResource&& other) noexcept;
        ImageResource& operator=(ImageResource&& other) noexcept;

        unsigned char* data() const;
        unsigned size() const;
        unsigned width() const;
        unsigned height() const;
    private:
        unsigned char* m_data;
        unsigned m_size;
        unsigned m_width;
        unsigned m_height;
    };

    class JAGE_API ModelResource final : public Resource
    {
    public:
        ModelResource(std::string_view filepath_str);
        ~ModelResource() = default;
    private:
        
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
    private:
        ResourceManager() = default;
        inline static std::unique_ptr<ResourceManager> m_instance;
        inline static std::mutex mutex;
    };
}