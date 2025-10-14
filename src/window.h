#pragma once

#include "JAGE/core.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace JAGE
{
    class GLFWWindow final : public Window
    {
    public:
        GLFWWindow(const WindowProperties& properties = WindowProperties{});
        ~GLFWWindow() override;

        void OnPollEvents() override;
        void OnClear() override;
        void OnRender() override;

        void set_vsync(bool enabled) override;

        void* handle() override { return m_handle; }
    private:
        GLFWwindow* m_handle;
    };
}