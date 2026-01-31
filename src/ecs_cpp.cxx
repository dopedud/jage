/**
 * 
 * 
 * SOURCE FILE NOT IN USE, ISSUE IS DESCRIBED BELOW:
 * 
 * Currently the issue is trying to get context data to work in `flecs::world`. When context data was set in a world
 * via `flecs::world::set_ctx()`, it somehow has invalid data when queried/fetched via `flecs::world::get_ctx()`. One
 * example would be to fetch application data from a running system, in which the system would need to fetch it from an
 * iterator via `flecs::iter::world()` to get the world, and then get the context data.
 * 
 *
 */

#include "JAGE/ecs.h"

#include "log.h"

namespace JAGE
{
    World::World(ApplicationContext app_ctx) : m_world {}, m_app_ctx { app_ctx }
    {
        JAGE_LOG_DEBUG("{}", app_ctx.window == nullptr);
        JAGE_LOG_DEBUG("{}", m_app_ctx.window == nullptr);
        JAGE_LOG_DEBUG("{}", reinterpret_cast<uintptr_t>(app_ctx.window));
        JAGE_LOG_DEBUG("{}", reinterpret_cast<uintptr_t>(m_app_ctx.window));
        JAGE_LOG_DEBUG("{}", reinterpret_cast<uintptr_t>(&m_app_ctx));
        m_world.set_ctx(&m_app_ctx);

        m_world.component<Transform>();
        m_world.component<Camera>();

        m_world.system<Transform, Camera>().kind(flecs::OnStart).run(CameraSystem_Initialise);
        m_world.system<Camera>().kind(flecs::OnStart).run(RenderSystem_Initialise);

        m_world.system<Transform>().run(TransformSystem);
        m_world.system<Transform, Camera>().run(CameraSystem);
        m_world.system<Transform, Camera>().ctx(&m_app_ctx).run(RenderSystem);
    }

    const flecs::world& World::world() const { return m_world; }

    void World::progress(float deltatime) { m_world.progress(deltatime); }

    Entity::Entity(const World& world, std::string_view name)
    : m_entity { world.world().entity(name.data()) } {}

    // TEMPLATE INSTANTIATIONS

    template<typename T> void       Entity::AddComponent()                      { m_entity.add<T>(); }
    template<typename T> void       Entity::AddComponent(const T& component)    { m_entity.set<T>(component); }
    template<typename T> const T&   Entity::GetComponent()                      { return m_entity.get<T>(); }
    template<typename T> T&         Entity::GetComponentMutable()               { return m_entity.get_mut<T>(); }
    template<typename T> void       Entity::RemoveComponent()                   { m_entity.remove<T>(); }

    template void               Entity::AddComponent<Transform>();
    template void               Entity::AddComponent<Transform>(const Transform& component);
    template const Transform&   Entity::GetComponent<Transform>();
    template Transform&         Entity::GetComponentMutable<Transform>();
    template void               Entity::RemoveComponent<Transform>();

    template void           Entity::AddComponent<Camera>();
    template void           Entity::AddComponent<Camera>(const Camera& component);
    template const Camera&  Entity::GetComponent<Camera>();
    template Camera&        Entity::GetComponentMutable<Camera>();
    template void           Entity::RemoveComponent<Camera>();


    // END TEMPLATE INSTANTIATIONS

    void CameraSystem_Initialise(flecs::iter& it)
    {
        while (it.next())
        {
            flecs::field transform { it.field<Transform>(0) };
            flecs::field camera { it.field<Camera>(1) };

            for (unsigned i : it)
            {
                Transform& t { transform[i] };
                Camera& c { camera[i] };

                t.position = glm::vec3{};
                t.orientation = glm::quat{ 1.0f, 0.0f, 0.0f, 0.0f };
                t.scale = glm::vec3{ 1.0f };

                c.move_speed = 0.01f;
                c.zoom_speed = 0.1f;
                c.sensitivity = 8.5f * 0.01f;

                c.pitch = 0.0f;
                c.yaw = 0.0f;
                c.fov = 90.0f;
            }
        }
    }

    void RenderSystem_Initialise(flecs::iter& it)
    {
        while (it.next())
        {
            flecs::field camera { it.field<Camera>(0) };

            for (unsigned i : it)
            {
                Camera& c { camera[i] };
                c.view_matrix = glm::mat4{ 1.0f };
                c.projection_matrix = glm::mat4{ 1.0f };
            }
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

    void CameraSystem(flecs::iter& it)
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

    void RenderSystem(flecs::iter& it)
    {
        while (it.next())
        {
            flecs::field transform { it.field<Transform>(0) };
            flecs::field camera { it.field<Camera>(1) };

            ApplicationContext* app_ctx { static_cast<ApplicationContext*>(it.world().get_ctx()) };
            JAGE_LOG_DEBUG("{}", reinterpret_cast<uintptr_t>(app_ctx));
            for (unsigned i : it)
            {
                Transform& t { transform[i] };
                Camera& c { camera[i] };

                JAGE_LOG_DEBUG("{}", app_ctx == nullptr);
                JAGE_LOG_DEBUG("{}", app_ctx->window == nullptr);
                JAGE_LOG_DEBUG("{}", app_ctx->value);
                JAGE_LOG_DEBUG("{}", reinterpret_cast<uintptr_t>(app_ctx->window));
                JAGE_LOG_DEBUG("{}", app_ctx->window->aspect_ratio());

                c.view_matrix = glm::lookAtLH(t.position, t.position + t.forward, t.up);
                c.projection_matrix = glm::infinitePerspectiveLH(glm::radians(c.fov), app_ctx->window->aspect_ratio(), 0.01f);
            }
        }
    }
}