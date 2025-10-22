#include "opengl_context.h"

#include "log.h"

#include <glad/glad.h>

namespace JAGE
{
    OpenGLContext::OpenGLContext(Window* window)
    : GraphicsContext(window)
    , glfw_window { static_cast<GLFWwindow*>(window->handle()) }
    {
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(glfw_window);
        int glad_load_success { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        JAGE_ASSERT(glad_load_success, "Failed to initialise GLAD.");
    }

    void OpenGLContext::Clear()
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLContext::SwapBuffers()
    {
        glViewport(0, 0, window->width(), window->height());
        glfwSwapBuffers(glfw_window);
    }
}