#include "JAGE/resources.h"

#include "log.h"

DISABLE_WARNING_PUSH
DISABLE_WARNING_GCC_CLANG("-Wmissing-field-initializers")

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define XXH_INLINE_ALL
#include <xxhash.h>

DISABLE_WARNING_POP

namespace JAGE
{
    std::string_view Resource::dir_path() { return "./resources/"; }
    std::string_view TextResource::dir_path() { return "shaders/"; }
    std::string_view ImageResource::dir_path() { return "images/"; }
    std::string_view ModelResource::dir_path() { return "models/"; }

    Resource::Resource(std::string_view path)
    : m_path { std::string{ dir_path() } + std::string{ path } } {}

    std::string_view Resource::path() const { return m_path; }

    template<typename T>
    ResourceHandle<T>::ResourceHandle(ResourceID id, T* resource)
    : m_id { id }, m_resource { resource } {}

    template<typename T> ResourceID ResourceHandle<T>::id() const { return m_id; }
    template<typename T> T* ResourceHandle<T>::resource() const { return m_resource; }

    ResourceManager::ResourceManager() : resources {}
    {
        load<TextResource>("default.vs");
        load<TextResource>("default.fs");
        load<ImageResource>("image.jpg");
        load<ModelResource>("ICOSPHERE.glb");
        load<ModelResource>("cube.glb");
        load<ModelResource>("pipo.fbx");
    }

    ResourceManager& ResourceManager::instance()
    {
        std::lock_guard<std::mutex> lock { mutex };

        if (!m_instance) m_instance.reset(new ResourceManager());
        return *m_instance;
    }

    void ResourceManager::reset()
    {
        std::lock_guard<std::mutex> lock { mutex };
        m_instance.reset();
    }

    ResourceID ResourceManager::path_to_ID(std::string_view str) { return XXH3_64bits(str.data(), str.size()); }

    template<typename T>
    void ResourceManager::load(std::string_view filename) 
    {
        std::unique_ptr<Resource> resource { std::make_unique<T>(Key{}, filename) };
        ResourceID id_hash { path_to_ID(resource->path()) };
        resources.emplace(id_hash, std::move(resource));
    }

    template<typename T>
    ResourceHandle<T> ResourceManager::get(std::string_view filename)
    {
        std::string path { std::string{ Resource::dir_path() } + std::string{ T::dir_path() } + std::string{ filename } };
        ResourceID id_hash { path_to_ID(path) };

        if (resources.find(id_hash) == resources.end())
        { 
            JAGE_MSG_ERROR("JAGE resource error: no resource with given ID.");
            JAGE_MSG_ERROR("Returning null resource.");
            return ResourceHandle<T>{ id_hash, nullptr };
        }

        Resource* resource { resources.find(id_hash)->second.get() };
        return ResourceHandle<T>{ id_hash, static_cast<T*>(resource) };
    }

    template class ResourceHandle<TextResource>;
    template class ResourceHandle<ImageResource>;
    template class ResourceHandle<ModelResource>;

    template void                           ResourceManager::load<TextResource>(std::string_view filename);
    template void                           ResourceManager::load<ImageResource>(std::string_view filename);
    template void                           ResourceManager::load<ModelResource>(std::string_view filename);
    template ResourceHandle<TextResource>   ResourceManager::get<TextResource>(std::string_view filename);
    template ResourceHandle<ImageResource>  ResourceManager::get<ImageResource>(std::string_view filename);
    template ResourceHandle<ModelResource>  ResourceManager::get<ModelResource>(std::string_view filename);

    TextResource::TextResource(ResourceManager::Key, std::string_view filename)
    : Resource{ std::string{ dir_path() } + std::string{ filename } }
    {
        std::ifstream file {};

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            file.open(m_path);

            std::stringstream sstream {};
            sstream << file.rdbuf();

            file.close();

            m_content = sstream.str();
        }

        catch (const std::ifstream::failure& e)
        {
            JAGE_LOG_ERROR("JAGE I/O error ({} - {}): {}.", e.code().value(), e.code().message(), e.what());
            JAGE_MSG_ERROR("Returning empty contents.");

            m_content = "";
        }
    }

    std::string_view TextResource::content() const { return m_content; }

    ImageResource::ImageResource(ResourceManager::Key, std::string_view filename)
    : Resource{ std::string{ dir_path() } + std::string{ filename } }
    , m_data {}
    {
        int width {};
        int height {};

        stbi_set_flip_vertically_on_load(true);
        ui8* loaded_data { stbi_load(m_path.c_str(), &width, &height, nullptr, STBI_rgb_alpha) };

        if (!loaded_data)
        {
            JAGE_LOG_ERROR("JAGE I/O error: failed to load image at path - {}", m_path);
            JAGE_MSG_ERROR("Returning empty contents.");
            return;
        }

        m_data.width = width;
        m_data.height = height;

        m_data.pixel
    }

    const ui8* ImageResource::data() const { return m_data; }

    unsigned ImageResource::size() const { return m_size; }
    unsigned ImageResource::width() const { return m_width; }
    unsigned ImageResource::height() const { return m_height; }

    void print_metadata(const aiScene* ai_scene)
    {
        JAGE_MSG_TRACE("Model information:");

        std::string vertices_count {};

        for (unsigned i {}; i < ai_scene->mNumMeshes; i++)
        vertices_count += " " + std::to_string(ai_scene->mMeshes[i]->mNumVertices) + ",";

        if (!vertices_count.empty()) vertices_count.back() = '.';

        JAGE_LOG_TRACE
        (
            "    Model contains {} mesh(es), with number of vertices from each mesh by order:{}",
            ai_scene->mNumMeshes,
            vertices_count
        );

        // JAGE_LOG_TRACE("    materials count: {}", ai_scene->mMaterials[0]->mNumProperties);

        // for (unsigned i {}; i < ai_scene->mMaterials[0]->mNumProperties; i++)
        // {
        //     aiMaterialProperty matprop { *ai_scene->mMaterials[0]->mProperties[i] };

        //     JAGE_LOG_TRACE("        matprop number {} name: {}", i, matprop.mKey.C_Str());

        //     switch (ai_scene->mMaterials[0]->mProperties[i]->mType)
        //     {
        //         case aiPropertyTypeInfo::aiPTI_Integer:     JAGE_LOG_TRACE("        matprop number {} type: {}", i, "integer");     break;
        //         case aiPropertyTypeInfo::aiPTI_Float:       JAGE_LOG_TRACE("        matprop number {} type: {}", i, "float");       break;
        //         case aiPropertyTypeInfo::aiPTI_Double:      JAGE_LOG_TRACE("        matprop number {} type: {}", i, "double");      break;
        //         case aiPropertyTypeInfo::aiPTI_String:      JAGE_LOG_TRACE("        matprop number {} type: {}", i, "string");      break;
        //         case aiPropertyTypeInfo::aiPTI_Buffer:      JAGE_LOG_TRACE("        matprop number {} type: {}", i, "buffer");      break;
        //         default:      JAGE_LOG_TRACE("        matprop number {} type: {}", i, "unknown"); break;
        //     }

        //     JAGE_LOG_TRACE("        matprop number {} semantic: {}", i, matprop.mSemantic);
        // }

        // JAGE_LOG_TRACE("    texture count: {}", ai_scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE));

        // aiString ai_string {};

        // ai_scene->mMaterials[0]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &ai_string);
        // JAGE_LOG_TRACE("    texture path: {}", ai_string.C_Str());

        // const aiTexture* ai_texture { ai_scene->GetEmbeddedTexture(ai_string.C_Str()) };
        // if(ai_texture) JAGE_LOG_TRACE("    texture name: {}", ai_texture->mFilename.C_Str());

        JAGE_MSG_TRACE("Metadata information:");

        aiMetadata metadata { *ai_scene->mMetaData };

        for (unsigned i {}; i < metadata.mNumProperties; i++)
        {
            switch (metadata.mValues[i].mType)
            {
                case aiMetadataType::AI_BOOL:           JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<bool*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_UINT32:         JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<ui32*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_UINT64:         JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<ui64*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_INT32:          JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<i32*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_INT64:          JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<i64*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_FLOAT:          JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<float*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_DOUBLE:         JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<double*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_AISTRING:       JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), static_cast<aiString*>(metadata.mValues[i].mData)->C_Str()); break;
                
                case aiMetadataType::AI_AIVECTOR3D:
                {
                    aiVector3D ai_vector { *static_cast<aiVector3D*>(metadata.mValues[i].mData) };
                    glm::vec3 vector { ai_vector.x, ai_vector.y, ai_vector.z };
                    JAGE_LOG_TRACE
                    (
                        "    {}: X: {}, Y: {}, Z: {}",
                        metadata.mKeys[i].C_Str(),
                        vector.x, vector.y, vector.z
                    );
                }
                break;

                default: JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), "metadata not recognized."); break;
            }
        }
    }

    MeshData process_mesh(aiMesh* ai_mesh, const aiScene* ai_scene)
    {
        MeshData data;

        data.name = ai_mesh->mName.C_Str();

        switch (ai_mesh->mPrimitiveTypes)
        {
            case aiPrimitiveType::aiPrimitiveType_POINT:        data.ptype = MeshData::PrimitiveType::POINT; break;
            case aiPrimitiveType::aiPrimitiveType_LINE:         data.ptype = MeshData::PrimitiveType::LINE; break;
            case aiPrimitiveType::aiPrimitiveType_TRIANGLE:     data.ptype = MeshData::PrimitiveType::TRIANGLE; break;

            default: 
                data.ptype = MeshData::PrimitiveType::UNKNOWN;
                JAGE_MSG_ERROR("JAGE mesh error: unknown primitive type, unable to assign indices."); 
                JAGE_LOG_ERROR("Assigning 0 indices to mesh named {}.", ai_mesh->mName.C_Str());
            break;
        }

        if (data.ptype != MeshData::PrimitiveType::UNKNOWN)
        {
            data.indices.reserve(ai_mesh->mNumVertices);
            for (unsigned i {}; i < ai_mesh->mNumFaces; i++)
            {
                aiFace face { ai_mesh->mFaces[i] };

                for (unsigned j {}; j < face.mNumIndices; j++)
                data.indices.push_back(face.mIndices[j]);
            }
        }

        data.vertices.reserve(ai_mesh->mNumVertices);
        for (unsigned i {}; i < ai_mesh->mNumVertices; i++)
        {
            MeshData::VertexData vertex;

            if (ai_mesh->HasPositions())
            {
                aiVector3D aiv_pos { ai_mesh->mVertices[i] };
                vertex.position = glm::vec3{ aiv_pos.x, aiv_pos.y, aiv_pos.z };
            }

            if
            (
                ai_mesh->HasNormals() &&
                ai_mesh->mPrimitiveTypes != aiPrimitiveType::aiPrimitiveType_POINT &&
                ai_mesh->mPrimitiveTypes != aiPrimitiveType::aiPrimitiveType_LINE
            )
            {
                aiVector3D aiv_normal { ai_mesh->mNormals[i] };
                vertex.normal = glm::vec3{ aiv_normal.x, aiv_normal.y, aiv_normal.z };
            }

            for (unsigned j {}; j < vertex.uvcoords.max_size(); j++)
            {
                if (ai_mesh->HasTextureCoords(j))
                {
                    aiVector3D aiv_uvcoord { ai_mesh->mTextureCoords[j][i] };
                    vertex.uvcoords[j] = glm::vec3{ aiv_uvcoord.x, aiv_uvcoord.y, aiv_uvcoord.z };
                }
            }

            for (unsigned j {}; j < vertex.colors.max_size(); j++)
            {
                if (ai_mesh->HasVertexColors(j))
                {
                    aiColor4D aiv_color { ai_mesh->mColors[j][i] };
                    vertex.colors[j] = glm::vec4{ aiv_color.r, aiv_color.g, aiv_color.b, aiv_color.a };
                }
            }

            data.vertices.push_back(std::move(vertex));
        }

        data.material_index = ai_mesh->mMaterialIndex;

        return data;

    }

    std::unique_ptr<ModelNode> process_node(std::vector<MeshData>& meshes, ModelNode* parent, const aiScene* ai_scene, aiNode* ai_node)
    {
        std::unique_ptr<ModelNode> model_node { std::make_unique<ModelNode>() };

        model_node->name = ai_node->mName.C_Str();

        glm::mat4 transformation_matrix { 1.0f };

        for (unsigned i {}; i < 4; i++) for (unsigned j {}; j < 4; j++)
        transformation_matrix[i][j] = ai_node->mTransformation[j][i];

        model_node->transformation_matrix = transformation_matrix;

        for (unsigned i {}; i < ai_node->mNumMeshes; i++)
        {
            model_node->meshes_index.push_back(ai_node->mMeshes[i]);
            aiMesh* ai_mesh { ai_scene->mMeshes[ai_node->mMeshes[i]] };
            meshes.push_back(process_mesh(ai_mesh, ai_scene));
        }

        for (unsigned i {}; i < ai_node->mNumChildren; i++)
        {
            model_node->children.push_back(process_node(meshes, model_node.get(), ai_scene, ai_node->mChildren[i]));
        }

        model_node->parent = parent;

        return model_node;
    }

    struct ModelResource::ModelResource_Impl
    {
        Assimp::Importer importer {};
        const aiScene* ai_scene;
    };

    ModelResource::ModelResource(ResourceManager::Key, std::string_view filename)
    : Resource{ std::string{ dir_path() } + std::string{ filename } }
    , meshes {}
    , impl { std::make_unique<ModelResource_Impl>() }
    {
        JAGE_MSG_TRACE("Loading ModelResource.");

        impl->ai_scene = impl->importer.ReadFile(m_path, aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded);

        if (!impl->ai_scene || impl->ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !impl->ai_scene->mRootNode)
        {
            JAGE_LOG_ERROR("JAGE I/O error: {}", impl->importer.GetErrorString());
            JAGE_MSG_ERROR("Returning empty contents.");
            return;
        }

        print_metadata(impl->ai_scene);

        meshes.reserve(impl->ai_scene->mNumMeshes);

        m_root = process_node(meshes, nullptr, impl->ai_scene, impl->ai_scene->mRootNode);

        JAGE_MSG_TRACE("ModelResource Loaded.");
    }

    ModelResource::~ModelResource() = default;

    const ModelNode* ModelResource::root() const { return m_root.get(); }

    const MeshData* ModelResource::mesh_data(unsigned index) const
    {
        if (index >= impl->ai_scene->mNumMeshes) 
        {
            JAGE_LOG_ERROR
            (
                "JAGE resource error: index out of bounds "s +
                "for number of meshes in ModelResource named {}"s, 
                impl->ai_scene->mName.C_Str()
            );
            return nullptr;
        }

        return &meshes[index];
    }
}