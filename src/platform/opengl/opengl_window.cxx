#include "opengl_window.h"

namespace JAGE
{
    static bool s_GLFW_initialised = false;

    Window* Window::create(const WindowProperties& properties)
    {
        return new OpenGLWindow(properties);
    }

    OpenGLWindow::OpenGLWindow(const WindowProperties& properties)
    {
        Init(properties);
    }

    OpenGLWindow::~OpenGLWindow()
    {
        Shutdown();
    }

    void OpenGLWindow::Init(const WindowProperties& properties)
    {
        m_data.title = properties.title;
        m_data.width = properties.width;
        m_data.height = properties.height;

        JAGE_LOG_INFO("Creating window {} ({}, {})", properties.title, properties.width, properties.height);

        if (!s_GLFW_initialised)
        {
            int success = glfwInit();
            JAGE_CORE_ASSERT(success, "Failed to initialise GLFW.")

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            s_GLFW_initialised = true;
        }

        m_window = glfwCreateWindow(
            static_cast<int>(properties.width),
            static_cast<int>(properties.height),
            properties.title.c_str(), nullptr, nullptr
        );

        JAGE_CORE_ASSERT(m_window, "Failed to create GLFW window.");

        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);

        int glad_load_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        JAGE_CORE_ASSERT(glad_load_success, "Failed to initialise GLAD.");
    }

    void OpenGLWindow::Shutdown()
    {
        glfwDestroyWindow(m_window);
    }

    void OpenGLWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void OpenGLWindow::set_vsync(bool enabled)
    {
        if (enabled) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        m_data.vsync = enabled;
    }

    bool OpenGLWindow::is_vsync() const { return m_data.vsync; }
}

