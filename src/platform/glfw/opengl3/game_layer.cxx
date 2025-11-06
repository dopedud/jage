#include "JAGE/layers.h"
#include "JAGE/renderer/core.h"
#include "JAGE/resources/core.h"

#include "log.h"

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer(window, "Game Layer") {}

    void GameLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching Game layer to layer stack.");

        varray.reset(VertexArray::Create());

        std::array<float, 8 * 7> vertices
        {
            // position             // color
            -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f, 1.0f,
            0.5f,  0.5f, 0.5f,      1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
            0.5f,  -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f,  -0.5f, 0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f
        };

        std::array<unsigned, 3 * 12> indices
        {
            0, 1, 2,
            0, 4, 2,
            1, 2, 3,
            1, 5, 3,
            2, 3, 7,
            2, 4, 7,
            3, 7, 6,
            3, 5, 6,
            7, 6, 0,
            7, 4, 0,
            6, 5, 1,
            6, 0, 1
        };

        std::array<float, 3 * 7> vertices2
        {
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f, 1.0f, 
        };

        std::array<unsigned, 3> indices2
        {
            0, 1, 2
        };

        BufferLayout layout
        {
            { ShaderData::Type::Float3, "v_position" },
            { ShaderData::Type::Float4, "v_color" },
        };

        ShaderResource default_shader { "default.vs", "default.fs" };

        shader.reset(Shader::Create(default_shader.vs(), default_shader.fs()));

        vbuffer.reset(VertexBuffer::Create(vertices2.data(), sizeof(vertices2)));
        vbuffer->set_layout(layout);
        varray->add_vbuffer(vbuffer);

        ibuffer.reset(IndexBuffer::Create(indices2.data(), sizeof(indices2)));
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
