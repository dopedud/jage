#pragma once

#include "JAGE/core.h"
#include "window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace JAGE
{
    class GLFWWindow : public WindowBackend
    {
    public:
        GLFWWindow(const WindowProperties& properties = WindowProperties{});
        ~GLFWWindow() override;

        inline unsigned int width() const override { return data.properties.width; }
        inline unsigned int height() const override { return data.properties.height; }

        void OnUpdate() override;

        inline void set_eventcallback(const EventCallbackFn& callback) override { this->data.callback = callback; }
        void set_vsync(bool enabled) override;
        inline bool is_vsync() const override { return data.properties.vsync; }
    private:
        GLFWwindow* handle = nullptr;
    };
}