#pragma once

#include "JAGE/core.h"
#include "window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace JAGE
{
    class GLFWWindow : public WindowBackend
    {
    public:
        GLFWWindow(const WindowProperties& properties = WindowProperties{});
        ~GLFWWindow() override;

        unsigned int width() const override { return data.properties.width; }
        unsigned int height() const override { return data.properties.height; }

        void OnUpdate() override;

        void set_eventcallback(const EventCallbackFn& callback) override { this->data.callback = callback; }
        void set_vsync(bool enabled) override;
        bool vsync() const override { return data.properties.vsync; }

        void* handle() { return m_handle; }
    private:
        GLFWwindow* m_handle;
    };
}