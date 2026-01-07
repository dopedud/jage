#pragma once

#include "platform/platform.h"

namespace JAGE
{
    class GLFWWindow final : public Window
    {
    public:
        GLFWWindow(const WindowProperties& properties = WindowProperties{});
        ~GLFWWindow() override;

        void set_vsync(bool enabled) override;

        void OnRender() override;

        void* handle() override { return m_handle; }
    private:
        GLFWwindow* m_handle;
    };
}