#pragma once

#include "platform/platform.h"

namespace JAGE
{
    class GLFWWindow final : public Window
    {
    public:
        GLFWWindow(const Properties& properties);
        ~GLFWWindow() override;

        void set_vsync(bool enabled) override;

        void OnUpdate() override;

        void* handle() override { return m_handle; }
    private:
        GLFWwindow* m_handle;
    };
}