#include "glfw_window.h"

namespace JAGE
{
    static bool s_GLFW_initialised = false;

    GLFWWindow::GLFWWindow(const WindowProperties& properties = WindowProperties{})
    {
        this->properties = properties; 

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

        handle = glfwCreateWindow(
            static_cast<int>(properties.width),
            static_cast<int>(properties.height),
            properties.title.c_str(), nullptr, nullptr
        );

        JAGE_CORE_ASSERT(m_window, "Failed to create GLFW window.");

        glfwMakeContextCurrent(handle);
        glfwSetWindowUserPointer(handle, (void*)&properties);

        int glad_load_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        JAGE_CORE_ASSERT(glad_load_success, "Failed to initialise GLAD.");
    }

    GLFWWindow::~GLFWWindow()
    {
        glfwDestroyWindow(handle); 
    }

    void GLFWWindow::OnUpdate()
    {

        glfwPollEvents();
        glfwSwapBuffers(handle);
    }

    void GLFWWindow::set_vsync(bool enabled)
    {
        if (enabled) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        properties.vsync = enabled;
    }
}
