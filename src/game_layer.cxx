#include "JAGE/layers.h"

#include "JAGE/resources.h"

#include "log.h"

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer(window, "Game Layer") {}

    void GameLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching Game layer to layer stack.");

        debug_renderer = DebugRenderer::Create();

        varray = VertexArray::Create();

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

        std::array<float, 3 * 9> vertices2
        {
            // position             // color                    // texcoords
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
            0.0f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f, 1.0f,     0.5f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f
        };

        std::array<unsigned, 3> indices2
        {
            0, 1, 2
        };

        BufferLayout layout
        {
            { ShaderData::Type::Float3, "v_position" },
            { ShaderData::Type::Float4, "v_color" },
            { ShaderData::Type::Float2, "v_texcoord" },
        };

        // ModelResource model { "Untitled.glb" }; 

        ResourceHandle<ImageResource> image { ResourceManager::instance().get<ImageResource>("image.jpg") };
        ResourceHandle<TextResource> vertex_shader { ResourceManager::instance().get<TextResource>("default.vs") };
        ResourceHandle<TextResource> fragment_shader { ResourceManager::instance().get<TextResource>("default.fs") };

        texture = Texture::Create(image.resource()->data(), image.resource()->width(), image.resource()->height());
        shader = Shader::Create(vertex_shader.resource()->content(), fragment_shader.resource()->content());

        std::unique_ptr<VertexBuffer> vbuffer { VertexBuffer::Create(vertices2.data(), sizeof(vertices2)) };
        vbuffer->set_layout(layout);
        varray->add_vbuffer(std::move(vbuffer));

        std::unique_ptr<IndexBuffer> ibuffer { IndexBuffer::Create(indices2.data(), sizeof(indices2)) };
        varray->set_ibuffer(std::move(ibuffer));

        camera.AddComponent<Transform>();
        camera.AddComponent<Camera>();

        JAGE_MSG_TRACE("Attached Game layer to layer stack.");
    }

    void GameLayer::OnDetach()
    {
        JAGE_MSG_TRACE("Detaching Game layer from layer stack.");

        varray.reset();
        shader.reset();
        texture.reset();

        JAGE_MSG_TRACE("Detached Game layer from layer stack.");
    }

    void GameLayer::OnRender()
    {
        world.progress(Time::DeltaTime());

        shader->bind();

        glm::mat4 model { glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }) };
        shader->set_uniform_mat4("model", model);

        const Camera* c { camera.GetComponent<Camera>() };
        shader->set_uniform_mat4("view", c->view_matrix);

        glm::mat4 projection { glm::infinitePerspectiveLH(glm::radians(60.0f), window->aspect_ratio(), 0.05f) };
        shader->set_uniform_mat4("projection", projection);

        texture->bind();
        varray->bind();
        debug_renderer->Render();
        texture->unbind();
        shader->unbind();

        debug_renderer->shader()->bind();
        debug_renderer->shader()->set_uniform_mat4("model", model);
        debug_renderer->shader()->set_uniform_mat4("view", c->view_matrix);
        debug_renderer->shader()->set_uniform_mat4("projection", projection);
        debug_renderer->RenderGridLines(10, 1.0f);
        debug_renderer->shader()->unbind();
    }

    void GameLayer::OnEvent(const Event& e)
    {
        // JAGE_MSG_DEBUG("Game Layer | " + e.to_string());
        EventDispatcher dispatcher { e };
        dispatcher.dispatch<KeyEvent>([](const KeyEvent& e) -> bool
        {
            if (e.action() == JAGE_ACTION_PRESSED && e.key() == JAGE_KEY_ESCAPE)
            {
                if (Input::GetCursorMode() == JAGE_CURSOR_MODE_NORMAL) Input::SetCursorMode(JAGE_CURSOR_MODE_DISABLED);
                else Input::SetCursorMode(JAGE_CURSOR_MODE_NORMAL);
            }

            return true;
        });
    }
}
