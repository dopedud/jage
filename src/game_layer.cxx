#include "JAGE/layers.h"

#include "JAGE/assets.h"

#include "log.h"

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer(window, "Game Layer") {}

    void GameLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching Game layer to layer stack.");

        renderer = m_window->renderer();
        debug_renderer = m_window->debug_renderer();

        Asset::Handle<Asset::Image> image { AssetManager::instance().Get<Asset::Image>("image.jpg") };
        Asset::Handle<Asset::Text> vertex_shader { AssetManager::instance().Get<Asset::Text>("default.vs") };
        Asset::Handle<Asset::Text> fragment_shader { AssetManager::instance().Get<Asset::Text>("default.fs") };
        Asset::Handle<Asset::Model> model1 { AssetManager::instance().Get<Asset::Model>("potted_plant_3.fbx") };
        Asset::Handle<Asset::Model> model2 { AssetManager::instance().Get<Asset::Model>("z4.fbx") };

        texture = renderer->CreateTexture(image);
        shader = renderer->CreateShader(vertex_shader, fragment_shader);
        mesh1 = renderer->CreateMesh(model1, 0);
        mesh2 = renderer->CreateMesh(model2, 0);
        mat1 = renderer->CreateMaterial(model1, shader, 0);
        mat2 = renderer->CreateMaterial(model2, shader, 0);

        mat1.resource()->set_face_culling_mode(Resource::Material::FaceCullingMode::NONE);
        mat2.resource()->set_face_culling_mode(Resource::Material::FaceCullingMode::NONE);

        World::ApplicationContext app_ctx;
        app_ctx.window = m_window;
        app_ctx.renderer = renderer;
        app_ctx.debug_renderer = debug_renderer;
        world = World{ app_ctx };
        camera = world.CreateEntity("FreeCamera");
        object1 = world.CreateEntity("object1");
        object2 = world.CreateEntity("object2");

        camera.AddComponent<Transform>();
        camera.AddComponent<Camera>();

        object1.AddComponent<Transform>();
        object2.AddComponent<Transform>();
        MeshRenderer mesh_renderer1 {};
        mesh_renderer1.mesh = mesh1;
        mesh_renderer1.material = mat1;
        object1.AddComponent<MeshRenderer>(mesh_renderer1);
        MeshRenderer mesh_renderer2 {};
        mesh_renderer2.mesh = mesh2;
        mesh_renderer2.material = mat2;
        object2.AddComponent<MeshRenderer>(mesh_renderer2);

        JAGE_MSG_TRACE("Attached Game layer to layer stack.");
    }

    void GameLayer::OnDetach()
    {
        JAGE_MSG_TRACE("Detaching Game layer from layer stack.");

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
