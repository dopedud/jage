#include "platform/glfw/window.h"
#include "platform/glfw/opengl3/renderer.h"

#include "timing.h"
#include "log.h"

namespace JAGE
{
    static void opengl_message_callback
    (
        GLenum, // source
        GLenum, // type
        GLuint, // id
        GLenum severity,
        GLsizei, // length
        const GLchar *message,
        const void* // userParam
    )
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_NOTIFICATION:    JAGE_MSG_TRACE(message); return;
            case GL_DEBUG_SEVERITY_LOW:             JAGE_MSG_WARN(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM:          JAGE_MSG_ERROR(message); return;
            case GL_DEBUG_SEVERITY_HIGH:            JAGE_MSG_CRITICAL(message); return;

            default: JAGE_MSG_ERROR("JAGE error: unknown severity level from OpenGL."); return;
        }
    }

    GLFWWindow::GLFWWindow(const Properties& properties) : Window{ properties }
    {
        JAGE_MSG_INFO("Window Info:");
        JAGE_MSG_INFO("    Backend:     GLFW");
        JAGE_LOG_INFO("    Title:       \"{}\"", properties.title);
        JAGE_LOG_INFO("    Dimensions:  {} x {}", properties.width, properties.height);

        data.OnEvent = [this](const Event& e) -> void { OnEvent(e); };

        m_handle = glfwCreateWindow
        (
            properties.width,
            properties.height,
            properties.title.c_str(),
            nullptr, nullptr
        );

        Input::SetActiveWindow(m_handle);

        JAGE_MSG_ASSERT(m_handle, "GLFW error: Failed to create GLFW window.")

        glfwMakeContextCurrent(m_handle);
        glfwSetWindowUserPointer(m_handle, &data);

        glfwSwapInterval(data.properties.vsync);

        // need to initialise GLAD first to use glGetString()
        int glad_load_success { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        JAGE_MSG_ASSERT(glad_load_success, "Failed to initialise GLAD.");

        JAGE_MSG_INFO("Graphics Info:");
        JAGE_MSG_INFO("    Graphics Backend:   OpenGL");
        JAGE_LOG_INFO("    Vendor:             {}", (const char*)glGetString(GL_VENDOR));
        JAGE_LOG_INFO("    Renderer:           {}", (const char*)glGetString(GL_RENDERER));
        JAGE_LOG_INFO("    Version:            {}", (const char*)glGetString(GL_VERSION));

        #ifdef DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(opengl_message_callback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
        #endif

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glViewport(0, 0, data.properties.width, data.properties.height);

        glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(m_handle),
        [](GLFWwindow* window, int width, int height) -> void
        {
            glViewport(0, 0, width, height);
        });

        if (glfwRawMouseMotionSupported()) glfwSetInputMode(m_handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        // BUNCH OF CALLBACK DEFINITIONS

        // NOTE: data.callback() COULD only be called for windows related event (such as the window events written
        // below) and have input related events be routed somewhere else; for now, all events are routed to the
        // application

        DISABLE_WARNING_PUSH
        DISABLE_WARNING_GCC_CLANG("-Wnarrowing")

        glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* window) -> void 
        {
            Data& data = *(Data*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event {};
            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetWindowFocusCallback(m_handle, [](GLFWwindow* window, int focused) -> void
        {
            Data& data = *(Data*)glfwGetWindowUserPointer(window);
            WindowFocusEvent event { focused };
            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* window, int width, int height) -> void
        {
            Data& data = *(Data*)glfwGetWindowUserPointer(window);
            data.properties.width = width;
            data.properties.height = height;

            WindowResizeEvent event { width, height };

            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetKeyCallback(m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
        {
            Data& data = *(Data*)glfwGetWindowUserPointer(window);

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
            Data& data = *(Data*)glfwGetWindowUserPointer(window);

            MouseButtonEvent event { Input::FromGLFWMouseButton(button), Input::FromGLFWAction(action), Input::FromGLFWMods(mods) };

            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetCursorEnterCallback(m_handle, [](GLFWwindow* window, int entered) -> void
        {
            Data& data = *(Data*)glfwGetWindowUserPointer(window);
            MouseEnterEvent event { entered };
            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetCursorPosCallback(m_handle, [](GLFWwindow* window, double xpos, double ypos) -> void
        {
            Data& data = *(Data*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event { xpos, ypos };
            data.callback(event);
            data.OnEvent(event);
        });

        glfwSetScrollCallback(m_handle, [](GLFWwindow* window, double xoffset, double yoffset) -> void
        {
            Data& data = *(Data*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event { xoffset, yoffset };
            data.callback(event);
            data.OnEvent(event);
        });

        DISABLE_WARNING_POP

        // END BUNCH OF CALLBACK DEFINITIONS
    }

    GLFWWindow::~GLFWWindow()
    {
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }

    void GLFWWindow::OnUpdate()
    {
        // CLEAR SCREEN
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Input::UpdateMousePosition();
        for (const std::unique_ptr<Layer>& layer : layers) layer->OnUpdate();

        // SWAP BUFFERS
        glfwPollEvents();
        glfwSwapBuffers(static_cast<GLFWwindow*>(m_handle));

        Time::FrameLap();
    }

    void GLFWWindow::set_vsync(bool enabled)
    {
        if (enabled) glfwSwapInterval(true);
        else glfwSwapInterval(false);

        data.properties.vsync = enabled;
    }
}
