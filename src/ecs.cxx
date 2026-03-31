#include "JAGE/ecs.h"

#include "log.h"

namespace JAGE
{
    DISABLE_WARNING_PUSH
    DISABLE_WARNING_GCC_CLANG("-Wmissing-field-initializers")

    ECS_COMPONENT_DECLARE(Transform);
    ECS_COMPONENT_DECLARE(MeshRenderer);
    ECS_COMPONENT_DECLARE(Camera);

    ECS_SYSTEM_DECLARE(CameraMovementSystem_OnMouseScrolled);

    World::World() : m_world {}, m_app_ctx {} {}

    World::World(ApplicationContext app_ctx)
    : m_world { ecs_init() }
    , m_app_ctx { std::make_unique<ApplicationContext>(app_ctx) }
    {
        ecs_set_ctx(m_world, m_app_ctx.get(), nullptr);

        ECS_COMPONENT_DEFINE(m_world, Transform);
        ECS_COMPONENT_DEFINE(m_world, MeshRenderer);
        ECS_COMPONENT_DEFINE(m_world, Camera);

        ECS_SYSTEM_DEFINE(m_world, CameraMovementSystem_OnMouseScrolled, 0, Camera);

        ECS_SYSTEM(m_world, TransformSystem, EcsOnUpdate, Transform);
        ECS_SYSTEM(m_world, CameraMovementSystem, EcsOnUpdate, Transform, Camera);
        ECS_SYSTEM(m_world, CameraRenderSystem, EcsOnUpdate, Transform, Camera);
        ECS_SYSTEM(m_world, MeshRenderSystem, EcsOnUpdate, Transform, MeshRenderer);

        ECS_SYSTEM(m_world, DebugRenderSystem, EcsOnUpdate, 0);
    }

    DISABLE_WARNING_POP

    // TEMPLATE SPECIALISATIONS

    template<> void World::emit_event<MouseScrolledEvent>(const MouseScrolledEvent& e)
    {
        ecs_run(m_world, ecs_id(CameraMovementSystem_OnMouseScrolled), 0.0f, &const_cast<MouseScrolledEvent&>(e));
    }

    // NOTE: Template specialisations are used here (instead of template instantiations) due to Flecs fundamentally
    // using macros to implement generic programming patterns. The template definitions are still provided for
    // reference.
    // NOTE: Also, template specialisations are put here early in this file because other code down below depends on it.

    // template<typename T> void       Entity::AddComponent()                       { ecs_add(m_world, m_entity, T); }
    // template<typename T> void       Entity::AddComponent(const T* component)     { ecs_set_ptr(m_world, m_entity, T, component); }
    // template<typename T> const T*   Entity::GetComponent()                       { return ecs_get(m_world, m_entity, T); }
    // template<typename T> T*         Entity::GetComponentMutable()                { return ecs_get_mut(m_world, m_entity, T); }
    // template<typename T> void       Entity::RemoveComponent()                    { ecs_remove(m_world, m_entity, T); }

    template<> void                 Entity::AddComponent<Transform>() { Transform c {}; ecs_set_ptr(m_world, m_entity, Transform, &c); }
    template<> void                 Entity::AddComponent<Transform>(const Transform* component)     { ecs_set_ptr(m_world, m_entity, Transform, component); }
    template<> void                 Entity::AddComponent<Transform>(const Transform& component)     { ecs_set_ptr(m_world, m_entity, Transform, &component); }
    template<> const Transform*     Entity::GetComponent<Transform>()                               { return ecs_get(m_world, m_entity, Transform); }
    template<> void                 Entity::RemoveComponent<Transform>()                            { ecs_remove(m_world, m_entity, Transform); }

    template<> void             Entity::AddComponent<Camera>() { Camera c {}; ecs_set_ptr(m_world, m_entity, Camera, &c); }
    template<> void             Entity::AddComponent<Camera>(const Camera* component)   { ecs_set_ptr(m_world, m_entity, Camera, component); }
    template<> void             Entity::AddComponent<Camera>(const Camera& component)   { ecs_set_ptr(m_world, m_entity, Camera, &component); }
    template<> const Camera*    Entity::GetComponent<Camera>()                          { return ecs_get(m_world, m_entity, Camera); }
    template<> void             Entity::RemoveComponent<Camera>()                       { ecs_remove(m_world, m_entity, Camera); }

    template<> void                 Entity::AddComponent<MeshRenderer>() { MeshRenderer c {}; ecs_set_ptr(m_world, m_entity, MeshRenderer, &c); }
    template<> void                 Entity::AddComponent<MeshRenderer>(const MeshRenderer* component)   { ecs_set_ptr(m_world, m_entity, MeshRenderer, component); }
    template<> void                 Entity::AddComponent<MeshRenderer>(const MeshRenderer& component)   { ecs_set_ptr(m_world, m_entity, MeshRenderer, &component); }
    template<> const MeshRenderer*  Entity::GetComponent<MeshRenderer>()                                { return ecs_get(m_world, m_entity, MeshRenderer); }
    template<> void                 Entity::RemoveComponent<MeshRenderer>()                             { ecs_remove(m_world, m_entity, MeshRenderer); }

    // END TEMPLATE SPECIALISATIONS

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

    Entity World::CreateEntity(std::string_view name)
    {
        std::string realname {};

        static unsigned counter {};
        if (name == "")
        {
            realname = "Entity" + std::to_string(counter);
            counter++;
        } else realname = name;

        Entity entity;
        entity.m_world = m_world;
        entity.m_name = realname;

        ecs_entity_desc_t entity_desc {};
        entity_desc.name = realname.c_str();
        entity.m_entity = ecs_entity_init(m_world, &entity_desc);

        return entity;
    }

    Entity World::EntityFromModelAsset(const Asset::Model* model_asset)
    { return EntityFromModelAsset(model_asset, model_asset->root()); }

    Entity World::EntityFromModelAsset(const Asset::Model* model_asset, const Asset::Model::Node* node)
    {
        Entity entity { CreateEntity(node->name) };

        glm::mat4 tm { node->transformation_matrix };
        Transform transform;
        glm::vec3 skew; // ignored
        glm::vec4 perspective; // ignored
        glm::decompose(tm, transform.scale, transform.orientation, transform.position, skew, perspective);

        entity.AddComponent<Transform>(transform);

        for (unsigned mesh_index : node->meshes_index)
        {
            // m_app_ctx->renderer.Get<Mesh>();
            MeshRenderer mesh_renderer;
        }

        for (const std::unique_ptr<Asset::Model::Node>& child : node->children)
        EntityFromModelAsset(model_asset, child.get());

        return entity;
    }

    void Entity::destruct() { ecs_delete(m_world, m_entity); }

    Entity Entity::child(std::string name)
    {
        Entity entity;
        ecs_entity_t e { ecs_lookup_child(m_world, m_entity, name.c_str()) };
        if (e)
        {
            entity.m_world = m_world;
            entity.m_entity = e;
            entity.m_name = name;
        } else
        {
            JAGE_LOG_ERROR("JAGE ECS error: No child with the name \"{}\" from parent \"{}\".", name, m_name);
            JAGE_MSG_ERROR("Returning invalid entity.");
        }

        return entity;
    }

    void CameraMovementSystem_OnMouseScrolled(ecs_iter_t* it)
    {
        Camera* camera { ecs_field(it, Camera, 0) };

        Camera& c { camera[0] };

        MouseScrolledEvent* e { static_cast<MouseScrolledEvent*>(it->param) };

        float scaled_delta { -e->offsetY() *10.0f * std::pow(c.fov / 90.0f, 2.0f) };
        c.fov = std::clamp(c.fov + scaled_delta, 1.0f, 150.0f);
    }

    void TransformSystem(ecs_iter_t* it)
    {
        Transform* transform { ecs_field(it, Transform, 0) };

        for (int i {}; i < it->count; i++)
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

    void MeshRenderSystem(ecs_iter_t* it)
    {
        World::ApplicationContext* app_ctx { static_cast<World::ApplicationContext*>(ecs_get_ctx(it->world)) };
        Renderer* renderer { app_ctx->renderer };

        Transform* transform { ecs_field(it, Transform, 0) };
        MeshRenderer* mesh_renderer { ecs_field(it, MeshRenderer, 1) };

        for (int i {}; i < it->count; i++)
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

    void DebugRenderSystem(ecs_iter_t* it)
    {
        World::ApplicationContext* app_ctx { static_cast<World::ApplicationContext*>(ecs_get_ctx(it->world)) };
        DebugRenderer* debug_renderer { app_ctx->debug_renderer };

        debug_renderer->RenderBaseAxes();
        debug_renderer->RenderGridLines(10, 1.0f);
    }

    void CameraMovementSystem(ecs_iter_t* it)
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

    void CameraRenderSystem(ecs_iter_t* it)
    {
        World::ApplicationContext* app_ctx { static_cast<World::ApplicationContext*>(ecs_get_ctx(it->world)) };
        Window* window { app_ctx->window };
        Renderer* renderer { app_ctx->renderer };
        DebugRenderer* debug_renderer { app_ctx->debug_renderer };

        Transform* transform { ecs_field(it, Transform, 0) };
        Camera* camera { ecs_field(it, Camera, 1) };

        Transform& t { transform[0] };
        Camera& c { camera[0] };

        c.view_matrix = glm::lookAtLH(t.position, t.position + t.forward, t.up);
        c.projection_matrix = glm::infinitePerspectiveLH(glm::radians(c.fov), window->aspect_ratio(), 0.01f);

        renderer->set_vp(c.view_matrix, c.projection_matrix);
        debug_renderer->set_vp(c.view_matrix, c.projection_matrix);
   }
}