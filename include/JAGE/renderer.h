#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"

namespace JAGE
{
    class JAGE_API Shader
    {
    public:
        enum class DataType : ui8
        {
            None = 0,
            Float, Float2, Float3, Float4,
            Int, Int2, Int3, Int4,
            Mat3, Mat4,
            Bool
        };

        static unsigned JAGE_API datatype_size(DataType datatype);

        static std::unique_ptr<Shader> Create(std::string_view vertex_str, std::string_view fragment_str);
        Shader(std::string_view vertex_str, std::string_view fragment_str);
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void set_uniform_bool   (std::string_view name, bool value) = 0;
        virtual void set_uniform_int    (std::string_view name, int value) = 0;
        virtual void set_uniform_uint   (std::string_view name, unsigned value) = 0;
        virtual void set_uniform_float  (std::string_view name, float value) = 0;
        virtual void set_uniform_mat4   (std::string_view name, const glm::mat4& value) = 0;
    protected:
        std::string m_vertex_str;
        std::string m_fragment_str;
    };

    class JAGE_API Texture
    {
    public:
        enum class Type : ui8 { DIFFUSE = 0, SPECULAR };

        static std::unique_ptr<Texture> Create(ui8* data, unsigned width, unsigned height);
        virtual ~Texture() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        Type type() const;
        void set_type(Type type);
    protected:
        Type m_type;
    };

    class JAGE_API Mesh
    {
    public:
        enum class PrimitiveType : ui8 { POINT, LINE, TRIANGLE };

        struct JAGE_API Vertex
        {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec4 color;
            // glm::vec2 texcoords;
        };

        static std::unique_ptr<Mesh> Create(
            PrimitiveType ptype,
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned>& indices
        );

        Mesh();

        Mesh(
            PrimitiveType ptype,
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned>& indices
        );

        virtual ~Mesh() = default;

        virtual void render(const std::unique_ptr<Shader>& shader) = 0;
    protected:
        PrimitiveType m_ptype;
        std::vector<Vertex> m_vertices;
        std::vector<unsigned> m_indices;
        std::vector<Texture*> m_textures;
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

    class JAGE_API VertexBuffer
    {
    public:
        static std::unique_ptr<VertexBuffer> Create(float* vertices, unsigned size);
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        const BufferLayout& layout() const { return m_layout; }
        void set_layout(const BufferLayout& layout) { m_layout = layout; }
    protected:
        unsigned rendererID;
        BufferLayout m_layout;
    };

    class JAGE_API IndexBuffer
    {
    public:
        static std::unique_ptr<IndexBuffer> Create(unsigned* indices, unsigned count);
        IndexBuffer(unsigned count);
        virtual ~IndexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        unsigned count() const { return m_count; }
    protected:
        unsigned rendererID;
        unsigned m_count;
    };

    class JAGE_API VertexArray
    {
    public:
        static std::unique_ptr<VertexArray> Create();
        virtual ~VertexArray() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void add_vbuffer(std::unique_ptr<VertexBuffer>&& vbuffer) = 0;
        virtual void set_ibuffer(std::unique_ptr<IndexBuffer>&& ibuffer) = 0;
    protected:
        unsigned rendererID;

        std::vector<std::unique_ptr<VertexBuffer>> vbuffers {};
        std::unique_ptr<IndexBuffer> ibuffer;
    };

    class JAGE_API DebugRenderer
    {
    public:
        static std::unique_ptr<DebugRenderer> Create(Window* window);
        DebugRenderer(Window* window);
        virtual ~DebugRenderer() = default;

        virtual void Render() = 0;

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

        std::unique_ptr<Shader> m_grid_shader;
        std::unique_ptr<Shader> m_coord_shader;

        glm::mat4 m_view, m_projection;
    };

}
