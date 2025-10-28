#include "opengl_renderer.h"

#include "log.h"

#include <glad/glad.h>

namespace JAGE
{
    OpenGLContext::OpenGLContext(Window* window) : GraphicsContext(window) {}

    void OpenGLContext::Init()
    {
        int glad_load_success { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        JAGE_ASSERT(glad_load_success, "Failed to initialise GLAD.");

        JAGE_MSG_INFO("OpenGL Info:");
        JAGE_LOG_INFO("    Vendor:      {}", (const char *)glGetString(GL_VENDOR));
        JAGE_LOG_INFO("    Renderer:    {}", (const char *)glGetString(GL_RENDERER));
        JAGE_LOG_INFO("    Version:     {}", (const char *)glGetString(GL_VERSION));

        glViewport(0, 0, window->width(), window->height());

        glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(window->handle()), [](GLFWwindow* window, int width, int height) -> void 
        {
            glViewport(0, 0, width, height);
        });
    }

    void OpenGLContext::Clear()
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwPollEvents();
        glfwSwapBuffers(static_cast<GLFWwindow*>(window->handle()));
    }
}
