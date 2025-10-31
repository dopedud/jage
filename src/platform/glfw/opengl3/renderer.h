#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer/core.h"

#include "platform/input.h"
#include <glad/glad.h>

namespace JAGE
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(Window* window);

        void Init() override;
        void Clear() override;
        void SwapBuffers() override;
    };

    namespace ShaderData
    {
        GLenum to_opengltype(Type type);
    }

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(std::string_view vertex_str, std::string_view fragment_str);
        virtual ~OpenGLShader();

        void bind() const override;
        void unbind() const override;
    };

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        void bind() const override;
        void unbind() const override;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        void bind() const override;
        void unbind() const override;
    };

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        void bind() const override;
        void unbind() const override;

        void add_vbuffer(const std::shared_ptr<VertexBuffer>& vbuffer) override;
        void set_ibuffer(const std::shared_ptr<IndexBuffer>& ibuffer) override;
    };
}
