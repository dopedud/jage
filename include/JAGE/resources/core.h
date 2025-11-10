#pragma once

#include "JAGE/core.h"

/**
 * 
 * 
 * MACRO FOR API EXPORT DEFINITIONS
 * 
 * 
 */
#ifdef _WIN32
#   ifdef JAGE_RESOURCES_EXPORT
#       define JAGE_RESOURCES_API __declspec(dllexport)
#   else
#       define JAGE_RESOURCES_API __declspec(dllimport)
#   endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define JAGE_RESOURCES_API __attribute__((visibility("default")))
#else
#   define JAGE_RESOURCES_API
#endif

namespace JAGE
{
    class JAGE_RESOURCES_API Resource
    {
    public:
        Resource() : path { "./resources/" } {}
        virtual ~Resource() = default;
    protected:
        std::string path;
    };

    class JAGE_RESOURCES_API ImageResource : public Resource
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

        unsigned char* data() const     { return m_data; }
        unsigned width() const          { return m_width; }
        unsigned height() const         { return m_height; }
        unsigned channels() const       { return m_channels; }
    private:
        unsigned char* m_data;
        int m_width;
        int m_height;
        int m_channels;
    };

    class JAGE_RESOURCES_API FileResource : public Resource
    {
    public:
        FileResource(std::string_view filepath_str);
        ~FileResource() = default;

        std::string_view content() const { return m_content; }
    private:
        std::string m_content;
    };

    class JAGE_RESOURCES_API ResourceManager
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