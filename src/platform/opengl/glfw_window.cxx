#include "glfw_window.h"

#include "log.h"

namespace JAGE
{
    static bool s_GLFW_initialised = false;

    GLFWWindow::GLFWWindow(const WindowProperties& properties) 
    {
        JAGE_LOG_INFO("Creating a window; backend: OpenGL 4.6, title: \"{}\", dimensions: ({}, {}).", properties.title, properties.width, properties.height);

        this->data.properties = properties; 

        glfwSetErrorCallback([](int error_code, const char* desc) -> void
        {
            JAGE_LOG_ERROR("GLFW error ({}): {}", error_code, desc);
        });

        if (!s_GLFW_initialised)
        {
            int success = glfwInit();
            JAGE_ASSERT(success, "Failed to initialise GLFW.")

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

        JAGE_ASSERT(handle, "Failed to create GLFW window.");

        glfwMakeContextCurrent(handle);
        glfwSetWindowUserPointer(handle, &data);

        int glad_load_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        JAGE_ASSERT(glad_load_success, "Failed to initialise GLAD.");

        // BUNCH OF CALLBACK DEFINITIONS

        // NOTE: data.callback() COULD only be called for windows related event (such as the 2 window events written
        // below) and have input related events be routed somewhere else; for now, all events are routed to the
        // application

        DISABLE_WARNING_PUSH
        DISABLE_WARNING_GCC_CLANG("-Wnarrowing")

        glfwSetWindowCloseCallback(handle, [](GLFWwindow* window) -> void 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event {};

            data.callback(event);
        });

        glfwSetWindowSizeCallback(handle, [](GLFWwindow* window, int width, int height) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.properties.width = width;
            data.properties.height = height;

            WindowResizeEvent event { width, height };

            data.callback(event);
        });

        glfwSetKeyCallback(handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event { key, false };

                    data.callback(event);
                }
                break;
                
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event { key };

                    data.callback(event);
                }
                break;
                
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event { key, true };

                    data.callback(event);
                }
                break;
            }
        });

        glfwSetMouseButtonCallback(handle, [](GLFWwindow* window, int button, int action, int mods) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event { button };

                    data.callback(event);
                }
                break;

                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event { button };

                    data.callback(event);
                }
                break;
            }
        });

        glfwSetCursorPosCallback(handle, [](GLFWwindow* window, double xpos, double ypos) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event { xpos, ypos };

            data.callback(event);
        });

        glfwSetScrollCallback(handle, [](GLFWwindow* window, double xoffset, double yoffset) -> void
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event { xoffset, yoffset };

            data.callback(event);
        });

        DISABLE_WARNING_POP

        // END BUNCH OF CALLBACK DEFINITIONS
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
