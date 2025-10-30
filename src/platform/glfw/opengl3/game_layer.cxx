#include "JAGE/layers.h"
#include "JAGE/renderer/core.h"

#include "log.h"

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer(window, "Game Layer") {}

    static unsigned int VAO {};

    void GameLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching Game layer to layer stack.");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };

        std::string_view vertex_str {R"(
            #version 460 core
            layout (location = 0) in vec3 pos;

            void main()
            {
                gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
            }
        )"};

        std::string_view fragment_str {R"(
            #version 460 core
            out vec4 color;

            void main()
            {
                color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )"};

        shader = Shader::Create(vertex_str, fragment_str);

        vbuffer = VertexBuffer::Create(vertices, sizeof(vertices));

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

    }

    void GameLayer::OnEvent(const Event& e)
    {
        // JAGE_MSG_DEBUG("Game Layer | " + std::string{ e.to_string() });
    }
}
