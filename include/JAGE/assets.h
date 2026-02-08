#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"

namespace JAGE
{
    namespace fs = std::filesystem;
    using ResourceID = u64;

    /**
     * @class Resource
     * 
     * @brief The `Resource` class that acts as a base class for all different types of assets to derive from.
     * 
     * @note Resources could technically be instantiated directly from classes derived from Resource, but this should
     * be avoided and only get resources from `ResourceManager`. Proper compile-time restrictions has been programmed in
     * place to avoid the user from accidentally instantiating Resource directly.
     */
    class JAGE_API Resource
    {
    public:
        static fs::path dir_path();

        Resource(fs::path path);
        virtual ~Resource() = default;

        fs::path path() const;
        bool is_valid() const;
    protected:
        fs::path m_path;
        bool m_is_valid;
    };

    template<typename T>
    class ResourceHandle
    {
    public:
        ResourceHandle(ResourceID id, T* resource);

        ResourceID id() const;
        const T* resource() const;
    private:
        ResourceID m_id;
        T* m_resource;
    };

    class JAGE_API ResourceManager
    {
    public:
        class Key
        {
            Key() = default;
            friend class ResourceManager;
        };

        static ResourceManager& instance();
        static void release();

        ~ResourceManager() = default;

        /**
         * `ResourceManager` is a singleton, which means it cannot be copied.
         * 
         * @{
         */
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager &operator=(const ResourceManager&) = delete;
        /** @} */

        void Initialise();

        ResourceID path_to_ID(fs::path path);

        template<typename T> void               load(std::string_view filename);
        template<typename T> ResourceHandle<T>  get(std::string_view filename);
    private:
        ResourceManager();

        inline static std::unique_ptr<ResourceManager> m_instance {};
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
         * @brief A dynamic array to hold the pixel data of an image.
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
         * @fn set_pixel
         * 
         * @brief Setter function to set a pixel value of an image.
         * 
         * @param channel The color channel of the pixel to set. Set 0, 1, 2, or 3 for red, green, blue, or alpha
         * channel respectively.
         * @param value The value to set the pixel value. Must be between 0 to 255 (255 is the maximum value for an
         * unsigned 1-byte integer).
         */
        void set_pixel(unsigned row, unsigned column, unsigned channel, u8 value);

        /**
         * @fn pink_black_checkerbox
         * 
         * @brief Spits out a pink black image with a checkerbox pattern, indicating it's an errorr image.
         */
        static const ImageData* pink_black_checkerbox();
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

            /**
             * The number of UV channel and vertex color set in a vertex should be determined since shaders do not
             * support variable number of them. For now, JAGE supports up to 4 UV channel set and 4 vertex color set.
             * 
             * @{
             */
            std::array<glm::vec2, 4> uvcoords {};
            std::array<glm::vec4, 4> colors {};
            /** @} */
        };

        std::string name {};
        PrimitiveType ptype {};
        std::vector<VertexData> vertices {};
        std::vector<unsigned> indices {};
        unsigned material_index {};
    };

    struct JAGE_API MaterialData
    {
        std::string name {};
        glm::vec4 albedo_color { 1.0f };
        const ImageData* albedo_map {};
        glm::vec4 normal_color { 0.5f };
        const ImageData* normal_map {};
        glm::vec4 specular_color { 0.5f };
        const ImageData* specular_map {};

        // metadata, mostly unimportant
        enum class TextureType : u8 { NONE = 0, ALBEDO, NORMAL, SPECULAR };
        std::unordered_map<std::string, TextureType> unloaded_textures {};
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
        std::vector<ImageData> embedded_textures;
        std::vector<MaterialData> materials;

        struct Impl;
        std::unique_ptr<Impl> pimpl;

        /**
         * Bad fucking design, but is needed to access `materials` (to load unloaded material textures) without
         * exposing it as a public API.
         */
        friend class ResourceManager;
    };
}