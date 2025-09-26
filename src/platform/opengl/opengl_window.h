#pragma once

#include "JAGE/core.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace JAGE
{
    class OpenGLWindow : public Window
    {
    public:
        OpenGLWindow(const WindowProperties& properties);
        virtual ~OpenGLWindow();

        void OnUpdate() override;

        inline unsigned int width() const override { return m_data.width; }
        inline unsigned int height() const override { return m_data.height; }

        inline void set_eventcallback(const EventCallbackFn& callback) override { m_data.event_callback = callback; }

        void set_vsync(bool enabled) override;
        bool is_vsync() const override;
    private:
        virtual void Init(const WindowProperties& properties);
        virtual void Shutdown();

        GLFWwindow* m_window;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            bool vsync;

            EventCallbackFn event_callback;
        };

        WindowData m_data;
    };
}
