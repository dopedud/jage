#include "window.h"

#include "platform/opengl/glfw_window.h"

namespace JAGE
{
    Window::Window_Impl::Window_Impl(const WindowProperties& properties)
    {
        backend = std::make_unique<GLFWWindow>(properties);
    }

    Window::Window(const WindowProperties& properties) 
    : pImpl { std::make_unique<Window_Impl>(properties) }
    {}

    Window::~Window() = default;

    unsigned int Window::width() const { return pImpl->width(); }
    unsigned int Window::height() const { return pImpl->height(); }

    void Window::OnUpdate() { pImpl->OnUpdate(); }

    void Window::set_eventcallback(const EventCallbackFn& callback) { pImpl->set_eventcallback(callback); }

    void Window::set_vsync(bool enabled) { pImpl->set_vsync(enabled); }
    bool Window::is_vsync() const { return pImpl->is_vsync(); }
}