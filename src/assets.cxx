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
    fs::path AssetBase::dir_path() { return fs::current_path() / "assets"; }

    AssetBase::AssetBase(fs::path path)
    : m_uri {}
    , m_path { dir_path() / path }
    , m_valid {} {}

    Data::URI AssetBase::uri() const { return m_uri; }
    fs::path AssetBase::path() const { return m_path; }
    bool AssetBase::is_valid() const { return m_valid; }

    template<typename T>
    AssetHandle<T>::AssetHandle(AssetID id, T* asset)
    : m_id { id }, m_asset { asset } {}

    template<typename T> AssetID AssetHandle<T>::id() const { return m_id; }
    template<typename T> const T* AssetHandle<T>::asset() const { return m_asset; }

    template class AssetHandle<Asset::Text>;
    template class AssetHandle<Asset::Image>;
    template class AssetHandle<Asset::Model>;

    AssetManager::AssetManager()
    : text_assets {}
    , image_assets {}
    , model_assets {}
    // might need to disable Assimp's flip UVs post-processing step after importing a model, or disable
    // stb_image's flip images vertically upon loading
    // either one should be disabled
    // { stbi_set_flip_vertically_on_load(true); }
    {}

    // TEMPLATE SPECIALISATIONS
    // NOTE: Template specialisations are put here early in this file because other code down below depends on it.

    template<typename T>
    void AssetManager::load(std::unordered_map<AssetID, std::unique_ptr<T>>& asset_map, std::string_view filename)
    {
        // TODO: move the below line to each asset's constructor
        fs::path path { AssetBase::dir_path() / T::dir_path() / fs::path { filename } };
        AssetID id { str_to_ID(path.string()) };

        if (asset_map.find(id) != asset_map.end())
        {
            JAGE_LOG_WARN("JAGE asset warning: asset with file name \"{}\" already loaded.", filename);
            return;
        }

        std::unique_ptr<T> asset { std::make_unique<T>(Key{}, filename) };
        asset_map.emplace(id, std::move(asset));
    }

    template<typename T>
    AssetHandle<T> AssetManager::get(std::unordered_map<AssetID, std::unique_ptr<T>>& asset_map, std::string_view filename)
    {
        fs::path path { AssetBase::dir_path() / T::dir_path() / fs::path { filename } };
        AssetID id { str_to_ID(path.string()) };

        typename std::unordered_map<AssetID, std::unique_ptr<T>>::iterator assets_it { asset_map.find(id) };

        if (assets_it == asset_map.end())
        { 
            fs::path truncated_path { T::dir_path() / fs::path{ filename } };
            JAGE_LOG_ERROR("JAGE asset error: no asset with file name \"{}\".", truncated_path.string());
            JAGE_MSG_ERROR("Returning null asset.");
            return AssetHandle<T>{ id, nullptr };
        }

        T* asset { assets_it->second.get() };
        return AssetHandle<T>{ id, asset };
    }

    template<> void                         AssetManager::Load<Asset::Text>(std::string_view filename)      { load<Asset::Text>(text_assets, filename); }
    template<> void                         AssetManager::Load<Asset::Image>(std::string_view filename)     { load<Asset::Image>(image_assets, filename); }
    template<> void                         AssetManager::Load<Asset::Model>(std::string_view filename)     { load<Asset::Model>(model_assets, filename); }
    template<> AssetHandle<Asset::Text>     AssetManager::Get<Asset::Text>(std::string_view filename)       { return get<Asset::Text>(text_assets, filename); }
    template<> AssetHandle<Asset::Image>    AssetManager::Get<Asset::Image>(std::string_view filename)      { return get<Asset::Image>(image_assets, filename); }
    template<> AssetHandle<Asset::Model>    AssetManager::Get<Asset::Model>(std::string_view filename)      { return get<Asset::Model>(model_assets, filename); }

    // END TEMPLATE SPECIALISATIONS

    void AssetManager::Initialise()
    {
        JAGE_MSG_INFO("Loading assets...");

        try { fs::directory_iterator{ AssetBase::dir_path() }; }
        catch (const fs::filesystem_error& e)
        {
            JAGE_LOG_ERROR("JAGE I/O error ({} - {}) at path \"{}\" and \"{}\": {}.",
                e.code().value(), e.code().message(), e.path1().string(), e.path2().string(), e.what());
            return;
        }

        for (const fs::directory_entry& entry : fs::directory_iterator{ AssetBase::dir_path() / Asset::Text::dir_path() })
        Load<Asset::Text>(entry.path().filename().string());
        for (const fs::directory_entry& entry : fs::directory_iterator{ AssetBase::dir_path() / Asset::Image::dir_path() })
        Load<Asset::Image>(entry.path().filename().string());
        for (const fs::directory_entry& entry : fs::directory_iterator{ AssetBase::dir_path() / Asset::Model::dir_path() })
        Load<Asset::Model>(entry.path().filename().string());

        for (const std::pair<const AssetID, std::unique_ptr<Asset::Model>>& asset : model_assets)
        {
            Asset::Model* model_asset { asset.second.get() };
            for (Data::Material& material : model_asset->materials)
            {
                if (material.unloaded_textures.size()) JAGE_MSG_TRACE("Loading external material textures.");
                for (const std::pair<const std::string, Data::Material::TextureType>& unloaded_texture : material.unloaded_textures)
                {
                    Load<Asset::Image>(unloaded_texture.first);
                    const Data::Image* data { Get<Asset::Image>(unloaded_texture.first).asset()->data() };
                    switch (unloaded_texture.second)
                    {
                        case Data::Material::TextureType::ALBEDO: material.albedo_map = data; break;
                        case Data::Material::TextureType::NORMAL: material.normal_map = data; break;
                        case Data::Material::TextureType::SPECULAR: material.specular_map = data; break;
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

    void AssetManager::release() { m_instance.release(); }

    AssetID AssetManager::str_to_ID(std::string_view str)
    { return XXH3_64bits(str.data(), str.size()); }

    static Data::Material::TextureType aiTextureType_ToTextureType(aiTextureType ai_texturetype)
    {
        switch (ai_texturetype)
        {
            case aiTextureType::aiTextureType_DIFFUSE:      return Data::Material::TextureType::ALBEDO;
            case aiTextureType::aiTextureType_NORMALS:      return Data::Material::TextureType::NORMAL;
            case aiTextureType::aiTextureType_SPECULAR:     return Data::Material::TextureType::SPECULAR;
            default: return Data::Material::TextureType::NONE;
        }
    }

    namespace Asset
    {
        fs::path Text::dir_path() { return "shaders"; }
        fs::path Image::dir_path() { return "images"; }
        fs::path Model::dir_path() { return "models"; }

        Text::Text(AssetManager::Key, std::string_view filename)
        : AssetBase{ dir_path() / fs::path{ filename } }, m_content {}
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
                m_valid = true;
            }
            catch (const std::ifstream::failure& e)
            {
                JAGE_LOG_ERROR("JAGE I/O error ({} - {}): {}.", e.code().value(), e.code().message(), e.what());
                JAGE_MSG_ERROR("Returning empty contents.");
                m_content = "";
                m_valid = false;
            }
        }

        std::string_view Text::content() const { return m_content; }

        Image::Image(AssetManager::Key, std::string_view filename)
        : AssetBase{ dir_path() / fs::path{ filename } }, m_data {}
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
                m_data = *Data::Image::pink_black_checkerbox();
                m_valid = false;
                return;
            }

            m_data.width = width;
            m_data.height = height;

            // literal 4 here indicates the desired number of channels the image should have
            // since desired channels was set to 4 upon loading the image via stbi_load, there is no need for variable
            // number of channels
            m_data.pixels.resize(width * height * 4);

            for (size_t i {}; i < m_data.pixels.size(); i++)
            m_data.pixels[i] = loaded_data[i];

            stbi_image_free(loaded_data);

            m_valid = true;
            JAGE_LOG_TRACE("ImageAsset \"{}\" loaded.", filename);
        }

        const Data::Image* Image::data() const
        { 
            if (m_valid) return &m_data;
            else return Data::Image::pink_black_checkerbox();
        }

        struct Model::Impl
        {
            std::vector<Data::Image>* embedded_textures;

            void print_metadata(const aiScene* ai_scene);
            std::unique_ptr<Model::Node>    process_node(const aiNode* ai_node, const aiScene* ai_scene, Model::Node* parent);
            Data::Mesh                      process_mesh(const aiMesh* ai_mesh, const aiScene* ai_scene);
            Data::Image                     process_embedded_texture(const aiTexture* ai_texture, const aiScene* ai_scene);
            Data::Material                  process_material(const aiMaterial* ai_material, const aiScene* ai_scene);
            const Data::Image*              get_material_texture(const aiMaterial* ai_material, aiTextureType ai_texturetype,
                                            const aiScene* ai_scene,
                                            std::unordered_map<std::string, Data::Material::TextureType>& unloaded_textures);
        };

        Model::Model(AssetManager::Key, std::string_view filename)
        : AssetBase{ dir_path() / fs::path{ filename } }
        , meshes {}
        , embedded_textures {}
        , materials {}
        , pimpl { std::make_unique<Impl>() }
        {
            JAGE_LOG_TRACE("Loading ModelAsset named \"{}\".", filename);

            pimpl->embedded_textures = &embedded_textures;

            // TODO: transform FBX models so that it matches engine's coordinate system
            // Somehow a FBX model is rotated 90 degrees along the X-axis upon import.
            Assimp::Importer importer {};

            const aiScene *ai_scene
            {
                importer.ReadFile
                (
                    m_path.string(),
                    aiProcess_MakeLeftHanded |
                    // might need to disable Assimp's flip UVs post-processing step after importing a model, or disable
                    // stb_image's flip images vertically upon loading
                    // either one should be disabled
                    aiProcess_FlipUVs |
                    aiProcess_TransformUVCoords |
                    aiProcessPreset_TargetRealtime_Quality
                )
            };

            if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode)
            {
                JAGE_LOG_ERROR("JAGE I/O error: {}", importer.GetErrorString());
                JAGE_MSG_ERROR("Returning empty contents.");
                m_valid = false;
                return;
            }

            pimpl->print_metadata(ai_scene);

            JAGE_MSG_TRACE("Processing model nodes.");
            m_root = pimpl->process_node(ai_scene->mRootNode, ai_scene, nullptr);
            JAGE_MSG_TRACE("Model nodes processed.");

            if (ai_scene->mNumMeshes) JAGE_MSG_TRACE("Processing meshes.");
            for (size_t i {}; i < ai_scene->mNumMeshes; i++)
            meshes.push_back(pimpl->process_mesh(ai_scene->mMeshes[i], ai_scene));
            if (ai_scene->mNumMeshes) JAGE_MSG_TRACE("Meshes processed.");

            if (ai_scene->mNumTextures) JAGE_MSG_TRACE("Processing embedded material textures.");
            for (size_t i {}; i < ai_scene->mNumTextures; i++)
            embedded_textures.push_back(pimpl->process_embedded_texture(ai_scene->mTextures[i], ai_scene));
            if (ai_scene->mNumTextures) JAGE_MSG_TRACE("Embedded material textures processed.");

            if (ai_scene->mNumMaterials) JAGE_MSG_TRACE("Processing materials.");
            for (size_t i {}; i < ai_scene->mNumMaterials; i++)
            materials.push_back(pimpl->process_material(ai_scene->mMaterials[i], ai_scene));
            if (ai_scene->mNumMaterials) JAGE_MSG_TRACE("Materials processed.");

            m_valid = true;
            JAGE_LOG_TRACE("ModelAsset \"{}\" loaded.", filename);
        }

        Model::~Model() = default;

        const Model::Node* Model::root() const { return m_root.get(); }

        const Data::Mesh* Model::meshdata(unsigned index) const
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

        const Data::Material* Model::materialdata(unsigned index) const
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

        void Model::Impl::print_metadata(const aiScene* ai_scene)
        {
            JAGE_MSG_TRACE("Model information:");

            std::string vertices_count {};
            for (size_t i {}; i < ai_scene->mNumMeshes; i++)
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
            for (size_t i {}; i < ai_scene->mNumMaterials; i++)
            matprop_count += " " + std::to_string(ai_scene->mMaterials[i]->mNumProperties) + ",";
            if (!matprop_count.empty()) matprop_count.back() = '.';

            JAGE_LOG_TRACE
            (
                "    Model contains {} material(s), with number of properties from each material by order:{}",
                ai_scene->mNumMaterials,
                matprop_count
            );

            // #define VERBOSE

            // define the VERBOSE macro to print out each material property in each material
            #ifdef VERBOSE
            JAGE_MSG_TRACE("Material information:");
            for (size_t i {}; i < ai_scene->mNumMaterials; i++)
            {
                JAGE_LOG_TRACE("MATERIAL {}:", i);
                for (size_t j {}; j < ai_scene->mMaterials[i]->mNumProperties; j++)
                {
                    const aiMaterialProperty& matprop { *ai_scene->mMaterials[i]->mProperties[j] };
                    std::string array_str {};
                    switch (matprop.mType)
                    {
                        case aiPropertyTypeInfo::aiPTI_String:
                        JAGE_LOG_TRACE("    {}: {}", matprop.mKey.C_Str(), reinterpret_cast<aiString*>(matprop.mData)->C_Str());
                        break;

                        case aiPropertyTypeInfo::aiPTI_Integer:
                            for (size_t k {}; k < matprop.mDataLength; k++)
                            array_str += " " + std::to_string(reinterpret_cast<i32*>(matprop.mData)[k]) + ",";
                            if (!array_str.empty()) array_str.back() = '.';
                            JAGE_LOG_TRACE("    {}:{}", matprop.mKey.C_Str(), array_str);
                        break;

                        case aiPropertyTypeInfo::aiPTI_Float: 
                            for (size_t k {}; k < matprop.mDataLength; k++)
                            array_str += " " + std::to_string(reinterpret_cast<float*>(matprop.mData)[k]) + ",";
                            if (!array_str.empty()) array_str.back() = '.';
                            JAGE_LOG_TRACE("    {}:{}", matprop.mKey.C_Str(), array_str);
                        break;

                        case aiPropertyTypeInfo::aiPTI_Double:
                            for (size_t k {}; k < matprop.mDataLength; k++)
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

            for (size_t i {}; i < metadata.mNumProperties; i++)
            {
                switch (metadata.mValues[i].mType)
                {
                    case aiMetadataType::AI_BOOL:       JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<bool*>(metadata.mValues[i].mData)); break;
                    case aiMetadataType::AI_UINT32:     JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<u32*>(metadata.mValues[i].mData)); break;
                    case aiMetadataType::AI_UINT64:     JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<u64*>(metadata.mValues[i].mData)); break;
                    case aiMetadataType::AI_INT32:      JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<i32*>(metadata.mValues[i].mData)); break;
                    case aiMetadataType::AI_INT64:      JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<i64*>(metadata.mValues[i].mData)); break;
                    case aiMetadataType::AI_FLOAT:      JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<float*>(metadata.mValues[i].mData)); break;
                    case aiMetadataType::AI_DOUBLE:     JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), *static_cast<double*>(metadata.mValues[i].mData)); break;
                    case aiMetadataType::AI_AISTRING:   JAGE_LOG_TRACE("    {}: {}", metadata.mKeys[i].C_Str(), static_cast<aiString*>(metadata.mValues[i].mData)->C_Str()); break;
                    
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

        std::unique_ptr<Model::Node> Model::Impl::process_node(const aiNode* ai_node, const aiScene* ai_scene, Model::Node* parent)
        {
            std::unique_ptr<Model::Node> model_node { std::make_unique<Model::Node>() };

            model_node->name = ai_node->mName.C_Str();

            for (size_t i {}; i < 4; i++) for (unsigned j {}; j < 4; j++)
            model_node->transformation_matrix[i][j] = ai_node->mTransformation[j][i];

            for (size_t i {}; i < ai_node->mNumMeshes; i++)
            model_node->meshes_index.push_back(ai_node->mMeshes[i]);

            for (size_t i {}; i < ai_node->mNumChildren; i++)
            model_node->children.push_back(process_node(ai_node->mChildren[i], ai_scene, model_node.get()));

            model_node->parent = parent;

            return model_node;
        }

        Data::Mesh Model::Impl::process_mesh(const aiMesh* ai_mesh, const aiScene* ai_scene)
        {
            Data::Mesh data;

            data.name = ai_mesh->mName.C_Str();

            switch (ai_mesh->mPrimitiveTypes)
            {
                case aiPrimitiveType::aiPrimitiveType_POINT:        data.ptype = Data::Mesh::PrimitiveType::POINT; break;
                case aiPrimitiveType::aiPrimitiveType_LINE:         data.ptype = Data::Mesh::PrimitiveType::LINE; break;
                case aiPrimitiveType::aiPrimitiveType_TRIANGLE:     data.ptype = Data::Mesh::PrimitiveType::TRIANGLE; break;

                default: 
                    data.ptype = Data::Mesh::PrimitiveType::UNKNOWN;
                    JAGE_MSG_ERROR("JAGE mesh error: unknown primitive type, unable to assign indices."); 
                    JAGE_LOG_ERROR("Assigning 0 indices to mesh named \"{}\".", ai_mesh->mName.C_Str());
                break;
            }

            if (data.ptype != Data::Mesh::PrimitiveType::UNKNOWN)
            {
                data.indices.reserve(ai_mesh->mNumVertices);
                for (size_t i {}; i < ai_mesh->mNumFaces; i++)
                {
                    aiFace face { ai_mesh->mFaces[i] };

                    for (size_t j {}; j < face.mNumIndices; j++)
                    data.indices.push_back(face.mIndices[j]);
                }
            }

            data.vertices.reserve(ai_mesh->mNumVertices);
            for (size_t i {}; i < ai_mesh->mNumVertices; i++)
            {
                Data::Mesh::Vertex vertex;

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

                for (size_t j {}; j < vertex.uvcoords.max_size(); j++)
                {
                    if (ai_mesh->HasTextureCoords(j))
                    {
                        aiVector3D aiv_uvcoord { ai_mesh->mTextureCoords[j][i] };
                        vertex.uvcoords[j] = glm::vec2{ aiv_uvcoord.x, aiv_uvcoord.y };
                    }
                }

                for (size_t j {}; j < vertex.colors.max_size(); j++)
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

        Data::Image Model::Impl::process_embedded_texture(const aiTexture* ai_texture, const aiScene* ai_scene)
        {
            Data::Image data;

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
                    data = *Data::Image::pink_black_checkerbox();
                } else
                {
                    data.width = width;
                    data.height = height;

                    data.pixels.resize(width * height * 4);

                    for (size_t i {}; i < data.pixels.size(); i++) data.pixels[i] = loaded_data[i];

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

                for (size_t i {}; i < ai_texture->mWidth * ai_texture->mHeight; i++)
                {
                    data.pixels[i * 4 + 0] = ai_texels[i].r;
                    data.pixels[i * 4 + 1] = ai_texels[i].g;
                    data.pixels[i * 4 + 2] = ai_texels[i].b;
                    data.pixels[i * 4 + 3] = ai_texels[i].a;
                }
            }

            return data;
        }

        Data::Material Model::Impl::process_material(const aiMaterial* ai_material, const aiScene* ai_scene)
        {
            Data::Material data;

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

            data.normal_map = get_material_texture(ai_material, aiTextureType::aiTextureType_NORMALS, ai_scene, data.unloaded_textures);

            ai_real specular_factor {};
            if (ai_material->Get(AI_MATKEY_SPECULAR_FACTOR, specular_factor) == aiReturn::aiReturn_SUCCESS)
            data.specular_factor = specular_factor;
            data.specular_map = get_material_texture(ai_material, aiTextureType::aiTextureType_SPECULAR, ai_scene, data.unloaded_textures);

            return data;
        }

        // function to process and get material textures, stored embedded or externally
        // for now process and get only a texture for a texture type, might need to rewrite to support process multiple
        // textures for a texture type in the future
        const Data::Image* Model::Impl::get_material_texture
        (
            const aiMaterial* ai_material,
            aiTextureType ai_texturetype,
            const aiScene* ai_scene,
            std::unordered_map<std::string, Data::Material::TextureType>& unloaded_textures
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
                    return Data::Image::pink_black_checkerbox();
                }
            }

            else
            {
                JAGE_LOG_WARN("JAGE asset warning: texture type {} for material named \"{}\" does not exist.", 
                    aiTextureTypeToString(ai_texturetype), ai_material->GetName().C_Str());
                JAGE_MSG_WARN("Returning pink black checkerbox image.");
                return Data::Image::pink_black_checkerbox();
            }
        }
    }

    namespace Data
    {
        void Image::set_pixel(unsigned row, unsigned column, unsigned channel, u8 value)
        { pixels[(row * width + column) * 4 + channel] = value; }

        const Image* Image::pink_black_checkerbox()
        {
            static Image data;

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
                        } else
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
    }


}