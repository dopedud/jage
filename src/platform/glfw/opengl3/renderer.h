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

        void Clear() override;
        void SwapBuffers() override;
    };

    namespace ShaderData
    {
        GLenum to_opengl_type(Type type);
    }

    class OpenGLTexture final : public Texture
    {
    public:
        OpenGLTexture(unsigned char* data, unsigned width, unsigned height);
        ~OpenGLTexture();

        void bind() override;
        void unbind() override;
    private:
        unsigned textureID;
    };

    class OpenGLShader final : public Shader
    {
    public:
        OpenGLShader(std::string_view vertex_str, std::string_view fragment_str);
        ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        void set_uniform_bool(std::string_view name, bool value) override;
        void set_uniform_int(std::string_view name, int value) override;
        void set_uniform_uint(std::string_view name, unsigned value) override;
        void set_uniform_float(std::string_view name, float value) override;
        void set_uniform_mat4(std::string_view name, const glm::mat4& value) override;
    private:
        unsigned shaderID;
    };

    class OpenGLMesh final : public Mesh
    {
    public:
        OpenGLMesh(
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned>& indices,
            const std::vector<std::unique_ptr<Texture>>& textures
        );

        void draw(const std::unique_ptr<Shader>& shader) override;
    private:
        unsigned vao, vbo, ebo;
    };

    class OpenGLVertexBuffer final : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, unsigned size);
        ~OpenGLVertexBuffer();

        void bind() override;
        void unbind() override;
    };

    class OpenGLIndexBuffer final : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(unsigned* indices, unsigned count);
        ~OpenGLIndexBuffer();

        void bind() override;
        void unbind() override;
    };

    class OpenGLVertexArray final : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void bind() override;
        void unbind() override;

        void add_vbuffer(std::unique_ptr<VertexBuffer>&& vbuffer) override;
        void set_ibuffer(std::unique_ptr<IndexBuffer>&& ibuffer) override;
    };
}
