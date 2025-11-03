#include "JAGE/layers.h"
#include "JAGE/renderer/core.h"
#include "JAGE/resource_manager/core.h"

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

        std::array<unsigned int, 3> indices
        {
            0, 1, 2
        };

        BufferLayout layout
        {
            { ShaderData::Type::Float3, "v_position" },
            { ShaderData::Type::Float4, "v_color" },
        };

        ShaderResource default_shader { ResourceManager::instance().DefaultShader() };

        shader.reset(Shader::Create(default_shader.get_vs(), default_shader.get_fs()));

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
        shader->unbind();
        varray->bind();
        Renderer::Render();
    }

    void GameLayer::OnEvent(const Event& e)
    {
        // JAGE_MSG_DEBUG("Game Layer | " + std::string{ e.to_string() });
    }
}
