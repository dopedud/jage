#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"

namespace JAGE
{
    namespace fs = std::filesystem;
    using ResourceID = u64;

    // NOTE: Resources could technically be instantiated directly from classes derived from Resource, but this should
    // be avoided and only get resources from ResourceManager. Proper compile-time restrictions has been programmed in
    // place to avoid the user from accidentally instantiated Resource directly.

    class JAGE_API Resource
    {
    public:
        static fs::path dir_path();

        Resource(fs::path path);
        virtual ~Resource() = default;

        fs::path path() const;
    protected:
        fs::path m_path;
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
        class Key
        {
            private: Key() = default;
            friend class ResourceManager;
        };

        static ResourceManager& instance();
        static void reset();

        ~ResourceManager() = default;

        /**
         * `ResourceManager` is a singleton, cannot be copied
         */
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager &operator=(const ResourceManager&) = delete;

        ResourceID path_to_ID(fs::path path);

        template<typename T> void               load(std::string_view filename);
        template<typename T> ResourceHandle<T>  get(std::string_view filename);
    private:
        ResourceManager();
        inline static std::unique_ptr<ResourceManager> m_instance;
        inline static std::mutex mutex;

        std::unordered_map<ResourceID, std::unique_ptr<Resource>> resources;
    };

    class JAGE_API TextResource final : public Resource
    {
    public:
        static fs::path dir_path();

        explicit TextResource(ResourceManager::Key, std::string_view filename);
        ~TextResource() = default;

        std::string_view content() const;
    private:
        std::string m_content;
    };

    struct JAGE_API ImageData
    {
        /**
         * @var pixels
         * 
         * @brief A dynamic array to hold pixel data of an image.
         * 
         * This array holds image data in contiguous memory because the renderer expects the image data to be
         * laid out as such.
         * 
         * @note The size of this array must be `width * height * 4`, with the literal 4 here being the number of
         * channels each pixel occupy. The modern format is RGBA8888 for each pixel.
         */
        std::vector<u8> pixels {};

        unsigned width {}, height {};

        /**
         * @fn ImageData::set_pixel
         * 
         * @brief Setter function to set a pixel value of an image.
         * 
         * @param row The row of the pixel to set.
         * @param collumn The column of the pixel to set.
         * @param channel The color channel of the pixel to set. Set 0, 1, 2, or 3 for red, green, blue, or alpha
         * channel respectively.
         * @param value The value to set the pixel value. Must be between 0 to 255 (maximum value for an unsigned integer).
         */
        void set_pixel(unsigned row, unsigned column, unsigned channel, u8 value);

        static ImageData pink_black_checkerbox();
    };

    class JAGE_API ImageResource final : public Resource
    {
    public:
        static fs::path dir_path();

        explicit ImageResource(ResourceManager::Key, std::string_view filename);

        const ImageData* data() const;
    private:
        ImageData m_data;
    };

    struct JAGE_API MeshData
    {
        enum class PrimitiveType : u8 { UNKNOWN = 0, POINT, LINE, TRIANGLE };

        struct JAGE_API VertexData
        {
            glm::vec3 position {};
            glm::vec3 normal {};
            std::array<glm::vec2, 4> uvcoords {};
            std::array<glm::vec4, 4> colors {};
        };

        std::string name {};
        PrimitiveType ptype {};
        std::vector<VertexData> vertices {};
        std::vector<unsigned> indices {};
        unsigned material_index {};
    };

    struct JAGE_API MaterialData
    {
        glm::vec4 diffuse_color { 1.0f };
        ImageData diffuse_map {};
    };

    struct JAGE_API ModelNode
    {
        std::string name {};
        ModelNode* parent {};
        std::vector<std::unique_ptr<ModelNode>> children {};
        glm::mat4 transformation_matrix { 1.0f };
        std::vector<unsigned> meshes_index {};
    };

    class JAGE_API ModelResource final : public Resource
    {
    public:
        static fs::path dir_path();

        explicit ModelResource(ResourceManager::Key, std::string_view filename);
        ~ModelResource();

        const ModelNode* root() const;
        const MeshData* mesh_data(unsigned index) const;
        const MaterialData* material_data(unsigned index) const;
    private:
        std::unique_ptr<ModelNode> m_root;
        std::vector<MeshData> meshes;
        std::vector<MaterialData> materials;

        struct ModelResource_Impl;
        std::unique_ptr<ModelResource_Impl> impl;
    };
}