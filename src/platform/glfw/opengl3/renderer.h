#pragma once

#include "JAGE/renderer.h"
#include "JAGE/resources.h"

#include "platform/platform.h"

#include <glad/glad.h>

namespace JAGE
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(Window* window);

        void Clear() override;
        void SwapBuffers() override;
    };

    namespace ShaderData
    {
        GLenum to_opengltype(Type type);
    }

    class OpenGLTexture : public Texture
    {
    public:
        OpenGLTexture(unsigned char* data, unsigned width, unsigned height);
        ~OpenGLTexture();

        void bind() override;
        void unbind() override;
    };

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(std::string_view vertex_str, std::string_view fragment_str);
        ~OpenGLShader();

        void bind() override;
        void unbind() override;

        void set_uniform_bool(std::string_view name, bool value) override;
        void set_uniform_int(std::string_view name, int value) override;
        void set_uniform_uint(std::string_view name, unsigned value) override;
        void set_uniform_float(std::string_view name, float value) override;
    };

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void bind() override;
        void unbind() override;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        void bind() override;
        void unbind() override;
    };

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void bind() override;
        void unbind() override;

        void add_vbuffer(std::unique_ptr<VertexBuffer>& vbuffer) override;
        void set_ibuffer(std::unique_ptr<IndexBuffer>& ibuffer) override;
    };
}
