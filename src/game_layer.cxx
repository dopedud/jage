#include "JAGE/layers.h"

#include "JAGE/assets.h"

#include "log.h"

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer(window, "Game Layer") {}

    void GameLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching Game layer to layer stack.");

        renderer = Renderer::Create(m_window);
        debug_renderer = DebugRenderer::Create(m_window);

        AssetHandle<ImageAsset> image { AssetManager::instance().get<ImageAsset>("image.jpg") };
        AssetHandle<TextAsset> vertex_shader { AssetManager::instance().get<TextAsset>("default.vs") };
        AssetHandle<TextAsset> fragment_shader { AssetManager::instance().get<TextAsset>("default.fs") };
        AssetHandle<ModelAsset> cube { AssetManager::instance().get<ModelAsset>("potted_plant_3.fbx") };

        texture = Texture::Create(image.asset()->data());
        shader = Shader::Create(vertex_shader.asset()->content(), fragment_shader.asset()->content());
        mesh = Mesh::Create(cube.asset()->mesh_data(0));
        material = std::make_unique<Material>(shader.get(), cube.asset()->material_data(0));

        World::ApplicationContext app_ctx;
        app_ctx.window = m_window;
        app_ctx.renderer = renderer.get();
        app_ctx.debug_renderer = debug_renderer.get();
        world = World{ app_ctx };
        camera = Entity{ world, "FreeCamera" };
        object = Entity{ world, "Object" };

        camera.AddComponent<Transform>();
        camera.AddComponent<Camera>();

        object.AddComponent<Transform>();
        MeshRenderer mesh_renderer {};
        mesh_renderer.mesh = mesh.get();
        mesh_renderer.material = material.get();
        object.AddComponent<MeshRenderer>(mesh_renderer);

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
