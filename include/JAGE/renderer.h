#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"
#include "JAGE/assets.h"

namespace JAGE
{
    /**
     * @namespace Resource
     * 
     * @brief The `Resource` namespace that contains representations of different GPU resources.
     * 
     * "Resource" in the context of game engines can refer to a wide variety of meaning, including memory resources and
     * persistent resources (files that live on the hard disk). However in JAGE specifically, "Resource" means GPU
     * resource, which are data that is uploaded from CPU to GPU, and stay in GPU memory. It could also represent
     * graphics resources that are not directly associated with memory on the GPU, such as materials.
     */
    namespace Resource
    {
        using ID = u64;

        template<typename T>
        class Handle
        {
        public:
            Handle(ID id, T* resource);

            ID id() const;
            const T* resource() const;
        private:
            ID m_id;
            T* m_resource;
        };

        /**
         * @class Resource::Base
         * 
         * @brief The `Resource::Base` class that acts as a base class for all the different types of GPU resources to
         * derive from.
         * 
         */
        class JAGE_API Base
        {
        public:
            static LogicalPath dir_path();

            Base(Data::URI uri);
            virtual ~Base() = default;

            Data::URI uri() const;
            bool is_valid() const;
        protected:
            Data::URI m_uri;
            bool m_valid;
        };

        class JAGE_API Shader : public Base
        {
        public:
            static LogicalPath dir_path();

            enum class DataType : u8
            {
                None = 0,
                Float, Float2, Float3, Float4,
                Int, Int2, Int3, Int4,
                Mat3, Mat4,
                Bool
            };

            static unsigned datatype_size(DataType datatype);

            static std::unique_ptr<Shader> Create
            (
                std::string_view vertex_str,
                std::string_view fragment_str,
                std::string_view geometry_str = ""
            );
            virtual ~Shader() = default;

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual void set_uniform_bool       (std::string_view name, bool value) = 0;
            virtual void set_uniform_uint       (std::string_view name, unsigned value) = 0;
            virtual void set_uniform_int        (std::string_view name, int value) = 0;
            virtual void set_uniform_float      (std::string_view name, float value) = 0;
            virtual void set_uniform_float2     (std::string_view name, const glm::vec2& value) = 0;
            virtual void set_uniform_float3     (std::string_view name, const glm::vec3& value) = 0;
            virtual void set_uniform_float4     (std::string_view name, const glm::vec4& value) = 0;
            virtual void set_uniform_mat4       (std::string_view name, const glm::mat4& value) = 0;
        };

        class JAGE_API Material : public Base
        {
        public:
            static LogicalPath dir_path();

            enum class FaceCullingMode : u8 { NONE = 0, BACK, FRONT };

            Material();

            static Material Create(Shader* shader, const Data::Material* materialdata);

            Shader* shader() const;
            const Data::Material* materialdata() const;
            Texture* albedo_texture() const;

            FaceCullingMode face_culling_mode() const;
            void set_face_culling_mode(FaceCullingMode mode);
        private:
            Material(Shader* shader, const Data::Material* materialdata);

            Shader* m_shader;
            const Data::Material* m_materialdata;
            std::unique_ptr<Texture> m_albedo_texture;
            FaceCullingMode m_face_culling_mode;
        };
    }

    class JAGE_API Texture
    {
    public:
        static std::unique_ptr<Texture> Create(const Data::Image* imagedata);
        virtual ~Texture() = default;

        virtual void bind(unsigned unit) const = 0;
        virtual void unbind() const = 0;
    };

    class JAGE_API Mesh
    {
    public:
        static std::unique_ptr<Mesh> Create(const Data::Mesh* meshdata);
        Mesh(const Data::Mesh* meshdata);
        virtual ~Mesh() = default;

        virtual void render(const Resource::Material* material) = 0;
    protected:
        const Data::Mesh* m_meshdata;
    };

    class JAGE_API Renderer
    {
    public:
        static std::unique_ptr<Renderer> Create(Window* window);
        Renderer(Window* window);
        virtual ~Renderer() = default;

        void set_vp(const glm::mat4& view, const glm::mat4& projection);

        const glm::mat4& view() const;
        const glm::mat4& projection() const;
    protected:
        Window* m_window;

        glm::mat4 m_view, m_projection;
    };

    class JAGE_API DebugRenderer
    {
    public:
        static std::unique_ptr<DebugRenderer> Create(Window* window);
        DebugRenderer(Window* window);
        virtual ~DebugRenderer() = default;

        /**
         * @fn RenderGridLines
         * @brief Render grid lines in the game world.
         * 
         * Ideally, `slices` should take even values to get half slices correctly. Odd values will be truncated to the
         * lowest and nearest even value.
         * 
         * @param slices  Number of slices. Note that the slices start from the center of the grid (meaning that if you
         * set this value to, for example, 5 slices, you'll get 10 slices total).
         * @param spacing Spacing between slices. 
         */
        virtual void RenderGridLines(unsigned slices = 5, float spacing = 25.0f) = 0;

        virtual void RenderBaseAxes(float size = 0.1f) = 0;

        void set_vp(glm::mat4 view, glm::mat4 projection);
    protected:
        Window* m_window;

        glm::mat4 m_view, m_projection;
    };

    struct JAGE_API BufferElement
    {
        Resource::Shader::DataType shader_datatype;
        std::string name;
        unsigned size;
        unsigned offset;
        bool normalized;

        BufferElement() = default;
        BufferElement(Resource::Shader::DataType shader_datatype, std::string_view name, bool normalized = false);

        unsigned component_count() const;
    };

    class JAGE_API BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        const std::vector<BufferElement>& elements() const;
        unsigned stride() const;
    private:
        std::vector<BufferElement> m_elements {};
        unsigned m_stride;
    };
}
