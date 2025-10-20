#include "platform/glfw/window.h"

#include "log.h"

#include <glad/glad.h>

namespace JAGE
{
    std::unique_ptr<Window> Window::create(const WindowProperties& properties)
    {
        return std::make_unique<GLFWWindow>(properties);
    }

    GLFWWindow::GLFWWindow(const WindowProperties& properties)
    {
        JAGE_LOG_INFO("Creating a window; backend: OpenGL 4.6, title: \"{}\", dimensions: ({}, {}).", properties.title, properties.width, properties.height);

        this->data.properties = properties;
        this->data.OnEvent = [this](const Event& e) -> void { OnEvent(e); };

        glfwSetErrorCallback([](int error_code, const char* desc) -> void
        {
            JAGE_LOG_ERROR("GLFW error ({}): {}", error_code, desc);
        });

        static bool s_GLFW_initialised { false };

        if (!s_GLFW_initialised)
        {
            int success { glfwInit() };
            JAGE_ASSERT(success, "Failed to initialise GLFW.")

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            s_GLFW_initialised = true;
        }

        m_handle = glfwCreateWindow(
            static_cast<int>(properties.width),
            static_cast<int>(properties.height),
            properties.title.c_str(), nullptr, nullptr
        );

        JAGE_ASSERT(m_handle, "Failed to create GLFW window.");

        glfwMakeContextCurrent(m_handle);
        glfwSetWindowUserPointer(m_handle, &data);

        int glad_load_success { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };

        JAGE_ASSERT(glad_load_success, "Failed to initialise GLAD.");

        glfwSwapInterval(data.properties.vsync);

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

        glfwSetCharCallback(m_handle, [](GLFWwindow* window, unsigned int codepoint) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            CharEvent event { codepoint };

            data.callback(event);
            // data.OnEvent(event);
        });

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
        for (Layer* layer : layers) delete layer;
        glfwDestroyWindow(m_handle);
    }

    void GLFWWindow::OnPollEvents()
    {
        glfwPollEvents();
    }

    void GLFWWindow::OnClear()
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLFWWindow::OnRender()
    {
        for (Layer* layer : layers) layer->OnRender();

        glViewport(0, 0, data.properties.width, data.properties.height);
        glfwSwapBuffers(m_handle);
    }

    void GLFWWindow::set_vsync(bool enabled)
    {
        if (enabled) glfwSwapInterval(true);
        else glfwSwapInterval(false);

        data.properties.vsync = enabled;
    }
}
