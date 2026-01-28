#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"
#include "JAGE/resources.h"

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

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void set_uniform_bool   (std::string_view name, bool value) = 0;
        virtual void set_uniform_int    (std::string_view name, int value) = 0;
        virtual void set_uniform_uint   (std::string_view name, unsigned value) = 0;
        virtual void set_uniform_float  (std::string_view name, float value) = 0;
        virtual void set_uniform_mat4   (std::string_view name, const glm::mat4& value) = 0;
    };

    class JAGE_API Texture
    {
    public:
        enum class Type : u8 { DIFFUSE = 0, SPECULAR };

        static std::unique_ptr<Texture> Create(const ImageData* data);
        virtual ~Texture() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        Type type() const;
    protected:
        Type m_type;
    };

    class JAGE_API Mesh
    {
    public:
        static std::unique_ptr<Mesh> Create(const MeshData* data);
        Mesh(const MeshData* data);
        virtual ~Mesh() = default;

        virtual void render(const std::unique_ptr<Shader>& shader) = 0;
    protected:
        const MeshData* m_data;
    };

    class JAGE_API Material
    {
    public:
        static std::unique_ptr<Material> Create(const MaterialData* shader);
        virtual ~Material() = default;

        void set_shader(const Shader* shader);
    private:
        const Shader* m_shader;
        const MaterialData* m_materialdata;
    };

    class JAGE_API DebugRenderer
    {
    public:
        static std::unique_ptr<DebugRenderer> Create(Window* window);
        DebugRenderer(Window* window);
        virtual ~DebugRenderer() = default;

        /**
         * @fn RenderGridLines()
         * @brief Render grid lines in the game world.
         * 
         * Ideally, @c slices should take even values to get half slices correctly. Odd values will be truncated to the
         * lowest and nearest even value.
         * 
         * @param slices number of slices
         * @param spacing spacing between slices
         */
        virtual void RenderGridLines(unsigned slices, float spacing) = 0;

        virtual void RenderBaseAxes(float size) = 0;

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
