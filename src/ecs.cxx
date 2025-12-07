#include "JAGE/ecs.h"

#include "log.h"

namespace JAGE
{
    glm::mat4 Transform::rotation_matrix()
    {
        glm::vec3 rotrad { glm::radians(rotation) };
        return glm::yawPitchRoll(rotrad.y, rotrad.x, rotrad.z);
    } 

    ECS_COMPONENT_DECLARE(Transform);
    ECS_COMPONENT_DECLARE(Camera);

    World::World() : m_world { ecs_init() }
    {
        ECS_COMPONENT_DEFINE(m_world, Transform);
        ECS_COMPONENT_DEFINE(m_world, Camera);

        ECS_SYSTEM(m_world, CameraSystem, EcsOnUpdate, Transform, Camera);
        ECS_SYSTEM(m_world, CameraSystem_Initialise, EcsOnStart, Transform, Camera);
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
    // NOTE: template instantiations for Entity class only support component types

    template<> void Entity::AddComponent<Transform>() { ecs_add(m_world, m_entity, Transform); }
    template<> void Entity::AddComponent<Transform>(const Transform* component) { ecs_set_ptr(m_world, m_entity, Transform, component); }
    template<> const Transform* Entity::GetComponent<Transform>() { return ecs_get(m_world, m_entity, Transform); }
    template<> void Entity::RemoveComponent<Transform>() { ecs_remove(m_world, m_entity, Transform); }

    template<> void Entity::AddComponent<Camera>() { ecs_add(m_world, m_entity, Camera); }
    template<> void Entity::AddComponent<Camera>(const Camera* component) { ecs_set_ptr(m_world, m_entity, Camera, component); }
    template<> const Camera* Entity::GetComponent<Camera>() { return ecs_get(m_world, m_entity, Camera); }
    template<> void Entity::RemoveComponent<Camera>() { ecs_remove(m_world, m_entity, Camera); }

    // END TEMPLATE INSTANTIATIONS

    void CameraSystem_Initialise(ecs_iter_t* it)
    {
        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

        t.position = glm::vec3{};
        t.rotation = glm::vec3{};
        t.scale = glm::vec3{ 1.0f };

        c.view_matrix = glm::mat4{ 1.0f };

        c.right = glm::vec3{ 1.0f, 0.0f, 0.0f };
        c.up = glm::vec3{ 0.0f, 1.0f, 0.0f };
        c.front = glm::vec3{ 0.0f, 0.0f, 1.0f };

        c.speed = 0.001f;
        c.sensitivity = 0.5f;
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

        // glm::normalize will produce UB for vectors with length ~ 0.0f, so it must be tested first for such cases
        move_vector = !glm::length(move_vector) ? glm::vec3{} : (glm::normalize(move_vector) * it->delta_time);

        JAGE_LOG_DEBUG("look_vector.x - {}", look_vector.x);
        JAGE_LOG_DEBUG("look_vector.y - {}", look_vector.y);

        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

        t.rotation.x += look_vector.y * c.sensitivity;
        t.rotation.y += look_vector.x * c.sensitivity;

        if (t.rotation.x > 89.0f) t.rotation.x = 89.0f;
        if (t.rotation.x < -89.0f) t.rotation.x = -89.0f;

        // c.front.x = glm::cos(glm::radians(t.rotation.x)) * glm::cos(glm::radians(t.rotation.y - 90.0f));
        // c.front.y = glm::sin(glm::radians(t.rotation.x));
        // c.front.z = glm::cos(glm::radians(t.rotation.x)) * glm::sin(glm::radians(t.rotation.y - 90.0f));

        // c.front = glm::normalize(c.front);
        // c.right = glm::normalize(glm::cross(c.front, glm::vec3{ 0.0f, 1.0f, 0.0f }));
        // c.up = glm::normalize(glm::cross(c.right, c.front));

        // t.position +=
        // (
        //     c.right * move_vector.x +
        //     c.up * move_vector.y +
        //     c.front * move_vector.z
        // ) * c.speed;

        glm::mat4 rotation_matrix { t.rotation_matrix() };

        c.right = glm::normalize(rotation_matrix[0]);
        c.up    = glm::normalize(rotation_matrix[1]);
        c.front = glm::normalize(rotation_matrix[2]);

        JAGE_LOG_DEBUG("rotation.x - {}", t.rotation.x);
        JAGE_LOG_DEBUG("rotation.y - {}", t.rotation.y);

        JAGE_LOG_DEBUG("right - {}", c.right);
        JAGE_LOG_DEBUG("up - {}", c.up);
        JAGE_LOG_DEBUG("front - {}", c.front);

        t.position +=
        (
            c.right * move_vector.x +
            c.up * move_vector.y +
            c.front * move_vector.z
        ) * c.speed;

        c.view_matrix = glm::lookAtLH(t.position, t.position + c.front, c.up);
    }
}