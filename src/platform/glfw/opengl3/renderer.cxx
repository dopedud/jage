#include "platform/glfw/opengl3/renderer.h"

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

        glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(window->handle()),
        [](GLFWwindow* window, int width, int height) -> void
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
        glfwSwapBuffers(static_cast<GLFWwindow*>(m_window->handle()));
    }

    DISABLE_WARNING_PUSH
    DISABLE_WARNING_GCC_CLANG("-Wvla")

    GLuint CreateSubShader(const GLchar* source, unsigned subshader_type)
    {
        JAGE_MSG_TRACE("Initialising subshader.");

        GLint compiled {};

        GLuint subshader { glCreateShader(subshader_type) };
        glShaderSource(subshader, 1, &source, 0);

        glCompileShader(subshader);
        glGetShaderiv(subshader, GL_COMPILE_STATUS, &compiled);
        if(compiled == GL_FALSE)
        {
            JAGE_LOG_DEBUG("SUBSHADER TYPE: {}", subshader_type);
            GLint max_length {};
            glGetShaderiv(subshader, GL_INFO_LOG_LENGTH, &max_length);

            GLchar infoLog[max_length];
            glGetShaderInfoLog(subshader, max_length, &max_length, &infoLog[0]);

            glDeleteShader(subshader);

            JAGE_LOG_ERROR("OpenGL shader error: {}.", static_cast<std::string_view>(infoLog));
            JAGE_MSG_ERROR("Returning invalid subshader.");

            return 0;
        }

        JAGE_MSG_TRACE("Subshader initialised.");

        return subshader;
    }

    template<typename... SubShaders>
    GLuint CreateShaderProgram(SubShaders... subshaders)
    {
        JAGE_MSG_TRACE("Initialising shader program.");

        GLuint shaderID { glCreateProgram() };
        GLint linked {};

        // coerce all received arguments to be of type GLuint
        GLuint subshaders_array[] { subshaders... };

        for (GLuint subshader : subshaders_array) glAttachShader(shaderID, subshader);

        glLinkProgram(shaderID);

        glGetProgramiv(shaderID, GL_LINK_STATUS, &linked);
        if (linked == GL_FALSE)
        {
            GLint max_length {};
            glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &max_length);

            GLchar infoLog[max_length];
            glGetProgramInfoLog(shaderID, max_length, &max_length, &infoLog[0]);

            glDeleteProgram(shaderID);
            for (GLuint subshader : subshaders_array) glDeleteShader(subshader);

            JAGE_LOG_ERROR("OpenGL shader error: {}.", static_cast<std::string_view>(infoLog));
            JAGE_MSG_ERROR("Returning invalid shader program.");

            return 0;
        }

        for (GLuint subshader : subshaders_array) glDetachShader(shaderID, subshader);

        JAGE_MSG_TRACE("Shader program initialised.");

        return shaderID;
    }

    DISABLE_WARNING_POP

    GLenum OpenGLShader::to_opengl_type(Shader::DataType datatype)
    {
        switch (datatype)
        {
            case DataType::None:    return GL_NONE;
            case DataType::Mat3:
            case DataType::Mat4:
            case DataType::Float:
            case DataType::Float2:
            case DataType::Float3:
            case DataType::Float4:  return GL_FLOAT;
            case DataType::Int:
            case DataType::Int2:
            case DataType::Int3:
            case DataType::Int4:    return GL_INT;
            case DataType::Bool:    return GL_BOOL;
        }

        JAGE_MSG_ERROR("JAGE shader error: unknown shader data type. Returning type 0.");

        return 0;
    }

    OpenGLShader::OpenGLShader(std::string_view vertex_str, std::string_view fragment_str)
    {
        JAGE_MSG_TRACE("Initialising an OpenGL shader.");

        GLuint vertex_shader { CreateSubShader(vertex_str.data(), GL_VERTEX_SHADER) };
        GLuint fragment_shader { CreateSubShader(fragment_str.data(), GL_FRAGMENT_SHADER) };

        shaderID = CreateShaderProgram(vertex_shader, fragment_shader);

        JAGE_MSG_TRACE("OpenGL shader initialised.");
    }

    OpenGLShader::~OpenGLShader() { glDeleteProgram(shaderID); }

    void OpenGLShader::bind() const { glUseProgram(shaderID); }
    void OpenGLShader::unbind() const { glUseProgram(0); }

    void OpenGLShader::set_uniform_bool(std::string_view name, bool value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform1i(loc, static_cast<int>(value));
    }

    void OpenGLShader::set_uniform_uint(std::string_view name, unsigned value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform1i(loc, value);
    }

    void OpenGLShader::set_uniform_int(std::string_view name, int value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform1i(loc, value);
    }

    void OpenGLShader::set_uniform_float(std::string_view name, float value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform1f(loc, value);
    }

    void OpenGLShader::set_uniform_float2(std::string_view name, const glm::vec2& value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform2f(loc, value.x, value.y);
    }

    void OpenGLShader::set_uniform_float3(std::string_view name, const glm::vec3& value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform3f(loc, value.x, value.y, value.z);
    }

    void OpenGLShader::set_uniform_float4(std::string_view name, const glm::vec4& value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniform4f(loc, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::set_uniform_mat4(std::string_view name, const glm::mat4& value)
    {
        GLint loc { glGetUniformLocation(shaderID, name.data()) };
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    OpenGLTexture::OpenGLTexture(const ImageData* imagedata)
    {
        glGenTextures(1, &textureID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagedata->width, imagedata->height,
            0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata->pixels.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture::~OpenGLTexture() { glDeleteTextures(1, &textureID); }

    void OpenGLTexture::bind() { glBindTexture(GL_TEXTURE_2D, textureID); }
    void OpenGLTexture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

    OpenGLMesh::OpenGLMesh(const MeshData* meshdata)
    : Mesh{ meshdata }
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, meshdata->vertices.size() * sizeof(MeshData::VertexData), &meshdata->vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshdata->indices.size() * sizeof(unsigned), &meshdata->indices[0], GL_STATIC_DRAW);

        BufferLayout layout
        {
            { Shader::DataType::Float3, "v_position" },
            { Shader::DataType::Float3, "v_normal" },

            // the number of vertex UV coordinates used should follow the size of the MeshData::Vertex::uvcoords array
            { Shader::DataType::Float2, "v_uvcoord0" },
            { Shader::DataType::Float2, "v_uvcoord1" },
            { Shader::DataType::Float2, "v_uvcoord2" },
            { Shader::DataType::Float2, "v_uvcoord3" },

            // the number of vertex colors used should follow the size of the MeshData::Vertex::colors array
            { Shader::DataType::Float4, "v_color0" },
            { Shader::DataType::Float4, "v_color1" },
            { Shader::DataType::Float4, "v_color2" },
            { Shader::DataType::Float4, "v_color3" },
        };

        const std::vector<BufferElement>& elements { layout.elements() };

        for (unsigned i {}; i < elements.size(); i++)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,
                elements[i].component_count(),
                OpenGLShader::to_opengl_type(elements[i].shader_datatype),
                elements[i].normalized ? GL_TRUE : GL_FALSE,
                sizeof(MeshData::VertexData),
                reinterpret_cast<void*>(elements[i].offset)
            );
        }

        glBindVertexArray(0);
    }

    void OpenGLMesh::render(const Material* material)
    {
        material->shader()->bind();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, m_meshdata->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        material->shader()->unbind();
    }

    OpenGLRenderer::OpenGLRenderer(Window* window) : Renderer{ window } {}
    OpenGLRenderer::~OpenGLRenderer() {}

    OpenGLDebugRenderer::OpenGLDebugRenderer(Window* window)
    : DebugRenderer{ window }
    , grid_shader
    {
        R"(
            #version 460 core
            layout (location = 0) in vec3 v_position;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            void main()
            {
                gl_Position = projection * view * model * vec4(v_position, 1.0);
                // vec4 view_space = view * model * vec4(v_position, 1.0);

                // float sign_x = sign(view_space.x);
                // float sign_y = sign(view_space.y);
                // float sign_z = sign(view_space.z);
                // float factor = 5.5;
                // view_space.x = sign_x * sqrt(abs(view_space.x) * factor);
                // view_space.y = sign_y * sqrt(abs(view_space.y) * factor);
                // view_space.z = sign_z * sqrt(abs(view_space.z) * factor);

                // gl_Position = projection * view_space;
            }
        )",
        R"(
            #version 460 core

            out vec4 color;

            void main()
            {
                color = vec4(0.5, 0.5, 0.5, 0.5);
            }
        )"
    }
    , axes_shader
    {
        R"(
            #version 460 core
            layout (location = 0) in vec3 v_position;

            out vec3 f_position;

            uniform mat4 view;
            uniform mat4 projection;

            void main()
            {
                f_position = v_position;
                gl_Position = projection * view * vec4(v_position, 1.0);

            }
        )",
        R"(
            #version 460 core

            in vec3 f_position;

            out vec4 color;

            void main()
            {
                color = vec4(normalize(f_position), 1.0);
            }
        )"
    }
    {
        glGenVertexArrays(1, &grid_vao);
        glGenVertexArrays(1, &axes_vao);
        glGenBuffers(1, &grid_vbo);
        glGenBuffers(1, &axes_vbo);
        glGenBuffers(1, &grid_ebo);
        glGenBuffers(1, &axes_ebo);
    }

    OpenGLDebugRenderer::~OpenGLDebugRenderer()
    {
        glDeleteVertexArrays(1, &grid_vao);
        glDeleteBuffers(1, &grid_vbo);
        glDeleteBuffers(1, &grid_ebo);
    }

    void OpenGLDebugRenderer::RenderGridLines(unsigned slices, float spacing)
    {
        static bool init { true };
        static std::vector<float> vertices {};
        static std::vector<unsigned> indices {};

        static unsigned m_slices {};
        static float m_spacing {};
        static unsigned m_major {};

        if (init ||
            m_slices != slices || m_spacing != spacing)
        {
            init = false;

            m_slices = slices;
            m_spacing = glm::abs(spacing);

            vertices.clear();
            indices.clear();

            int slices_int { static_cast<int>(slices) };

            for (int slice_index { -slices_int }; slice_index <= slices_int; slice_index++)
            {
                for (int sub_slice_index { -slices_int }; sub_slice_index <= slices_int; sub_slice_index++)
                {
                    // first vertex of vertices pair along X-axis
                    vertices.push_back(static_cast<float>(sub_slice_index) * m_spacing);
                    vertices.push_back(static_cast<float>(-slices_int) * m_spacing);
                    vertices.push_back(static_cast<float>(slice_index) * m_spacing);

                    // second vertex of vertices pair along X-axis
                    vertices.push_back(static_cast<float>(sub_slice_index) * m_spacing);
                    vertices.push_back(static_cast<float>(slices_int) * m_spacing);
                    vertices.push_back(static_cast<float>(slice_index) * m_spacing);

                    // first vertex of vertices pair along Y-axis
                    vertices.push_back(static_cast<float>(-slices_int) * m_spacing);
                    vertices.push_back(static_cast<float>(sub_slice_index) * m_spacing);
                    vertices.push_back(static_cast<float>(slice_index) * m_spacing);

                    // second vertex of vertices pair along Y-axis
                    vertices.push_back(static_cast<float>(slices_int) * m_spacing);
                    vertices.push_back(static_cast<float>(sub_slice_index) * m_spacing);
                    vertices.push_back(static_cast<float>(slice_index) * m_spacing);

                    // first vertex of vertices pair along Z-axis
                    vertices.push_back(static_cast<float>(sub_slice_index) * m_spacing);
                    vertices.push_back(static_cast<float>(slice_index) * m_spacing);
                    vertices.push_back(static_cast<float>(-slices_int) * m_spacing);

                    // second vertex of vertices pair along Z-axis
                    vertices.push_back(static_cast<float>(sub_slice_index) * m_spacing);
                    vertices.push_back(static_cast<float>(slice_index) * m_spacing);
                    vertices.push_back(static_cast<float>(slices_int) * m_spacing);

                    u64 index { indices.size() };

                    indices.push_back(index + 0); indices.push_back(index + 1);
                    indices.push_back(index + 2); indices.push_back(index + 3);
                    indices.push_back(index + 4); indices.push_back(index + 5);
                }
            }

            glBindVertexArray(grid_vao);

            glBindBuffer(GL_ARRAY_BUFFER, grid_vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
            glEnableVertexAttribArray(0);

            glBindVertexArray(0);
        }

        glm::vec3 view_pos { glm::inverse(m_view)[3] };
        glm::mat4 model { glm::translate(glm::mat4{ 1.0f }, glm::floor(view_pos / m_spacing) * m_spacing) };

        grid_shader.bind();
        grid_shader.set_uniform_mat4("model", model);
        grid_shader.set_uniform_mat4("view", m_view);
        grid_shader.set_uniform_mat4("projection", m_projection);

        glBindVertexArray(grid_vao);
        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        grid_shader.unbind();
    }

    void OpenGLDebugRenderer::RenderBaseAxes(float size)
    {
        static bool init { true };
        static std::vector<float> vertices {};
        static std::vector<unsigned> indices {};

        static float m_size {};

        if (init ||
        m_size != size)
        {
            init = false;

            m_size = size;

            vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(0.0f);
            vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f);
            vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);
            vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(1.0f);

            indices.push_back(0); indices.push_back(1);
            indices.push_back(0); indices.push_back(2);
            indices.push_back(0); indices.push_back(3);

            glBindVertexArray(axes_vao);

            glBindBuffer(GL_ARRAY_BUFFER, axes_vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axes_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
            glEnableVertexAttribArray(0);

            glBindVertexArray(0);
        }

        glm::vec3 forward { m_view[0][2], m_view[1][2], m_view[2][2] };
        glm::vec3 up { m_view[0][1], m_view[1][1], m_view[2][1] };

        glm::vec3 view_pos { forward * -10.0f };

        glm::mat4 orbited_view { glm::lookAtLH(view_pos, view_pos + forward, up) };

        float inv_size { 1.0f / size };

        axes_shader.bind();
        axes_shader.set_uniform_mat4("view", orbited_view);
        axes_shader.set_uniform_mat4("projection",
            glm::orthoLH
            (
                -inv_size * m_window->aspect_ratio(),
                inv_size * m_window->aspect_ratio(),
                -inv_size, inv_size, 0.01f, 100.0f
            ));

        glBindVertexArray(axes_vao);
        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        axes_shader.unbind();
    }
}
