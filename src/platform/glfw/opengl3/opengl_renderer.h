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

    // class OpenGLVertexBuffer : public VertexBuffer
    // {
    //     OpenGLVertexBuffer(uint32_t size);
    //     OpenGLVertexBuffer(float* vertices, uint32_t size);
    //     virtual ~OpenGLVertexBuffer();

    //     void Bind() const override;
    //     void Unbind() const override;
    // };

    // class OpenGLIndexBuffer : public IndexBuffer
    // {
    //     OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    //     virtual ~OpenGLIndexBuffer();

    //     void Bind() const override;
    //     void Unbind() const override;
    // };
}
