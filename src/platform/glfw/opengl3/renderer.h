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

    class OpenGLShader final : public Shader
    {
    public:
        static GLenum to_opengl_type(DataType datatype);

        OpenGLShader(std::string_view vertex_str, std::string_view fragment_str);
        ~OpenGLShader();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void set_uniform_bool   (std::string_view name, bool value) override;
        virtual void set_uniform_int    (std::string_view name, int value) override;
        virtual void set_uniform_uint   (std::string_view name, unsigned value) override;
        virtual void set_uniform_float  (std::string_view name, float value) override;
        virtual void set_uniform_mat4   (std::string_view name, const glm::mat4& value) override;
    private:
        unsigned shaderID;
    };

    class OpenGLTexture final : public Texture
    {
    public:
        OpenGLTexture(const ImageData* imagedata);
        ~OpenGLTexture();

        virtual void bind() override;
        virtual void unbind() override;
    private:
        unsigned textureID;
    };

    class OpenGLMesh final : public Mesh
    {
    public:
        OpenGLMesh(const MeshData* meshdata);

        virtual void render(const Shader* shader) override;
    private:
        unsigned vao, vbo, ebo;
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
