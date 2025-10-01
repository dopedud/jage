#include "glfw_window.h"

#include "log.h"

namespace JAGE
{
    static bool s_GLFW_initialised = false;

    GLFWWindow::GLFWWindow(const WindowProperties& properties) 
    {
        JAGE_LOG_INFO("Creating a window; backend: OpenGL 4.6, title: \"{}\", dimensions: ({}, {}).", properties.title, properties.width, properties.height);

        this->data.properties = properties; 

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

        JAGE_CORE_ASSERT(handle, "Failed to create GLFW window.");

        glfwMakeContextCurrent(handle);
        glfwSetWindowUserPointer(handle, &data);

        int glad_load_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        JAGE_CORE_ASSERT(glad_load_success, "Failed to initialise GLAD.");

        glfwSetWindowCloseCallback(handle, [](GLFWwindow* window) -> void 
        {
            JAGE_MSG_TRACE

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event {};
            data.callback(event);
        });
    }

    GLFWWindow::~GLFWWindow()
    {
        glfwDestroyWindow(handle); 
    }

    void GLFWWindow::OnUpdate()
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(handle);
    }

    void GLFWWindow::set_vsync(bool enabled)
    {
        if (enabled) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        data.properties.vsync = enabled;
    }
}
