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

    OpenGLContext::OpenGLContext(Window* window) : GraphicsContext{ window }
    {
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

        glViewport(0, 0, window->width(), window->height());

        glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(window->handle()), [](GLFWwindow* window, int width, int height) -> void
        {
            glViewport(0, 0, width, height);
        });
    }

    void OpenGLContext::Clear()
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        GLenum to_opengl_type(Type type)
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

    OpenGLTexture::OpenGLTexture(unsigned char* data, unsigned width, unsigned height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &textureID);
    }

    void OpenGLTexture::bind() { glBindTexture(GL_TEXTURE_2D, textureID); }
    void OpenGLTexture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

    DISABLE_WARNING_PUSH
    DISABLE_WARNING_GCC_CLANG("-Wvla")

    OpenGLShader::OpenGLShader(std::string_view vertex_str, std::string_view fragment_str)
    : Shader{ vertex_str, fragment_str }
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

    OpenGLShader::~OpenGLShader() { glDeleteProgram(shaderID); }

    DISABLE_WARNING_POP

    void OpenGLShader::bind() const { glUseProgram(shaderID); }
    void OpenGLShader::unbind() const { glUseProgram(0); }

    void OpenGLShader::set_uniform_bool(std::string_view name, bool value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform1i(loc, static_cast<int>(value));
    }

    void OpenGLShader::set_uniform_int(std::string_view name, int value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform1i(loc, value);
    }

    void OpenGLShader::set_uniform_uint(std::string_view name, unsigned value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform1i(loc, value);
    }

    void OpenGLShader::set_uniform_float(std::string_view name, float value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform1i(loc, value);
    }

    void OpenGLShader::set_uniform_mat4(std::string_view name, const glm::mat4& value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
    }

    OpenGLMesh::OpenGLMesh(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned>& indices,
        const std::vector<std::unique_ptr<Texture>>& textures
    )
    // : Mesh{ vertices, indices, textures }
    {
        glCreateVertexArrays(1, &vao);
        glCreateBuffers(1, &vbo);
        glCreateBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

        BufferLayout layout
        {
            { ShaderData::Type::Float3, "v_position" },
            { ShaderData::Type::Float3, "v_normal" },
            { ShaderData::Type::Float4, "v_color" },
            { ShaderData::Type::Float2, "v_texcoords" },
        };

        const std::vector<BufferElement>& elements { layout.elements() };

        for (int i {}; i < static_cast<int>(elements.size()); i++)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,
                elements[i].component_count(),
                ShaderData::to_opengl_type(elements[i].shader_datatype),
                elements[i].normalized ? GL_TRUE : GL_FALSE,
                layout.stride(),
                (void*)elements[i].offset
            );
        }

        glBindVertexArray(0);
    }

    void OpenGLMesh::draw(const std::unique_ptr<Shader>& shader)
    {
        shader->bind();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        shader->unbind();
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned size)
    {
        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &rendererID); }

    void OpenGLVertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, rendererID); }
    void OpenGLVertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned* indices, unsigned count) : IndexBuffer{ count }
    {
        glCreateBuffers(1, &rendererID);

        // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
        // binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &rendererID); }

    void OpenGLIndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID); }
    void OpenGLIndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    OpenGLVertexArray::OpenGLVertexArray() { glCreateVertexArrays(1, &rendererID); }
    OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &rendererID); }

    void OpenGLVertexArray::bind() { glBindVertexArray(rendererID); }
    void OpenGLVertexArray::unbind() { glBindVertexArray(0); }

    void OpenGLVertexArray::add_vbuffer(std::unique_ptr<VertexBuffer>&& vbuffer)
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
                ShaderData::to_opengl_type(elements[i].shader_datatype),
                elements[i].normalized ? GL_TRUE : GL_FALSE,
                layout.stride(),
                (const void*)elements[i].offset
            );
        }

        vbuffers.push_back(std::move(vbuffer));
    }

    void OpenGLVertexArray::set_ibuffer(std::unique_ptr<IndexBuffer>&& ibuffer)
    {
        glBindVertexArray(rendererID);
        ibuffer->bind();

        this->ibuffer = std::move(ibuffer);
    }
}

