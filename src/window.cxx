#include "window.h"
#include "glfw_window.h"

namespace JAGE
{
    Window::Window_Impl::Window_Impl(const WindowProperties& properties = WindowProperties{})
    {
        backend = std::make_unique<GLFWWindow>(properties);
    }
}