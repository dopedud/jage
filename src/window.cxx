#include "window.h"

#include "platform/glfw/opengl3/window_impl.h"

namespace JAGE
{
    Window::Window_Impl::Window_Impl(const WindowProperties& properties)
    {
        // NOTE: backend can be initialised to any kind of window, provided it is derived from the Window base class
        backend = std::make_unique<GLFWWindow>(properties);
    }

    Window::Window(const WindowProperties& properties) 
    : pImpl { std::make_unique<Window_Impl>(properties) }
    {}

    Window::~Window() = default;

    unsigned int Window::width() const { return pImpl->width(); }
    unsigned int Window::height() const { return pImpl->height(); }

    void Window::OnPollEvents() { pImpl->OnPollEvents(); }
    void Window::OnClear() { pImpl->OnClear(); }
    void Window::OnRender() { pImpl->OnRender(); }

    void Window::set_eventcallback(const EventCallbackFn& callback) { pImpl->set_eventcallback(callback); }

    void Window::set_vsync(bool enabled) { pImpl->set_vsync(enabled); }
    bool Window::vsync() const { return pImpl->vsync(); }

    void* Window::handle() { return pImpl->handle(); }
}