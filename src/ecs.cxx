#include "JAGE/ecs.h"

#include "log.h"

namespace JAGE
{
    DISABLE_WARNING_PUSH
    DISABLE_WARNING_GCC_CLANG("-Wmissing-field-initializers")

    ECS_COMPONENT_DECLARE(Transform);
    ECS_COMPONENT_DECLARE(Camera);

    ECS_COMPONENT_DECLARE(MouseScrolledEvent);

    World::World() : m_world {}, m_app_ctx {} {}

    World::World(ApplicationContext app_ctx)
    : m_world { ecs_init() }
    , m_app_ctx { std::make_unique<ApplicationContext>(app_ctx) }
    {
        ecs_set_ctx(m_world, m_app_ctx.get(), nullptr);

        ECS_COMPONENT_DEFINE(m_world, Transform);
        ECS_COMPONENT_DEFINE(m_world, Camera);

        ECS_COMPONENT_DEFINE(m_world, MouseScrolledEvent);

        ECS_SYSTEM(m_world, CameraSystem_Initialise, EcsOnStart, Transform, Camera);
        ECS_SYSTEM(m_world, RenderSystem_Initialise, EcsOnStart, Transform, Camera);

        ECS_SYSTEM(m_world, TransformSystem, EcsOnUpdate, Transform);
        ECS_SYSTEM(m_world, CameraSystem, EcsOnUpdate, Transform, Camera);
        ECS_SYSTEM(m_world, RenderSystem, EcsOnUpdate, Transform, Camera);
    }

    DISABLE_WARNING_POP

    World::~World() { release(); }

    World::World(World&& other) noexcept
    : m_world { other.m_world }
    , m_app_ctx { std::move(other.m_app_ctx) }
    {
        other.m_world = nullptr;
    }

    World& World::operator=(World&& other) noexcept
    {
        if (this != &other)
        {
            release();

            m_world = other.m_world;
            m_app_ctx = std::move(other.m_app_ctx);

            other.m_world = nullptr;
        }

        return *this;
    }

    ecs_world_t* World::world() const { return m_world; }

    void World::progress(float deltatime) { ecs_progress(m_world, deltatime); }

    // copied from flecs's source code
    void World::release()
    {
        if (m_world)
        {
            if (!flecs_poly_release(m_world))
            {
                if (ecs_stage_get_id(m_world) == -1) ecs_stage_free(m_world);
                
                else
                {
                    // before we call ecs_fini(), we increment the reference count back to 1
                    // otherwise, copies of this object created during ecs_fini (e.g. a component on_remove hook)
                    // would call again this destructor and ecs_fini().
                    flecs_poly_claim(m_world);
                    ecs_fini(m_world);
                }
            }

            m_world = nullptr;
            m_app_ctx.release();
        }        
    }

    Entity::Entity() : m_world {}, m_name {}, m_entity {} {}

    Entity::Entity(const World& world, std::string_view name)
    : m_world { world.world() }
    , m_name { name }
    , m_entity {}
    {
        ecs_entity_desc_t entity_desc {};
        entity_desc.name = m_name.c_str();

        m_entity = ecs_entity_init(m_world, &entity_desc);
    }

    Entity::~Entity() { release(); }

    Entity::Entity(Entity&& other) noexcept
    : m_world { other.m_world }
    , m_name { other.m_name }
    , m_entity { other.m_entity }
    {
        other.m_world = nullptr;
        other.m_name = "";
        other.m_entity = 0;
    }

    Entity& Entity::operator=(Entity&& other) noexcept
    {
        if (this != &other)
        {
            release();

            m_world = other.m_world;
            m_name = other.m_name;
            m_entity = other.m_entity;

            other.m_world = nullptr;
            other.m_name = "";
            other.m_entity = 0;
        }

        return *this;
    }

    void Entity::release()
    {
        if (m_world && m_entity && ecs_is_valid(m_world, m_entity))
        {
            ecs_delete(m_world, m_entity);
        }
    }

    // TEMPLATE INSTANTIATIONS

    // NOTE: Template specializations are used here (instead of template instantiations) due to Flecs fundamentally
    // using macros to implement generic programming patterns. The template definitions are still provided for
    // reference.

    // template<typename T> void       Entity::AddComponent()                       { ecs_add(m_world, m_entity, T); }
    // template<typename T> void       Entity::AddComponent(const T* component)     { ecs_set_ptr(m_world, m_entity, T, component); }
    // template<typename T> const T*   Entity::GetComponent()                       { return ecs_get(m_world, m_entity, T); }
    // template<typename T> T*         Entity::GetComponentMutable()                { return ecs_get_mut(m_world, m_entity, T); }
    // template<typename T> void       Entity::RemoveComponent()                    { ecs_remove(m_world, m_entity, T); }

    template<> void                 Entity::AddComponent<Transform>()                               { ecs_add(m_world, m_entity, Transform); }
    template<> void                 Entity::AddComponent<Transform>(const Transform* component)     { ecs_set_ptr(m_world, m_entity, Transform, component); }
    template<> const Transform&     Entity::GetComponent<Transform>()                               { return *ecs_get(m_world, m_entity, Transform); }
    template<> Transform&           Entity::GetComponentMutable<Transform>()                        { return *ecs_get_mut(m_world, m_entity, Transform); }
    template<> void                 Entity::RemoveComponent<Transform>()                            { ecs_remove(m_world, m_entity, Transform); }

    template<> void             Entity::AddComponent<Camera>()                          { ecs_add(m_world, m_entity, Camera); }
    template<> void             Entity::AddComponent<Camera>(const Camera* component)   { ecs_set_ptr(m_world, m_entity, Camera, component); }
    template<> const Camera&    Entity::GetComponent<Camera>()                          { return *ecs_get(m_world, m_entity, Camera); }
    template<> Camera&          Entity::GetComponentMutable<Camera>()                   { return *ecs_get_mut(m_world, m_entity, Camera); }
    template<> void             Entity::RemoveComponent<Camera>()                       { ecs_remove(m_world, m_entity, Camera); }

    // END TEMPLATE INSTANTIATIONS

    void CameraSystem_Initialise(ecs_iter_t* it)
    {
        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

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

    void RenderSystem_Initialise(ecs_iter_t* it)
    {
        Camera* camera { ecs_field(it, Camera, 1) };
        Camera& c { camera[0] };
        c.view_matrix = glm::mat4{ 1.0f };
    }

    void TransformSystem(ecs_iter_t* it)
    {
        Transform* transform { ecs_field(it, Transform, 0) };

        for (unsigned i {}; i < it->count; i++)
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

    void CameraSystem(ecs_iter_t* it)
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

        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        float delta_time { it->delta_time };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

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

    void RenderSystem(ecs_iter_t* it)
    {
        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

        ApplicationContext* app_ctx { static_cast<ApplicationContext*>(ecs_get_ctx(it->world)) };

        c.view_matrix = glm::lookAtLH(t.position, t.position + t.forward, t.up);
        c.projection_matrix = glm::infinitePerspectiveLH(glm::radians(c.fov), app_ctx->window->aspect_ratio(), 0.01f);
    }
}