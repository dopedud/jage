#include "platform/glfw/window.h"

#include "JAGE/resources.h"

#include "platform/glfw/opengl3/renderer.h"
#include "log.h"

namespace JAGE
{
    GLFWWindow::GLFWWindow(const WindowProperties& properties)
    {
        JAGE_MSG_INFO("Window Info:");
        JAGE_MSG_INFO("    Backend:     GLFW");
        JAGE_LOG_INFO("    Title:       \"{}\"", properties.title);
        JAGE_LOG_INFO("    Dimensions:  {} x {}", properties.width, properties.height);

        data.properties = properties;
        data.OnEvent = [this](const Event& e) -> void { OnEvent(e); };

        glfwSetErrorCallback([](int error_code, const char* desc) -> void
        {
            JAGE_LOG_ERROR("GLFW error {}: {}.", error_code, desc);
        });

        int success { glfwInit() };
        JAGE_MSG_ASSERT(success, "GLFW error: Failed to initialise GLFW.")

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_handle = glfwCreateWindow(
            properties.width,
            properties.height,
            properties.title.c_str(), nullptr, nullptr
        );

        JAGE_MSG_ASSERT(m_handle, "GLFW error: Failed to create GLFW window.")

        glfwMakeContextCurrent(m_handle);
        glfwSetWindowUserPointer(m_handle, &data);

        glfwSwapInterval(data.properties.vsync);

        graphics_context = std::make_unique<OpenGLContext>(this);

        // glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // BUNCH OF CALLBACK DEFINITIONS

        // NOTE: data.callback() COULD only be called for windows related event (such as the 2 window events written
        // below) and have input related events be routed somewhere else; for now, all events are routed to the
        // application

        DISABLE_WARNING_PUSH
        DISABLE_WARNING_GCC_CLANG("-Wnarrowing")

        glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* window) -> void 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event {};
            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetWindowFocusCallback(m_handle, [](GLFWwindow* window, int focused) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowFocusEvent event { focused };
            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* window, int width, int height) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.properties.width = width;
            data.properties.height = height;

            WindowResizeEvent event { width, height };

            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetKeyCallback(m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyEvent event { Input::FromGLFWKey(key), scancode, Input::FromGLFWAction(action), Input::FromGLFWMods(mods) };

            data.callback(event);
            data.OnEvent(event);
        });

        // glfwSetCharCallback(m_handle, [](GLFWwindow* window, int codepoint) -> void
        // {
        //     WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        //     CharEvent event { codepoint };

        //     data.callback(event);
        //     data.OnEvent(event);
        // });

        glfwSetMouseButtonCallback(m_handle, [](GLFWwindow* window, int button, int action, int mods) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseButtonEvent event { Input::FromGLFWMouseButton(button), Input::FromGLFWAction(action), Input::FromGLFWMods(mods) };

            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetCursorEnterCallback(m_handle, [](GLFWwindow* window, int entered) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseEnterEvent event { entered };
            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetCursorPosCallback(m_handle, [](GLFWwindow* window, double xpos, double ypos) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event { xpos, ypos };
            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetScrollCallback(m_handle, [](GLFWwindow* window, double xoffset, double yoffset) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event { xoffset, yoffset };
            data.callback(event);
            data.OnEvent(event);
        });

        DISABLE_WARNING_POP

        // END BUNCH OF CALLBACK DEFINITIONS
    }

    GLFWWindow::~GLFWWindow()
    {
        for (Layer* layer : layers)
        {
            layer->OnDetach();
            delete layer;
        }

        glfwDestroyWindow(m_handle);
        m_handle = nullptr;

        glfwTerminate();
    }

    void GLFWWindow::OnRender()
    {
        graphics_context->Clear();

        for (Layer* layer : layers) layer->OnRender();

        graphics_context->SwapBuffers();
    }

    void GLFWWindow::set_vsync(bool enabled)
    {
        if (enabled) glfwSwapInterval(true);
        else glfwSwapInterval(false);

        data.properties.vsync = enabled;
    }
}
