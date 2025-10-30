#include "platform/glfw/opengl3/renderer.h"

#include "log.h"

#include <glad/glad.h>

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
        JAGE_LOG_INFO("     Vendor:     {}", (const char*)glGetString(GL_VENDOR));
        JAGE_LOG_INFO("     Renderer:   {}", (const char*)glGetString(GL_RENDERER));
        JAGE_LOG_INFO("     Version:    {}", (const char*)glGetString(GL_VERSION));

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

    namespace ShaderData
    {
        unsigned int size(ShaderDataType type)
        {
            switch (type)
            {
                case ShaderDataType::None:      return 0;
                case ShaderDataType::Float:     return 4;
                case ShaderDataType::Float2:    return 4 * 2;
                case ShaderDataType::Float3:    return 4 * 3;
                case ShaderDataType::Float4:    return 4 * 4;
                case ShaderDataType::Int:       return 4;
                case ShaderDataType::Int2:      return 4 * 2;
                case ShaderDataType::Int3:      return 4 * 3;
                case ShaderDataType::Int4:      return 4 * 4;
                case ShaderDataType::Mat3:      return 4 * 3 * 3;
                case ShaderDataType::Mat4:      return 4 * 4 * 4;
                case ShaderDataType::Bool:      return 1;
            }

            JAGE_MSG_ERROR("Shader error: unknown shader data type. Returning size 0.");

            return 0;
        }
    }

    static GLenum to_opengltype(ShaderData::ShaderDataType type)
    {
        switch (type)
        {
            case ShaderData::ShaderDataType::None:      return GL_NONE;
            case ShaderData::ShaderDataType::Mat3:
            case ShaderData::ShaderDataType::Mat4:
            case ShaderData::ShaderDataType::Float:
            case ShaderData::ShaderDataType::Float2:
            case ShaderData::ShaderDataType::Float3:
            case ShaderData::ShaderDataType::Float4:    return GL_FLOAT;
            case ShaderData::ShaderDataType::Int:
            case ShaderData::ShaderDataType::Int2:
            case ShaderData::ShaderDataType::Int3:
            case ShaderData::ShaderDataType::Int4:      return GL_INT;
            case ShaderData::ShaderDataType::Bool:      return GL_BOOL;
        }

        JAGE_MSG_ERROR("Shader error: unknown shader data type. Returning type 0.");

        return 0;
    }

    BufferElement::BufferElement(ShaderData::ShaderDataType type, std::string_view name)
    : shader_datatype { type }
    , name { name }
    , size { ShaderData::size(type) }
    {}

    unsigned int BufferElement::component_count() const
    {
        switch (shader_datatype)
        {
            case ShaderData::ShaderDataType::None:      return 0;
            case ShaderData::ShaderDataType::Float:     return 1;
            case ShaderData::ShaderDataType::Float2:    return 2;
            case ShaderData::ShaderDataType::Float3:    return 3;
            case ShaderData::ShaderDataType::Float4:    return 4;
            case ShaderData::ShaderDataType::Int:       return 1;
            case ShaderData::ShaderDataType::Int2:      return 2;
            case ShaderData::ShaderDataType::Int3:      return 3;
            case ShaderData::ShaderDataType::Int4:      return 4;
            case ShaderData::ShaderDataType::Mat3:      return 3 * 3;
            case ShaderData::ShaderDataType::Mat4:      return 4 * 4;
            case ShaderData::ShaderDataType::Bool:      return 1;
        }

        JAGE_MSG_ERROR("Shader error: unknown shader data type. Returning count 0.");

        return 0;
    }

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
    : m_elements { elements }
    {
        unsigned int offset {};
        m_stride = 0;

        for (auto& element : m_elements)
        {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

    // SHADER IMPLEMENTATION

    std::unique_ptr<Shader> Shader::Create(std::string_view vertex_str, std::string_view fragment_str)
    {
        return std::make_unique<OpenGLShader>(vertex_str, fragment_str);
    }

    DISABLE_WARNING_PUSH
    DISABLE_WARNING_GCC_CLANG("-Wvla")

    OpenGLShader::OpenGLShader(std::string_view vertex_str, std::string_view fragment_str)
    {
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

        glDetachShader(rendererID, vertex_shader);
        glDetachShader(rendererID, fragment_shader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(rendererID);
    }

    DISABLE_WARNING_POP

    void OpenGLShader::Bind() const
    {
        glUseProgram(rendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    // END SHADER IMPLEMENTATION

    // OPENGL VERTEX BUFFER IMPLEMENTATION

    std::unique_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
    {
        return std::make_unique<OpenGLVertexBuffer>(vertices, size);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
    {
        glCreateBuffers(1, &rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // END OPENGL VERTEX BUFFER IMPLEMENTATION

    // OPENGL INDEX BUFFER IMPLEMENTATION

    std::unique_ptr<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
    {
        return std::make_unique<OpenGLIndexBuffer>(indices, count);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count) : IndexBuffer { count }
    {
        glCreateBuffers(1, &rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
    }

    void OpenGLIndexBuffer::Unbind() const
    {
    }

    // END OPENGL INDEX BUFFER IMPLEMENTATION
}

