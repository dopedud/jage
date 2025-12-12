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

    class JAGE_API TextResource final : public Resource
    {
    public:
        TextResource(std::string_view filepath_str);
        ~TextResource() = default;

        std::string_view content() const { return m_content; }
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

        void* data() const          { return m_data; }
        unsigned width() const      { return m_width; }
        unsigned height() const     { return m_height; }
        unsigned channels() const   { return m_channels; }
    private:
        void* m_data;
        int m_width;
        int m_height;
        int m_channels;
    };

    class JAGE_API ModelResource final : public Resource
    {
    public:
        ModelResource(std::string_view filepath_str);
        ~ModelResource() = default;
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
        ResourceManager() {}
        inline static std::unique_ptr<ResourceManager> m_instance;
        inline static std::mutex mutex;
    };
}