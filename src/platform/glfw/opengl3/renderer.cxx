#include "platform/glfw/opengl3/renderer.h"

#include "log.h"

namespace JAGE
{
    static void opengl_message_callback(
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
        }

        JAGE_MSG_ERROR("JAGE error: unknown severity level from OpenGL.");

        return;
    }

    void OpenGLContext::Init()
    {
        // need to initialise GLAD first to use glGetString()
        int glad_load_success { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        JAGE_ASSERT(glad_load_success, "Failed to initialise GLAD.");

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

    void Renderer::Render()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    namespace ShaderData
    {
        GLenum to_opengltype(Type type)
        {
            switch (type)
            {
                case Type::None:        return GL_NONE;
                case Type::Mat3:
                case Type::Mat4:
                case Type::Float:
                case Type::Float2:
                case Type::Float3:
                case Type::Float4:      return GL_FLOAT;
                case Type::Int:
                case Type::Int2:
                case Type::Int3:
                case Type::Int4:        return GL_INT;
                case Type::Bool:        return GL_BOOL;
            }

            JAGE_MSG_ERROR("Shader error: unknown shader data type. Returning type 0.");

            return 0;
        }
    }

    // OPENGL TEXTURE IMPLEMENTATION

    Texture* Texture::Create(unsigned char* data)
    {
        return new OpenGLTexture{ data };
    }

    OpenGLTexture::OpenGLTexture(unsigned char* data)
    {

    }

    OpenGLTexture::~OpenGLTexture()
    {

    }

    void OpenGLTexture::bind() {}
    void OpenGLTexture::unbind() {}

    // END OPENGL TEXTURE IMPLEMENTATION

    // OPENGL SHADER IMPLEMENTATION

    Shader* Shader::Create(std::string_view vertex_str, std::string_view fragment_str)
    {
        return new OpenGLShader{ vertex_str, fragment_str };
    }

    DISABLE_WARNING_PUSH
    DISABLE_WARNING_GCC_CLANG("-Wvla")

    OpenGLShader::OpenGLShader(std::string_view vertex_str, std::string_view fragment_str)
    {
        JAGE_MSG_TRACE("Initialising a OpenGL shader.");

        const GLchar* source {};
        GLint compiled {};

        GLuint vertex_shader { glCreateShader(GL_VERTEX_SHADER) };
        source = vertex_str.data();
        glShaderSource(vertex_shader, 1, &source, 0);
        glCompileShader(vertex_shader);

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compiled);
        if(compiled == GL_FALSE)
        {
            GLint max_length {};
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

            GLchar infoLog[max_length];
            glGetShaderInfoLog(vertex_shader, max_length, &max_length, &infoLog[0]);

            glDeleteShader(vertex_shader);

            JAGE_LOG_ERROR("OpenGL shader error: {}.", static_cast<std::string_view>(infoLog));

            return;
        }

        JAGE_MSG_TRACE("Vertex shader initialised.");

        GLuint fragment_shader { glCreateShader(GL_FRAGMENT_SHADER) };
        source = fragment_str.data();
        glShaderSource(fragment_shader, 1, &source, 0);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE)
        {
            GLint max_length {};
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

            GLchar infoLog[max_length];
            glGetShaderInfoLog(fragment_shader, max_length, &max_length, &infoLog[0]);

            glDeleteShader(fragment_shader);

            JAGE_LOG_ERROR("OpenGL shader error: {}.", static_cast<std::string_view>(infoLog));

            return;
        }

        JAGE_MSG_TRACE("Fragment shader initialised.");

        shaderID = glCreateProgram();
        GLint linked {};

        glAttachShader(shaderID, vertex_shader);
        glAttachShader(shaderID, fragment_shader);
        glLinkProgram(shaderID);

        glGetProgramiv(shaderID, GL_LINK_STATUS, (int *)&linked);
        if (linked == GL_FALSE)
        {
            GLint max_length {};
            glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &max_length);

            GLchar infoLog[max_length];
            glGetProgramInfoLog(shaderID, max_length, &max_length, &infoLog[0]);

            glDeleteProgram(shaderID);
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            JAGE_LOG_ERROR("OpenGL shader error: {}.", static_cast<std::string_view>(infoLog));

            return;
        }

        JAGE_MSG_TRACE("Shader program initialised.");

        glDetachShader(shaderID, vertex_shader);
        glDetachShader(shaderID, fragment_shader);

        JAGE_MSG_TRACE("OpenGL shader initialised.");
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(shaderID);
    }

    DISABLE_WARNING_POP

    void OpenGLShader::bind() { glUseProgram(shaderID); }
    void OpenGLShader::unbind() { glUseProgram(0); }

    // END OPENGL SHADER IMPLEMENTATION

    // OPENGL VERTEX BUFFER IMPLEMENTATION

    VertexBuffer* VertexBuffer::Create(float* vertices, unsigned size)
    {
        return new OpenGLVertexBuffer{ vertices, size };
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned size)
    {
        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLVertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, rendererID); }
    void OpenGLVertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    // END OPENGL VERTEX BUFFER IMPLEMENTATION

    // OPENGL INDEX BUFFER IMPLEMENTATION

    IndexBuffer* IndexBuffer::Create(unsigned* indices, unsigned count)
    {
        return new OpenGLIndexBuffer{ indices, count };
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned* indices, unsigned count) : IndexBuffer{ count }
    {
        glCreateBuffers(1, &rendererID);

        // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
        // binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLIndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID); }
    void OpenGLIndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    // END OPENGL INDEX BUFFER IMPLEMENTATION

    // OPENGL VERTEX ARRAY IMPLEMENTATION

    VertexArray* VertexArray::Create()
    {
        return new OpenGLVertexArray{};
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &rendererID);
    }

    void OpenGLVertexArray::bind() { glBindVertexArray(rendererID); }
    void OpenGLVertexArray::unbind() { glBindVertexArray(0); }

    void OpenGLVertexArray::add_vbuffer(const std::shared_ptr<VertexBuffer>& vbuffer)
    {
        glBindVertexArray(rendererID);
        vbuffer->bind();

        const BufferLayout& layout { vbuffer->layout() };
        const auto& elements { layout.elements() };
        for (int i {}; i < static_cast<int>(elements.size()); i++)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,
                elements[i].component_count(),
                ShaderData::to_opengltype(elements[i].shader_datatype),
                elements[i].normalized ? GL_TRUE : GL_FALSE,
                layout.stride(),
                (const void*)elements[i].offset
            );
        }

        vbuffers.push_back(vbuffer);
    }

    void OpenGLVertexArray::set_ibuffer(const std::shared_ptr<IndexBuffer>& ibuffer)
    {
        glBindVertexArray(rendererID);
        ibuffer->bind();

        this->ibuffer = ibuffer;
    }

    // END OPENGL VERTEX ARRAY IMPLEMENTATION
}

