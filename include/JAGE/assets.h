#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"

namespace JAGE
{
    namespace fs = std::filesystem;
    using AssetID = u64;

    /**
     * @class Asset
     * 
     * @brief The `Asset` class that acts as a base class for all the different types of assets to derive from.
     * 
     * @note Assets could technically be instantiated directly from classes derived from `Asset`, but this should
     * be avoided and only get assets from `AssetManager`. Proper compile-time restrictions has been programmed in
     * place to avoid the user from accidentally instantiating `Asset` and classes that derive from it directly.
     */
    class JAGE_API AssetBase
    {
    public:
        static fs::path dir_path();

        AssetBase(fs::path path);
        virtual ~AssetBase() = default;

        fs::path path() const;
        bool is_valid() const;
    protected:
        fs::path m_path;
        bool m_is_valid;
    };

    template<typename T>
    class AssetHandle
    {
    public:
        AssetHandle(AssetID id, T* asset);

        AssetID id() const;
        const T* asset() const;
    private:
        AssetID m_id;
        T* m_asset;
    };

    // forward declare TextAsset, ImageAsset, and ModelAsset class to be used by AssetManager` class
    namespace Asset
    {
        class JAGE_API Text;
        class JAGE_API Image;
        class JAGE_API Model;
    }

    class JAGE_API AssetManager
    {
    public:
        /**
         * @class Key
         * 
         * @brief The `Key` class that classes that are derived from `Asset` receives as a constructor argument.
         * 
         * The `Key` class is the compile-time restriction to prevent the user from instantiating `Asset` and its
         * derived classes directly. It can only be used by `AssetManager`.
         */
        class Key
        {
            Key() = default;
            friend class AssetManager;
        };

        static AssetManager& instance();
        static void release();

        ~AssetManager() = default;

        /**
         * `AssetManager` is a singleton, which means it cannot be copied.
         * 
         * @{
         */
        AssetManager(const AssetManager&) = delete;
        AssetManager &operator=(const AssetManager&) = delete;
        /** @} */

        void Initialise();

        AssetID path_to_ID(fs::path path);

        template<typename T> void               Load(std::string_view filename);
        template<typename T> AssetHandle<T>     Get(std::string_view filename);
    private:
        AssetManager();

        inline static std::unique_ptr<AssetManager> m_instance {};
        std::unordered_map<AssetID, std::unique_ptr<Asset::Text>> text_assets;
        std::unordered_map<AssetID, std::unique_ptr<Asset::Image>> image_assets;
        std::unordered_map<AssetID, std::unique_ptr<Asset::Model>> model_assets;
    };

    namespace Data
    {
        struct JAGE_API Image
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
             * channels each pixel occupy. The format used is RGBA8888 for each pixel.
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
             * @brief Spits out a pink black image with a checkerbox pattern, indicating it's an error image.
             */
            static const Image* pink_black_checkerbox();
        };

        struct JAGE_API Mesh
        {
            enum class PrimitiveType : u8 { UNKNOWN = 0, POINT, LINE, TRIANGLE };

            struct JAGE_API Vertex
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
            std::vector<Vertex> vertices {};
            std::vector<unsigned> indices {};
            unsigned material_index {};
        };

        struct JAGE_API Material
        {
            std::string name {};
            glm::vec4 albedo_color { 1.0f };
            const Image* albedo_map {};
            float normal_factor { 0.5f };
            const Image* normal_map {};
            float specular_factor { 0.5f };
            const Image* specular_map {};

            // metadata, mostly unimportant
            enum class TextureType : u8 { NONE = 0, ALBEDO, NORMAL, SPECULAR };
            std::unordered_map<std::string, TextureType> unloaded_textures {};
        };
    }

    namespace Asset
    {

        class JAGE_API Text final : public AssetBase
        {
        public:
            static fs::path dir_path();

            explicit Text(AssetManager::Key, std::string_view filename);
            ~Text() = default;

            std::string_view content() const;
        private:
            std::string m_content;
        };

        class JAGE_API Image final : public AssetBase
        {
        public:
            static fs::path dir_path();

            explicit Image(AssetManager::Key, std::string_view filename);

            const Data::Image* data() const;
        private:
            Data::Image m_data;
        };

        class JAGE_API Model final : public AssetBase
        {
        public:
            static fs::path dir_path();

            explicit Model(AssetManager::Key, std::string_view filename);
            ~Model();

            struct JAGE_API Node
            {
                std::string name {};
                Node* parent {};
                std::vector<std::unique_ptr<Node>> children {};
                glm::mat4 transformation_matrix { 1.0f };
                std::vector<unsigned> meshes_index {};
            };

            const Node* root() const;
            const Data::Mesh* meshdata(unsigned index) const;
            const Data::Material* materialdata(unsigned index) const;
        private:
            std::unique_ptr<Node> m_root;
            std::vector<Data::Mesh> meshes;
            std::vector<Data::Image> embedded_textures;
            std::vector<Data::Material> materials;

            struct Impl;
            std::unique_ptr<Impl> pimpl;

            /**
             * Bad fucking design, but is needed to access `materials` (to load unloaded material textures) without
             * exposing it as a public API.
             */
            friend class ::JAGE::AssetManager;
        };
    }
}