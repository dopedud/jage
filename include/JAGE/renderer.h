#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"
#include "JAGE/assets.h"

namespace JAGE
{
    class JAGE_API Shader
    {
    public:
        enum class DataType : u8
        {
            None = 0,
            Float, Float2, Float3, Float4,
            Int, Int2, Int3, Int4,
            Mat3, Mat4,
            Bool
        };

        static unsigned datatype_size(DataType datatype);

        static std::unique_ptr<Shader> Create(std::string_view vertex_str, std::string_view fragment_str);
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

    class JAGE_API Texture
    {
    public:
        static std::unique_ptr<Texture> Create(const ImageData* imagedata);
        virtual ~Texture() = default;

        virtual void bind(unsigned unit) const = 0;
        virtual void unbind() const = 0;
    };

    class JAGE_API Material
    {
    public:
        Material(Shader* shader, const MaterialData* materialdata);
        Material();

        Shader* shader() const;
        const MaterialData* materialdata() const;
        Texture* albedo_texture() const;
    private:
        Shader* m_shader;
        std::unique_ptr<Texture> m_albedo_texture;
        const MaterialData* m_materialdata;
    };

    class JAGE_API Mesh
    {
    public:
        static std::unique_ptr<Mesh> Create(const MeshData* meshdata);
        Mesh(const MeshData* meshdata);
        virtual ~Mesh() = default;

        virtual void render(const Material* material) = 0;
    protected:
        const MeshData* m_meshdata;
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
        Shader::DataType shader_datatype;
        std::string name;
        unsigned size;
        unsigned offset;
        bool normalized;

        BufferElement() = default;
        BufferElement(Shader::DataType shader_datatype, std::string_view name, bool normalized = false);

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
