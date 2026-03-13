/**
 * SOURCE FILE NOT IN USE, ISSUE IS DESCRIBED BELOW:
 * 
 * Currently the issue is trying to get context data to work in `flecs::world`. When context data was set in a world
 * via `flecs::world::set_ctx()`, it somehow returns invalid data when queried/fetched via `flecs::world::get_ctx()`. One
 * example would be to fetch application data from a running system, in which the system would need to fetch it from an
 * iterator via `flecs::iter::world()` to get the world, and then get the context data.
 * 
 * There is also the issue of flecs C++ API not shutting down properly when the application is halted suddenly. Even
 * when the application was shut down abruptly, it should call proper destructor functions (for example, for the case
 * of the `Layer` class, calling `Layer::OnDetach()`) for all created objects, including flecs's objects.
 */

#include "JAGE/ecs.h"

#include "log.h"

namespace JAGE
{
    World::World() : m_world {}, eventemitter {}, m_app_ctx {} {}

    World::World(ApplicationContext app_ctx)
    : m_world {}
    , eventemitter { m_world.entity("EventEmitter") }
    , m_app_ctx { std::make_unique<ApplicationContext>(app_ctx) }
    {
        m_world.set_ctx(m_app_ctx.get());

        m_world.component<Transform>();
        m_world.component<MeshRenderer>();
        m_world.component<Camera>();

        // m_world.observer<Camera>()
        // .event<MouseScrolledEvent>()
        // .run(CameraMovementSystem_OnMouseScrolled);

        m_world.system<Transform>().run(TransformSystem);
        m_world.system<Transform, Camera>().run(CameraMovementSystem);
        m_world.system<Transform, Camera>().run(CameraRenderSystem);
        m_world.system<Transform, MeshRenderer>().run(MeshRenderSystem);

        m_world.system().run(DebugRenderSystem);
    }

    World::World(World&& other) noexcept
    : m_world { other.m_world }
    , m_app_ctx { std::move(other.m_app_ctx) }
    {}

    World& World::operator=(World&& other) noexcept
    {
        if (this != &other)
        {
            m_world = other.m_world;
            m_app_ctx = std::move(other.m_app_ctx);
        }
        
        return *this;
    }

    const flecs::world& World::world() const { return m_world; }

    void World::progress(float deltatime) { m_world.progress(deltatime); }

    Entity::Entity() : m_entity {} {}

    Entity::Entity(const World& world, std::string_view name)
    : m_entity { world.world().entity(name.data()) } {}

    // TEMPLATE INSTANTIATIONS

    template<> void World::emit_event<MouseScrolledEvent>(const MouseScrolledEvent& e)
    {
        // m_world.event<MouseScrolledEvent>().ctx(e).emit();
    }

    template<typename T> void       Entity::AddComponent()                      { m_entity.add<T>(); }
    template<typename T> void       Entity::AddComponent(const T& component)    { m_entity.set<T>(component); }
    template<typename T> const T&   Entity::GetComponent()                      { return m_entity.get<T>(); }
    template<typename T> void       Entity::RemoveComponent()                   { m_entity.remove<T>(); }

    template void                   Entity::AddComponent<Transform>();
    template void                   Entity::AddComponent<Transform>(const Transform& component);
    template const Transform&       Entity::GetComponent<Transform>();
    template void                   Entity::RemoveComponent<Transform>();

    template void                   Entity::AddComponent<MeshRenderer>();
    template void                   Entity::AddComponent<MeshRenderer>(const MeshRenderer& component);
    template const MeshRenderer&    Entity::GetComponent<MeshRenderer>();
    template void                   Entity::RemoveComponent<MeshRenderer>();

    template void                   Entity::AddComponent<Camera>();
    template void                   Entity::AddComponent<Camera>(const Camera& component);
    template const Camera&          Entity::GetComponent<Camera>();
    template void                   Entity::RemoveComponent<Camera>();


    // END TEMPLATE INSTANTIATIONS

    void CameraMovementSystem_OnMouseScrolled(flecs::iter& it)
    {
        while (it.next())
        {
            flecs::field camera { it.field<Camera>(0) };
            Camera& c { camera[0] };
            MouseScrolledEvent* e { static_cast<MouseScrolledEvent*>(it.param()) };
            float scaled_delta { -e->offsetY() *10.0f * std::pow(c.fov / 90.0f, 2.0f) };
            c.fov = std::clamp(c.fov + scaled_delta, 1.0f, 150.0f);
        }
    }

    void TransformSystem(flecs::iter& it)
    {
        while (it.next())
        {
            flecs::field transform { it.field<Transform>(0) };

            for (unsigned i : it)
            {
                Transform& t { transform[i] };

                t.right     = glm::normalize(t.orientation * glm::vec3{1.0f, 0.0f, 0.0f}); 
                t.up        = glm::normalize(t.orientation * glm::vec3{0.0f, 1.0f, 0.0f}); 
                t.forward   = glm::normalize(t.orientation * glm::vec3{0.0f, 0.0f, 1.0f}); 

                t.euler_angles = glm::degrees(glm::eulerAngles(t.orientation));

                t.transformation_matrix = 
                    glm::translate(glm::mat4{ 1.0f }, t.position) *
                    glm::mat4_cast(t.orientation) *
                    glm::scale(glm::mat4{ 1.0f }, t.scale);
            }
        }
    }

    void MeshRenderSystem(flecs::iter& it)
    {
        while (it.next())
        {
            World::ApplicationContext* app_ctx { static_cast<World::ApplicationContext*>(it.world().get_ctx()) };
            Renderer* renderer { app_ctx->renderer };

            flecs::field transform { it.field<Transform>(0) };
            flecs::field mesh_renderer { it.field<MeshRenderer>(1) };

            for (unsigned i : it)
            {
                Transform& t { transform[i] };
                MeshRenderer& mr { mesh_renderer[i] };

                Shader* shader { mr.material->shader() };

                shader->bind();
                shader->set_uniform_mat4("model", t.transformation_matrix);
                shader->set_uniform_mat4("view", renderer->view());
                shader->set_uniform_mat4("projection", renderer->projection());
                shader->unbind();

                mr.mesh->render(mr.material);
            }
        }
    }

    void DebugRenderSystem(flecs::iter& it)
    {
        while (it.next())
        {
            World::ApplicationContext* app_ctx { static_cast<World::ApplicationContext*>(it.world().get_ctx()) };
            DebugRenderer* debug_renderer { app_ctx->debug_renderer };

            debug_renderer->RenderBaseAxes();
            debug_renderer->RenderGridLines(10, 1.0f);
        }
    }

    void CameraMovementSystem(flecs::iter& it)
    {
        if (Input::GetCursorMode() == JAGE_CURSOR_MODE_NORMAL) return;

        glm::vec3 move_vector {};
        float move_multiplier { 1.0f };
        float zoom {};
        float zoom_multiplier { 1.0f };

        if (Input::IsKeyPressed(JAGE_KEY_D)) move_vector.x += 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_A)) move_vector.x -= 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_SPACE)) move_vector.y += 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_LEFT_CONTROL)) move_vector.y -= 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_W)) move_vector.z += 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_S)) move_vector.z -= 1.0f;

        if (Input::IsKeyPressed(JAGE_KEY_E)) zoom -= 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_Q)) zoom += 1.0f;

        if (Input::IsKeyPressed(JAGE_KEY_LEFT_SHIFT))
        {
            move_multiplier = 5.0f;
            zoom_multiplier = 5.0f;
        }

        glm::vec2 look_vector { Input::GetMousePositionDeltaX(), Input::GetMousePositionDeltaY() };

        // glm::normalize will produce undefined behaviour for vectors with length ~ 0.0f, so it must be tested first
        // for such cases
        move_vector = glm::length(move_vector) ? glm::normalize(move_vector) : glm::vec3{};

        while (it.next())
        {
            flecs::field transform { it.field<Transform>(0) };
            flecs::field camera { it.field<Camera>(1) };

            float delta_time { it.delta_time() };

            for (unsigned i : it)
            {
                Transform& t { transform[i] };
                Camera& c { camera[i] };

                c.yaw += look_vector.x * c.sensitivity;
                c.pitch += look_vector.y * c.sensitivity;
                c.pitch = glm::clamp(c.pitch, -90.0f, 90.0f);

                t.orientation = glm::quat{ glm::radians(glm::vec3{ c.pitch, c.yaw, 0.0f }) };

                float scaled_delta { zoom * c.zoom_speed * zoom_multiplier * delta_time * std::pow(c.fov / 90.0f, 2.0f) };
                c.fov = std::clamp(c.fov + scaled_delta, 1.0f, 150.0f);

                t.position +=
                (
                    t.right * move_vector.x +
                    t.up * move_vector.y +
                    t.forward * move_vector.z
                ) * c.move_speed * move_multiplier * delta_time;
            }
        }
    }

    void CameraRenderSystem(flecs::iter& it)
    {
        while (it.next())
        {
            flecs::field transform { it.field<Transform>(0) };
            flecs::field camera { it.field<Camera>(1) };

            World::ApplicationContext* app_ctx { static_cast<World::ApplicationContext*>(it.world().get_ctx()) };

            for (unsigned i : it)
            {
                Transform& t { transform[i] };
                Camera& c { camera[i] };

                c.view_matrix = glm::lookAtLH(t.position, t.position + t.forward, t.up);
                c.projection_matrix = glm::infinitePerspectiveLH(glm::radians(c.fov), app_ctx->window->aspect_ratio(), 0.01f);
            }
        }
    }
}