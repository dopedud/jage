#include "JAGE/layers.h"

#include "JAGE/resources.h"

#include "log.h"

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer(window, "Game Layer") {}

    void GameLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching Game layer to layer stack.");

        renderer = Renderer::Create(m_window);
        debug_renderer = DebugRenderer::Create(m_window);

        ResourceHandle<ImageResource> image { ResourceManager::instance().get<ImageResource>("image.jpg") };
        ResourceHandle<TextResource> vertex_shader { ResourceManager::instance().get<TextResource>("default.vs") };
        ResourceHandle<TextResource> fragment_shader { ResourceManager::instance().get<TextResource>("default.fs") };
        ResourceHandle<ModelResource> cube { ResourceManager::instance().get<ModelResource>("cube.glb") };

        texture = Texture::Create(image.resource()->data());
        shader = Shader::Create(vertex_shader.resource()->content(), fragment_shader.resource()->content());
        mesh = Mesh::Create(cube.resource()->mesh_data(0));
        material = std::make_unique<Material>(shader.get(), cube.resource()->material_data(0));

        World::ApplicationContext app_ctx;
        app_ctx.window = m_window;
        app_ctx.renderer = renderer.get();
        world = World{ app_ctx };
        camera = Entity{ world, "FreeCamera" };
        object = Entity{ world, "Object" };

        camera.AddComponent<Transform>();
        camera.AddComponent<Camera>();

        object.AddComponent<Transform>();
        MeshRenderer mesh_renderer {};
        mesh_renderer.mesh = mesh.get();
        mesh_renderer.material = material.get();
        object.AddComponent<MeshRenderer>(&mesh_renderer);

        camera_component = camera.GetComponent<Camera>();

        JAGE_MSG_TRACE("Attached Game layer to layer stack.");
    }

    void GameLayer::OnDetach()
    {
        JAGE_MSG_TRACE("Detaching Game layer from layer stack.");

        shader.reset();
        texture.reset();

        JAGE_MSG_TRACE("Detached Game layer from layer stack.");
    }

    void GameLayer::OnUpdate()
    {
        world.progress(Time::DeltaTime());

        // glm::mat4 model { glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 1.0f, 0.0f, 2.0f }) };
        // glm::mat4 view { camera_component->view_matrix };
        // glm::mat4 projection { camera_component->projection_matrix };

        // shader->bind();
        // shader->set_uniform_mat4("model", glm::mat4{ 1.0f });
        // shader->set_uniform_mat4("view", view);
        // shader->set_uniform_mat4("projection", projection);
        // shader->unbind();

        // texture->bind();

        // mesh->render(shader.get());

        // texture->unbind();

        // debug_renderer->set_vp(view, projection);
        // debug_renderer->RenderGridLines(5, 25.0f);
        // debug_renderer->RenderBaseAxes(0.1f);
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

        dispatcher.dispatch<MouseScrolledEvent>([this](const MouseScrolledEvent& e) -> bool
        {
            world.emit_event<MouseScrolledEvent>(e);

            return true;
        });
    }
}
