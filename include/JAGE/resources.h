#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"

namespace JAGE
{
    using ResourceID = ui64;

    // NOTE: Resources could technically be instantiated directly from classes derived from Resource, but this should
    // be avoided and only get resources from ResourceManager. Proper compile-time restrictions has been programmed in
    // place to avoid the user from accidentally instantiated Resource directly.

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
        class Key
        {
            private: Key() = default;
            friend class ResourceManager;
        };

        static ResourceManager& instance();
        static void reset();

        ~ResourceManager() = default;

        /**
         * @c ResourceManager is a singleton, cannot be copied
         */
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager &operator=(const ResourceManager&) = delete;

        ResourceID path_to_ID(std::string_view str);

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
        static std::string_view dir_path();

        explicit TextResource(ResourceManager::Key, std::string_view filename);
        ~TextResource() = default;

        std::string_view content() const;
    private:
        std::string m_content;
    };

    class JAGE_API ImageResource final : public Resource
    {
    public:
        static std::string_view dir_path();

        explicit ImageResource(ResourceManager::Key, std::string_view filename);
        ~ImageResource();

        const ui8* data() const;

        unsigned size() const;
        unsigned width() const;
        unsigned height() const;
    private:
        ui8* m_data;
        unsigned m_size, m_width, m_height;
    };

    struct JAGE_API MeshData
    {
        enum class PrimitiveType : ui8 { UNKNOWN = 0, POINT, LINE, TRIANGLE };

        struct JAGE_API Vertex
        {
            glm::vec3 position {};
            glm::vec3 normal {};
            glm::vec2 uvcoord {};

            std::array<glm::vec4, 4> colors {};
        };

        std::string name {};
        PrimitiveType ptype {};
        std::vector<Vertex> vertices {};
        std::vector<unsigned> indices {};
    };

    struct JAGE_API ModelNode
    {
        std::string name {};
        ModelNode* parent {};
        std::vector<std::unique_ptr<ModelNode>> children {};
        glm::mat4 transformation_matrix {};
        std::vector<unsigned> meshes_index {};
    };

    class JAGE_API ModelResource final : public Resource
    {
    public:
        static std::string_view dir_path();

        explicit ModelResource(ResourceManager::Key, std::string_view filename);
        ~ModelResource();

        const ModelNode* root() const;
        const MeshData* data(unsigned index) const;
    private:
        std::unique_ptr<ModelNode> m_root;
        std::vector<MeshData> meshes;

        struct ModelResource_Impl;
        std::unique_ptr<ModelResource_Impl> impl;
    };
}