#pragma once

#include "JAGE/core.h"

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
    private:
        GLFWwindow* glfw_window;
    };
}