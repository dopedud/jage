#include "platform/glfw/opengl3/renderer.h"

#include "log.h"

namespace JAGE
{
    OpenGLContext::OpenGLContext(Window* window) : GraphicsContext(window) {}

    void OpenGLContext::Init()
    {
        // need to initialise GLAD first to use glGetString()
        int glad_load_success { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        JAGE_ASSERT(glad_load_success, "Failed to initialise GLAD.");

        JAGE_MSG_INFO("Graphics Info:");
        JAGE_MSG_INFO("     Graphics Backend:   OpenGL");
        JAGE_LOG_INFO("     Vendor:             {}", (const char*)glGetString(GL_VENDOR));
        JAGE_LOG_INFO("     Renderer:           {}", (const char*)glGetString(GL_RENDERER));
        JAGE_LOG_INFO("     Version:            {}", (const char*)glGetString(GL_VERSION));

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
                case ShaderData::Type::None:      return GL_NONE;
                case ShaderData::Type::Mat3:
                case ShaderData::Type::Mat4:
                case ShaderData::Type::Float:
                case ShaderData::Type::Float2:
                case ShaderData::Type::Float3:
                case ShaderData::Type::Float4:    return GL_FLOAT;
                case ShaderData::Type::Int:
                case ShaderData::Type::Int2:
                case ShaderData::Type::Int3:
                case ShaderData::Type::Int4:      return GL_INT;
                case ShaderData::Type::Bool:      return GL_BOOL;
            }

            JAGE_MSG_ERROR("Shader error: unknown shader data type. Returning type 0.");

            return 0;
        }
    }

    // SHADER IMPLEMENTATION

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
            GLint maxLength {};
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar infoLog[maxLength];
            glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &infoLog[0]);

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
            GLint maxLength {};
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar infoLog[maxLength];
            glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragment_shader);

            JAGE_LOG_ERROR("OpenGL shader error: {}.", static_cast<std::string_view>(infoLog));

            return;
        }

        JAGE_MSG_TRACE("Fragment shader initialised.");

        rendererID = glCreateProgram();
        GLint linked {};

        glAttachShader(rendererID, vertex_shader);
        glAttachShader(rendererID, fragment_shader);
        glLinkProgram(rendererID);

        glGetProgramiv(rendererID, GL_LINK_STATUS, (int *)&linked);
        if (linked == GL_FALSE)
        {
            GLint maxLength {};
            glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar infoLog[maxLength];
            glGetProgramInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(rendererID);
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            JAGE_LOG_ERROR("OpenGL shader error: {}.", static_cast<std::string_view>(infoLog));

            return;
        }

        JAGE_MSG_TRACE("Shader program initialised.");

        glDetachShader(rendererID, vertex_shader);
        glDetachShader(rendererID, fragment_shader);

        JAGE_MSG_TRACE("OpenGL shader initialised.");
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(rendererID);
    }

    DISABLE_WARNING_POP

    void OpenGLShader::bind() const
    {
        glUseProgram(rendererID);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }

    // END SHADER IMPLEMENTATION

    // OPENGL VERTEX BUFFER IMPLEMENTATION

    VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
    {
        return new OpenGLVertexBuffer{ vertices, size };
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
    {
        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // END OPENGL VERTEX BUFFER IMPLEMENTATION

    // OPENGL INDEX BUFFER IMPLEMENTATION

    IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
    {
        return new OpenGLIndexBuffer{ indices, count };
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count) : IndexBuffer { count }
    {
        glCreateBuffers(1, &rendererID);

        // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
        // binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

    void OpenGLIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

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

    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(rendererID);
    }

    void OpenGLVertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

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
}

