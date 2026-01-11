#include "JAGE/ecs.h"

#include "log.h"

namespace JAGE
{
    glm::vec3 Transform::right()    const { return glm::normalize(orientation * glm::vec3{1.0f, 0.0f, 0.0f}); }
    glm::vec3 Transform::up()       const { return glm::normalize(orientation * glm::vec3{0.0f, 1.0f, 0.0f}); }
    glm::vec3 Transform::forward()  const { return glm::normalize(orientation * glm::vec3{0.0f, 0.0f, 1.0f}); }

    glm::vec3 Transform::euler_angles() const { return glm::degrees(glm::eulerAngles(orientation)); }

    glm::mat4 Transform::transformation_matrix() const
    {
        return
            glm::translate(glm::mat4{ 1.0f }, position) *
            glm::mat4_cast(orientation) *
            glm::scale(glm::mat4{ 1.0f }, scale);
    }

    ECS_COMPONENT_DECLARE(Transform);
    ECS_COMPONENT_DECLARE(Camera);

    World::World() : m_world { ecs_init() }
    {
        ECS_COMPONENT_DEFINE(m_world, Transform);
        ECS_COMPONENT_DEFINE(m_world, Camera);

        ECS_SYSTEM(m_world, TransformSystem, EcsOnUpdate, Transform);

        ECS_SYSTEM(m_world, CameraSystem_Initialise, EcsOnStart, Transform, Camera);
        ECS_SYSTEM(m_world, CameraSystem, EcsOnUpdate, Transform, Camera);
        ECS_SYSTEM(m_world, RenderSystem_Initialise, EcsOnStart, Transform, Camera);
        ECS_SYSTEM(m_world, RenderSystem, EcsOnUpdate, Transform, Camera);
    }

    World::~World() { ecs_fini(m_world); }

    ecs_world_t* World::world() const { return m_world; }

    void World::progress(float deltatime) { ecs_progress(m_world, deltatime); }

    Entity::Entity(World* world, std::string_view name)
    : m_name { name }
    , m_world { world->world() }
    {
        ecs_entity_desc_t entity_desc {};
        entity_desc.name = m_name.c_str();

        m_entity = ecs_entity_init(m_world, &entity_desc);
    }

    Entity::~Entity() { ecs_delete(m_world, m_entity); }

    // TEMPLATE INSTANTIATIONS

    // NOTE: Template specializations are used here (instead of template instantiations) due to Flecs fundamentally
    // using macros to implement generic programming patterns. The template definitions are still provided for
    // reference.

    // template<typename T> void       Entity::AddComponent() { ecs_add(m_world, m_entity, T); }
    // template<typename T> void       Entity::AddComponent(const T* component) { ecs_set_ptr(m_world, m_entity, T, component); }
    // template<typename T> const T*   Entity::GetComponent() { return ecs_get(m_world, m_entity, T); }
    // template<typename T> T*         Entity::GetComponentMutable() { return ecs_get_mut(m_world, m_entity, T); }
    // template<typename T> void       Entity::RemoveComponent() { ecs_remove(m_world, m_entity, T); }

    template<> void                 Entity::AddComponent<Transform>()                               { ecs_add(m_world, m_entity, Transform); }
    template<> void                 Entity::AddComponent<Transform>(const Transform* component)     { ecs_set_ptr(m_world, m_entity, Transform, component); }
    template<> const Transform*     Entity::GetComponent<Transform>()                               { return ecs_get(m_world, m_entity, Transform); }
    template<> Transform*           Entity::GetComponentMutable<Transform>()                        { return ecs_get_mut(m_world, m_entity, Transform); }
    template<> void                 Entity::RemoveComponent<Transform>()                            { ecs_remove(m_world, m_entity, Transform); }

    template<> void             Entity::AddComponent<Camera>()                          { ecs_add(m_world, m_entity, Camera); }
    template<> void             Entity::AddComponent<Camera>(const Camera* component)   { ecs_set_ptr(m_world, m_entity, Camera, component); }
    template<> const Camera*    Entity::GetComponent<Camera>()                          { return ecs_get(m_world, m_entity, Camera); }
    template<> Camera*          Entity::GetComponentMutable<Camera>()                   { return ecs_get_mut(m_world, m_entity, Camera); }
    template<> void             Entity::RemoveComponent<Camera>()                       { ecs_remove(m_world, m_entity, Camera); }

    // END TEMPLATE INSTANTIATIONS

    void TransformSystem(ecs_iter_t* it)
    {
        Transform* transform { ecs_field(it, Transform, 0) };
        Transform& t { transform[0] };
        glm::mat4 transformation_matrix { t.transformation_matrix() };
    }

    void CameraSystem_Initialise(ecs_iter_t* it)
    {
        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

        t.position = glm::vec3{};
        t.orientation = glm::quat{ 1.0f, 0.0f, 0.0f, 0.0f };
        t.scale = glm::vec3{ 1.0f };

        c.speed = 0.01f;
        c.sensitivity = 8.5f * 0.01f;

        c.pitch = 0.0f;
        c.yaw = 0.0f;
        c.fov = 90.0f;
    }

    JAGE_API void RenderSystem_Initialise(ecs_iter_t* it)
    {
        Camera* camera { ecs_field(it, Camera, 1) };
        Camera& c { camera[0] };
        c.view_matrix = glm::mat4{ 1.0f };
    }

    void CameraSystem(ecs_iter_t* it)
    {
        if (Input::GetCursorMode() == JAGE_CURSOR_MODE_NORMAL) return;

        glm::vec3 move_vector {};

        if (Input::IsKeyPressed(JAGE_KEY_D)) move_vector.x += 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_A)) move_vector.x -= 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_SPACE)) move_vector.y += 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_LEFT_CONTROL)) move_vector.y -= 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_W)) move_vector.z += 1.0f;
        if (Input::IsKeyPressed(JAGE_KEY_S)) move_vector.z -= 1.0f;

        glm::vec2 look_vector { Input::GetMousePositionDeltaX(), Input::GetMousePositionDeltaY() };

        float speed_multiplier { 1.0f };
        if (Input::IsKeyPressed(JAGE_KEY_LEFT_SHIFT)) speed_multiplier = 5.0f;

        // glm::normalize will produce undefined behaviour for vectors with length ~ 0.0f, so it must be tested first
        // for such cases
        move_vector = !glm::length(move_vector) ? glm::vec3{} : (glm::normalize(move_vector) * it->delta_time);

        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

        c.yaw += look_vector.x * c.sensitivity;
        c.pitch += look_vector.y * c.sensitivity;
        c.pitch = glm::clamp(c.pitch, -90.0f, 90.0f);

        t.orientation = glm::quat{ glm::radians(glm::vec3{ c.pitch, c.yaw, 0.0f }) };

        t.position +=
        (
            t.right() * move_vector.x +
            t.up() * move_vector.y +
            t.forward() * move_vector.z
        ) * c.speed * speed_multiplier;
    }

    JAGE_API void RenderSystem(ecs_iter_t* it)
    {
        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

        c.view_matrix = glm::lookAtLH(t.position, t.position + t.forward(), t.up());
    }
}