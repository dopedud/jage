#include "JAGE/assets.h"

#include "log.h"

DISABLE_WARNING_PUSH
DISABLE_WARNING_GCC_CLANG("-Wmissing-field-initializers")

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define XXH_INLINE_ALL
#include <xxhash.h>

DISABLE_WARNING_POP

namespace JAGE
{
    fs::path Asset::dir_path() { return fs::current_path() / "assets"; }
    fs::path TextAsset::dir_path() { return "shaders"; }
    fs::path ImageAsset::dir_path() { return "images"; }
    fs::path ModelAsset::dir_path() { return "models"; }

    Asset::Asset(fs::path path)
    : m_path { Asset::dir_path() / path }, m_is_valid {} {}

    fs::path Asset::path() const { return m_path; }
    bool Asset::is_valid() const { return m_is_valid; }

    template<typename T>
    AssetHandle<T>::AssetHandle(AssetID id, T* asset)
    : m_id { id }, m_asset { asset } {}

    template<typename T> AssetID AssetHandle<T>::id() const { return m_id; }
    template<typename T> const T* AssetHandle<T>::asset() const { return m_asset; }

    AssetManager::AssetManager() : assets {}
    { stbi_set_flip_vertically_on_load(true); }

    void AssetManager::Initialise()
    {
        for (const fs::directory_entry& entry : fs::directory_iterator{ Asset::dir_path() / TextAsset::dir_path() })
        load<TextAsset>(entry.path().filename().string());
        for (const fs::directory_entry& entry : fs::directory_iterator{ Asset::dir_path() / ImageAsset::dir_path() })
        load<ImageAsset>(entry.path().filename().string());
        for (const fs::directory_entry& entry : fs::directory_iterator{ Asset::dir_path() / ModelAsset::dir_path() })
        load<ModelAsset>(entry.path().filename().string());

        for (const std::pair<const AssetID, std::unique_ptr<Asset>>& asset : assets)
        {
            ModelAsset* model_asset { dynamic_cast<ModelAsset*>(asset.second.get()) };
            if (!model_asset) continue;
            for (MaterialData& material : model_asset->materials)
            {
                if (material.unloaded_textures.size()) JAGE_MSG_TRACE("Loading external material textures.");
                for (const std::pair<const std::string, MaterialData::TextureType>& unloaded_texture : material.unloaded_textures)
                {
                    load<ImageAsset>(unloaded_texture.first);
                    const ImageData* data { get<ImageAsset>(unloaded_texture.first).asset()->data() };
                    switch (unloaded_texture.second)
                    {
                        case MaterialData::TextureType::ALBEDO: material.albedo_map = data; break;
                        case MaterialData::TextureType::NORMAL: material.normal_map = data; break;
                        case MaterialData::TextureType::SPECULAR: material.specular_map = data; break;
                        default: material.albedo_map = data; break;
                    }
                }
                if (material.unloaded_textures.size()) JAGE_MSG_TRACE("External material textures loaded.");

                material.unloaded_textures.clear();
            }
        }
    }

    AssetManager& AssetManager::instance()
    {
        if (!m_instance) m_instance.reset(new AssetManager());
        return *m_instance;
    }

    void AssetManager::release()
    {
        m_instance.release();
    }

    AssetID AssetManager::path_to_ID(fs::path path)
    { return XXH3_64bits(path.string().c_str(), path.string().size()); }

    template<typename T>
    void AssetManager::load(std::string_view filename) 
    {
        fs::path path { Asset::dir_path() / T::dir_path() / fs::path{ filename } };
        AssetID id_hash { path_to_ID(path) };

        if (assets.find(id_hash) != assets.end())
        { 
            JAGE_LOG_WARN("JAGE asset warning: asset with file name \"{}\" already loaded.", filename);
            return;
        }

        std::unique_ptr<Asset> asset { std::make_unique<T>(Key{}, filename) };
        assets.emplace(id_hash, std::move(asset));
    }

    template<typename T>
    AssetHandle<T> AssetManager::get(std::string_view filename)
    {
        fs::path path { Asset::dir_path() / T::dir_path() / fs::path{ filename } };
        AssetID id_hash { path_to_ID(path) };

        if (assets.find(id_hash) == assets.end())
        { 
            fs::path truncated_path { T::dir_path() / fs::path{ filename } };
            JAGE_LOG_ERROR("JAGE asset error: no asset with \"{}\".", truncated_path.string());
            JAGE_MSG_ERROR("Returning null asset.");
            return AssetHandle<T>{ id_hash, nullptr };
        }

        Asset* asset { assets.find(id_hash)->second.get() };
        return AssetHandle<T>{ id_hash, static_cast<T*>(asset) };
    }

    template class AssetHandle<TextAsset>;
    template class AssetHandle<ImageAsset>;
    template class AssetHandle<ModelAsset>;

    template void                           AssetManager::load<TextAsset>(std::string_view filename);
    template void                           AssetManager::load<ImageAsset>(std::string_view filename);
    template void                           AssetManager::load<ModelAsset>(std::string_view filename);
    template AssetHandle<TextAsset>   AssetManager::get<TextAsset>(std::string_view filename);
    template AssetHandle<ImageAsset>  AssetManager::get<ImageAsset>(std::string_view filename);
    template AssetHandle<ModelAsset>  AssetManager::get<ModelAsset>(std::string_view filename);

    TextAsset::TextAsset(AssetManager::Key, std::string_view filename)
    : Asset{ dir_path() / fs::path{ filename } }
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
            m_is_valid = true;
        }

        catch (const std::ifstream::failure& e)
        {
            JAGE_LOG_ERROR("JAGE I/O error ({} - {}): {}.", e.code().value(), e.code().message(), e.what());
            JAGE_MSG_ERROR("Returning empty contents.");
            m_content = "";
            m_is_valid = false;
        }
    }

    std::string_view TextAsset::content() const { return m_content; }

    ImageAsset::ImageAsset(AssetManager::Key, std::string_view filename)
    : Asset{ dir_path() / fs::path{ filename } }, m_data {}
    {
        JAGE_LOG_TRACE("Loading ImageAsset named \"{}\".", filename);

        int width {}, height {};
        u8* loaded_data
        { 
            stbi_load(m_path.string().c_str(),
            &width, &height, nullptr, STBI_rgb_alpha)
        };

        if (!loaded_data)
        {
            JAGE_LOG_ERROR("JAGE I/O error: {}", stbi_failure_reason());
            JAGE_MSG_ERROR("Returning pink black checkerbox image.");
            m_data = *ImageData::pink_black_checkerbox();
            m_is_valid = false;
            return;
        }

        m_data.width = width;
        m_data.height = height;

        // literal 4 here indicates the desired number of channels the image should have
        // since desired channels was set to 4 upon loading the image via stbi_load, there is no need for variable
        // number of channels
        m_data.pixels.resize(width * height * 4);

        for (unsigned i {}; i < m_data.pixels.size(); i++)
        m_data.pixels[i] = loaded_data[i];

        stbi_image_free(loaded_data);

        m_is_valid = true;
        JAGE_LOG_TRACE("ImageAsset \"{}\" loaded.", filename);
    }

    const ImageData* ImageAsset::data() const
    { 
        if (m_is_valid) return &m_data;
        else return ImageData::pink_black_checkerbox();
    }

    void ImageData::set_pixel(unsigned row, unsigned column, unsigned channel, u8 value)
    { pixels[(row * width + column) * 4 + channel] = value; }

    const ImageData* ImageData::pink_black_checkerbox()
    {
        static ImageData data;

        if (data.pixels.empty())
        {
            unsigned width { 1024 };
            unsigned height { 1024 };

            data.width = width;
            data.height = height;

            data.pixels.resize(width * height * 4);

            for (unsigned i {}; i < width; i++)
            {
                for (unsigned j {}; j < height; j++)
                {
                    data.set_pixel(i, j, 3, U8_MAX);

                    if 
                    (
                        (i < width / 2 && j < height / 2)
                        ||
                        (i > width / 2 && j > height / 2)
                    )
                    {
                        data.set_pixel(i, j, 0, 0);
                        data.set_pixel(i, j, 1, 0);
                        data.set_pixel(i, j, 2, 0);
                    }

                    else
                    {
                        data.set_pixel(i, j, 0, U8_MAX);
                        data.set_pixel(i, j, 1, 0);
                        data.set_pixel(i, j, 2, U8_MAX);
                    }
                }
            }
        }

        return &data;
    }

    struct ModelAsset::Impl
    {
        std::vector<ImageData>* embedded_textures;

        void print_metadata(const aiScene* ai_scene);
        std::unique_ptr<ModelNode> process_node(const aiNode* ai_node, const aiScene* ai_scene, ModelNode* parent);
        MeshData process_mesh(const aiMesh* ai_mesh, const aiScene* ai_scene);
        ImageData process_embedded_texture(const aiTexture* ai_texture, const aiScene* ai_scene);
        MaterialData process_material(const aiMaterial* ai_material, const aiScene* ai_scene);
        const ImageData* get_material_texture(const aiMaterial* ai_material, aiTextureType ai_texturetype, const aiScene* ai_scene, 
            std::unordered_map<std::string, MaterialData::TextureType>& unloaded_textures);
    };

    ModelAsset::ModelAsset(AssetManager::Key, std::string_view filename)
    : Asset{ dir_path() / fs::path{ filename } }
    , meshes {}
    , embedded_textures {}
    , materials {}
    , pimpl { std::make_unique<Impl>() }
    {
        JAGE_LOG_TRACE("Loading ModelAsset named \"{}\".", filename);

        pimpl->embedded_textures = &embedded_textures;

        Assimp::Importer importer {};
        const aiScene* ai_scene
        { 
            importer.ReadFile
            (
                m_path.string(), 
                aiProcessPreset_TargetRealtime_Quality |
                aiProcess_TransformUVCoords
            )
        };

        if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode)
        {
            JAGE_LOG_ERROR("JAGE I/O error: {}", importer.GetErrorString());
            JAGE_MSG_ERROR("Returning empty contents.");
            m_is_valid = false;
            return;
        }

        pimpl->print_metadata(ai_scene);

        JAGE_MSG_TRACE("Processing model nodes.");
        m_root = pimpl->process_node(ai_scene->mRootNode, ai_scene, nullptr);
        JAGE_MSG_TRACE("Model nodes processed.");

        if (ai_scene->mNumMeshes) JAGE_MSG_TRACE("Processing meshes.");
        for (unsigned i {}; i < ai_scene->mNumMeshes; i++)
        meshes.push_back(pimpl->process_mesh(ai_scene->mMeshes[i], ai_scene));
        if (ai_scene->mNumMeshes) JAGE_MSG_TRACE("Meshes processed.");

        if (ai_scene->mNumTextures) JAGE_MSG_TRACE("Processing embedded material textures.");
        for (unsigned i {}; i < ai_scene->mNumTextures; i++)
        embedded_textures.push_back(pimpl->process_embedded_texture(ai_scene->mTextures[i], ai_scene));
        if (ai_scene->mNumTextures) JAGE_MSG_TRACE("Embedded material textures processed.");

        if (ai_scene->mNumMaterials) JAGE_MSG_TRACE("Processing materials.");
        for (unsigned i {}; i < ai_scene->mNumMaterials; i++)
        materials.push_back(pimpl->process_material(ai_scene->mMaterials[i], ai_scene));
        if (ai_scene->mNumMaterials) JAGE_MSG_TRACE("Materials processed.");

        m_is_valid = true;
        JAGE_LOG_TRACE("ModelAsset \"{}\" loaded.", filename);
    }

    ModelAsset::~ModelAsset() = default;

    const ModelNode* ModelAsset::root() const { return m_root.get(); }

    const MeshData* ModelAsset::mesh_data(unsigned index) const
    {
        if (index >= meshes.size())
        {
            JAGE_LOG_ERROR
            (
                "JAGE asset error: index out of bounds "s +
                "for number of meshes in ModelAsset named \"{}\"."s,
                m_path.filename().string()
            );
            JAGE_MSG_ERROR("Returning nullptr.");
            return nullptr;
        }

        return &meshes[index];
    }

    const MaterialData* ModelAsset::material_data(unsigned index) const
    {
        if (index >= materials.size())
        {
            JAGE_LOG_ERROR
            (
                "JAGE asset error: index out of bounds "s +
                "for number of materials in ModelAsset named \"{}\"."s,
                m_path.filename().string()
            );
            JAGE_MSG_ERROR("Returning nullptr.");
            return nullptr;
        }

        return &materials[index];
    }

    void ModelAsset::Impl::print_metadata(const aiScene* ai_scene)
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

        JAGE_LOG_TRACE("    Model contains {} embedded texture(s).", ai_scene->mNumTextures);

        std::string matprop_count {};
        for (unsigned i {}; i < ai_scene->mNumMaterials; i++)
        matprop_count += " " + std::to_string(ai_scene->mMaterials[i]->mNumProperties) + ",";
        if (!matprop_count.empty()) matprop_count.back() = '.';

        JAGE_LOG_TRACE
        (
            "    Model contains {} material(s), with number of properties from each material by order:{}",
            ai_scene->mNumMaterials,
            matprop_count
        );

        #define VERBOSE

        // define the VERBOSE macro to print out each material property in each material
        #ifdef VERBOSE
        JAGE_MSG_TRACE("Material information:");
        for (unsigned i {}; i < ai_scene->mNumMaterials; i++)
        {
            JAGE_LOG_TRACE("MATERIAL {}:", i);
            for (unsigned j {}; j < ai_scene->mMaterials[i]->mNumProperties; j++)
            {
                const aiMaterialProperty& matprop { *ai_scene->mMaterials[i]->mProperties[j] };
                std::string array_str {};
                switch (matprop.mType)
                {
                    case aiPropertyTypeInfo::aiPTI_String:
                    JAGE_LOG_TRACE("    {}: {}", matprop.mKey.C_Str(), reinterpret_cast<aiString*>(matprop.mData)->C_Str());
                    break;

                    case aiPropertyTypeInfo::aiPTI_Integer:
                        for (unsigned k {}; k < matprop.mDataLength; k++)
                        array_str += " " + std::to_string(reinterpret_cast<i32*>(matprop.mData)[k]) + ",";
                        if (!array_str.empty()) array_str.back() = '.';
                        JAGE_LOG_TRACE("    {}:{}", matprop.mKey.C_Str(), array_str);
                    break;

                    case aiPropertyTypeInfo::aiPTI_Float: 
                        for (unsigned k {}; k < matprop.mDataLength; k++)
                        array_str += " " + std::to_string(reinterpret_cast<float*>(matprop.mData)[k]) + ",";
                        if (!array_str.empty()) array_str.back() = '.';
                        JAGE_LOG_TRACE("    {}:{}", matprop.mKey.C_Str(), array_str);
                    break;

                    case aiPropertyTypeInfo::aiPTI_Double:
                        for (unsigned k {}; k < matprop.mDataLength; k++)
                        array_str += " " + std::to_string(reinterpret_cast<double*>(matprop.mData)[k]) + ",";
                        if (!array_str.empty()) array_str.back() = '.';
                        JAGE_LOG_TRACE("    {}:{}", matprop.mKey.C_Str(), array_str);
                    break;

                    default: JAGE_LOG_TRACE("    {}: {}", matprop.mKey.C_Str(), "material property not recognized.");
                }
            }
        }
        #undef VERBOSE
        #endif

        JAGE_MSG_TRACE("Metadata information:");

        aiMetadata metadata { *ai_scene->mMetaData };

        for (unsigned i {}; i < metadata.mNumProperties; i++)
        {
            switch (metadata.mValues[i].mType)
            {
                case aiMetadataType::AI_BOOL:           JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<bool*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_UINT32:         JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<u32*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_UINT64:         JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<u64*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_INT32:          JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<i32*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_INT64:          JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<i64*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_FLOAT:          JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<float*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_DOUBLE:         JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<double*>(metadata.mValues[i].mData)); break;
                case aiMetadataType::AI_AISTRING:       JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), static_cast<aiString*>(metadata.mValues[i].mData)->C_Str()); break;
                
                case aiMetadataType::AI_AIVECTOR3D:
                {
                    const aiVector3D& ai_vector { *static_cast<aiVector3D*>(metadata.mValues[i].mData) };
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

    std::unique_ptr<ModelNode> ModelAsset::Impl::process_node(const aiNode* ai_node, const aiScene* ai_scene, ModelNode* parent)
    {
        std::unique_ptr<ModelNode> model_node { std::make_unique<ModelNode>() };

        model_node->name = ai_node->mName.C_Str();

        for (unsigned i {}; i < 4; i++) for (unsigned j {}; j < 4; j++)
        model_node->transformation_matrix[i][j] = ai_node->mTransformation[j][i];

        for (unsigned i {}; i < ai_node->mNumMeshes; i++)
        model_node->meshes_index.push_back(ai_node->mMeshes[i]);

        for (unsigned i {}; i < ai_node->mNumChildren; i++)
        model_node->children.push_back(process_node(ai_node->mChildren[i], ai_scene, model_node.get()));

        model_node->parent = parent;

        return model_node;
    }

    MeshData ModelAsset::Impl::process_mesh(const aiMesh* ai_mesh, const aiScene* ai_scene)
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
                JAGE_LOG_ERROR("Assigning 0 indices to mesh named \"{}\".", ai_mesh->mName.C_Str());
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
                    vertex.uvcoords[j] = glm::vec2{ aiv_uvcoord.x, aiv_uvcoord.y };
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

    ImageData ModelAsset::Impl::process_embedded_texture(const aiTexture* ai_texture, const aiScene* ai_scene)
    {
        ImageData data;

        // texture is compressed
        if (ai_texture->mHeight == 0)
        {
            int width {}, height {};
            u8* loaded_data
            { 
                stbi_load_from_memory(reinterpret_cast<u8*>(ai_texture->pcData),
                ai_texture->mWidth, &width, &height, nullptr, STBI_rgb_alpha)
            };

            if (!loaded_data)
            {
                JAGE_LOG_ERROR("JAGE I/O error: failed to load embedded material texture named \"{}\".", ai_texture->mFilename.C_Str());
                JAGE_LOG_ERROR("Reason: {}.", stbi_failure_reason());
                JAGE_MSG_ERROR("Returning pink black checkerbox image.");
                data = *ImageData::pink_black_checkerbox();
            }

            else
            {
                data.width = width;
                data.height = height;

                data.pixels.resize(width * height * 4);

                for (unsigned i {}; i < data.pixels.size(); i++) data.pixels[i] = loaded_data[i];

                stbi_image_free(loaded_data);
            }
        }

        // texture is uncompressed
        else
        {
            data.width = ai_texture->mWidth;
            data.height = ai_texture->mHeight;

            data.pixels.resize(ai_texture->mWidth * ai_texture->mHeight * 4);

            aiTexel* ai_texels { ai_texture->pcData };

            for (unsigned i {}; i < ai_texture->mWidth * ai_texture->mHeight; i++)
            {
                data.pixels[i * 4 + 0] = ai_texels[i].r;
                data.pixels[i * 4 + 1] = ai_texels[i].g;
                data.pixels[i * 4 + 2] = ai_texels[i].b;
                data.pixels[i * 4 + 3] = ai_texels[i].a;
            }
        }

        return data;
    }

    MaterialData ModelAsset::Impl::process_material(const aiMaterial* ai_material, const aiScene* ai_scene)
    {
        MaterialData data;

        data.name = ai_material->GetName().C_Str();

        aiColor4D diffuse_color;
        if (ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse_color) == aiReturn::aiReturn_SUCCESS)
        {
            data.albedo_color.r = diffuse_color.r;
            data.albedo_color.g = diffuse_color.g;
            data.albedo_color.b = diffuse_color.b;
            data.albedo_color.a = diffuse_color.a;
        }

        data.albedo_map = get_material_texture(ai_material, aiTextureType::aiTextureType_DIFFUSE, ai_scene, data.unloaded_textures);

        aiColor4D normal_color;
        if (ai_material->Get(AI_MATKEY_COLOR_SPECULAR, normal_color) == aiReturn::aiReturn_SUCCESS)
        {
            data.normal_color.r = normal_color.r;
            data.normal_color.g = normal_color.g;
            data.normal_color.b = normal_color.b;
            data.normal_color.a = normal_color.a;
        }

        data.normal_map = get_material_texture(ai_material, aiTextureType::aiTextureType_NORMALS, ai_scene, data.unloaded_textures);

        aiColor4D specular_color;
        if (ai_material->Get(AI_MATKEY_COLOR_SPECULAR, specular_color) == aiReturn::aiReturn_SUCCESS)
        {
            data.specular_color.r = specular_color.r;
            data.specular_color.g = specular_color.g;
            data.specular_color.b = specular_color.b;
            data.specular_color.a = specular_color.a;
        }

        data.specular_map = get_material_texture(ai_material, aiTextureType::aiTextureType_SPECULAR, ai_scene, data.unloaded_textures);

        return data;
    }

    static MaterialData::TextureType aiTextureType_ToTextureType(aiTextureType ai_texturetype)
    {
        switch (ai_texturetype)
        {
            case aiTextureType::aiTextureType_DIFFUSE: return MaterialData::TextureType::ALBEDO;
            case aiTextureType::aiTextureType_NORMALS: return MaterialData::TextureType::NORMAL;
            case aiTextureType::aiTextureType_SPECULAR: return MaterialData::TextureType::SPECULAR;
            default: return MaterialData::TextureType::NONE;
        }
    }

    // function to process and get material textures, stored embedded or externally
    // for now process and get only a texture for a texture type, might need to rewrite to support process multiple
    // textures for a texture type in the future
    const ImageData* ModelAsset::Impl::get_material_texture
    (
        const aiMaterial* ai_material,
        aiTextureType ai_texturetype,
        const aiScene* ai_scene,
        std::unordered_map<std::string, MaterialData::TextureType>& unloaded_textures
    )
    {
        if (ai_material->GetTextureCount(ai_texturetype) > 0)
        {
            aiString ai_texture_path_str {};
            ai_material->GetTexture(ai_texturetype, 0, &ai_texture_path_str);

            std::string filename { fs::path{ ai_texture_path_str.C_Str() }.filename().string() };

            std::pair<const aiTexture*, int> ai_texture_index { ai_scene->GetEmbeddedTextureAndIndex(filename.c_str()) };

            // load textures from memory (embedded)
            if (ai_texture_index.first) return &(*(embedded_textures))[ai_texture_index.second];

            // load textures externally
            else
            {
                JAGE_MSG_WARN("Loading textures externally, deferring operations later.");
                JAGE_MSG_WARN("This might be a bad design, but it is good for now.");
                JAGE_MSG_WARN("Returning pink black checkerbox image.");
                unloaded_textures.emplace(filename, aiTextureType_ToTextureType(ai_texturetype));
                return ImageData::pink_black_checkerbox();
            }
        }

        else
        {
            JAGE_LOG_WARN("JAGE asset warning: texture type {} for material named \"{}\" does not exist.", 
                aiTextureTypeToString(ai_texturetype), ai_material->GetName().C_Str());
            JAGE_MSG_WARN("Returning pink black checkerbox image.");
            return ImageData::pink_black_checkerbox();
        }
    }
}