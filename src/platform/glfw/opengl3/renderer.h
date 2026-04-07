#pragma once

#include "JAGE/renderer.h"

#include "platform/platform.h"

#include <glad/glad.h>

namespace JAGE
{
    class OpenGLContext final : public GraphicsContext
    {
    public:
        OpenGLContext(Window* window);

        virtual void Clear() override;
        virtual void SwapBuffers() override;
    };

    class OpenGLShader final : public Resource::Shader
    {
    public:
        static GLenum to_opengl_type(DataType datatype);

        OpenGLShader
        (
            Data::URI uri,
            std::string_view vertex_str,
            std::string_view fragment_str,
            std::string_view geometry_str
        );
        ~OpenGLShader();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void set_uniform_bool       (std::string_view name, bool value) override;
        virtual void set_uniform_uint       (std::string_view name, unsigned value) override;
        virtual void set_uniform_int        (std::string_view name, int value) override;
        virtual void set_uniform_float      (std::string_view name, float value) override;
        virtual void set_uniform_float2     (std::string_view name, const glm::vec2& value) override;
        virtual void set_uniform_float3     (std::string_view name, const glm::vec3& value) override;
        virtual void set_uniform_float4     (std::string_view name, const glm::vec4& value) override;
        virtual void set_uniform_mat4       (std::string_view name, const glm::mat4& value) override;
    private:
        unsigned id;
    };

    class OpenGLTexture final : public Texture
    {
    public:
        OpenGLTexture(const Data::Image* imagedata);
        ~OpenGLTexture();

        virtual void bind(unsigned unit) const override;
        virtual void unbind() const override;
    private:
        unsigned id;
    };

    class OpenGLMesh final : public Mesh
    {
    public:
        OpenGLMesh(const Data::Mesh* meshdata);

        virtual void render(const Resource::Material* material) override;
    private:
        unsigned vao, vbo, ebo;
    };

    class OpenGLRenderer final : public Renderer
    {
    public:
        OpenGLRenderer(Window* window);
        ~OpenGLRenderer();
    };

    class OpenGLDebugRenderer final : public DebugRenderer
    {
    public:
        OpenGLDebugRenderer(Window* window);
        ~OpenGLDebugRenderer();

        virtual void RenderGridLines(unsigned slices, float spacing) override;
        virtual void RenderBaseAxes(float size) override;
    private:
        OpenGLShader grid_shader, axes_shader;

        unsigned grid_vao, grid_vbo, grid_ebo;
        unsigned axes_vao, axes_vbo, axes_ebo;
    };
}
