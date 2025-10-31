#include "JAGE/layers.h"
#include "JAGE/renderer/core.h"

#include "log.h"

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer(window, "Game Layer") {}

    void GameLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching Game layer to layer stack.");

        varray.reset(VertexArray::Create());

        std::array<float, 3 * 7> vertices
        {
            // position             // color
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f,
            0.0f,  0.5f, 0.0f,      0.0f, 0.0f, 1.0f, 1.0f
        };

        std::array<unsigned int, 3> indices
        {
            0, 1, 2
        };

        BufferLayout layout
        {
            { ShaderData::Type::Float3, "v_position" },
            { ShaderData::Type::Float4, "v_color" },
        };

        std::string_view vertex_str
        {R"(
            #version 460 core

            layout (location = 0) in vec3 v_position;
            layout (location = 1) in vec4 v_color;

            out vec3 f_position;
            out vec4 f_color;

            void main()
            {
                f_position = v_position;
                f_color = v_color;

                gl_Position = vec4(v_position.x, v_position.y, v_position.z, 1.0);
            }
        )"};

        std::string_view fragment_str
        {R"(
            #version 460 core

            in vec3 f_position;
            in vec4 f_color;

            out vec4 color;

            void main()
            {
                color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
                color = f_color;
            }
        )"};

        shader.reset(Shader::Create(vertex_str, fragment_str));

        vbuffer.reset(VertexBuffer::Create(vertices.data(), sizeof(vertices)));
        vbuffer->set_layout(layout);
        varray->add_vbuffer(vbuffer);

        ibuffer.reset(IndexBuffer::Create(indices.data(), sizeof(indices)));
        varray->set_ibuffer(ibuffer);

        JAGE_MSG_TRACE("Attached Game layer to layer stack.");
    }

    void GameLayer::OnDetach()
    {
        JAGE_MSG_TRACE("Detaching Game layer to layer stack.");

        shader.reset();

        JAGE_MSG_TRACE("Detached Game layer to layer stack.");
    }

    void GameLayer::OnRender()
    {
        shader->bind();
        varray->bind();
        Renderer::Render();
    }

    void GameLayer::OnEvent(const Event& e)
    {
        // JAGE_MSG_DEBUG("Game Layer | " + std::string{ e.to_string() });
    }
}
