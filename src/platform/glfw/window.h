#pragma once

#include "platform/input.h"

namespace JAGE
{
    class GLFWWindow final : public Window
    {
    public:
        GLFWWindow(const WindowProperties& properties = WindowProperties{});
        ~GLFWWindow() override;

        void OnRender() override;

        void set_vsync(bool enabled) override;

        void* handle() override { return m_handle; }
    private:
        GLFWwindow* m_handle;
    };
}