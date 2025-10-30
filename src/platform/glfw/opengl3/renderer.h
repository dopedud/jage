#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer/core.h"

#include "platform/input.h"

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

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(std::string_view vertex_str, std::string_view fragment_str);
        virtual ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;
    };

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;
    };
}
