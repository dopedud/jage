#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"
#include "JAGE/math.h"

#include <flecs.h>

namespace JAGE
{
    struct JAGE_API Transform
    {
        glm::vec3 position {};
        glm::quat orientation { 1.0f, 0.0f, 0.0f, 0.0f };
        glm::vec3 scale { 1.0f };

        // each data below has to be modified via ECS system based on the 3 data above

        glm::vec3 right     { glm::normalize(orientation * glm::vec3{ 1.0f, 0.0f, 0.0f }) };
        glm::vec3 up        { glm::normalize(orientation * glm::vec3{ 0.0f, 1.0f, 0.0f }) };
        glm::vec3 forward   { glm::normalize(orientation * glm::vec3{ 0.0f, 0.0f, 1.0f }) };

        glm::vec3 euler_angles {};
        glm::mat4 transformation_matrix { 1.0f };
    };

    struct JAGE_API Camera
    { 
        glm::mat4 view_matrix { 1.0f };
        glm::mat4 projection_matrix { 1.0f };

        float move_speed { 0.01f };
        float zoom_speed { 0.1f };
        float sensitivity { 8.5f * 0.01f };

        float pitch {};
        float yaw {};
        float fov { 90.0f };
    };

    struct JAGE_API MeshRenderer
    {
        Mesh* mesh {};
        Material* material {};
    };

    void CameraMovementSystem_OnMouseScrolled(ecs_iter_t* it);

    void TransformSystem(ecs_iter_t* it);
    void CameraMovementSystem(ecs_iter_t* it);
    void CameraRenderSystem(ecs_iter_t* it);
    void MeshRenderSystem(ecs_iter_t* it);

    class JAGE_API World
    {
    public:
        struct JAGE_API ApplicationContext
        {
            Window* window;
            Renderer* renderer;
        };

        World(ApplicationContext app_ctx);
        World();
        ~World();

        /**
         * ECS worlds are not meant to be copied, only moved from one another.
         * 
         * Cloning will be implemented in the future for duplicating ECS worlds.
         * 
         * @{
         */

        World(const World& other) = delete;
        World& operator=(const World& other) = delete;
        World(World&& other) noexcept;
        World& operator=(World&& other) noexcept;

        /** @} */
        
        ecs_world_t* world() const;

        void progress(float deltatime);

        /**
         * @fn emit_event
         * 
         * @brief Function to emit events for ECS entities to react.
         * 
         * @tparam TEventData The event data type.
         * @param event_data The event data to supply when emitting the event.
         */
        template<typename TEventData>
        void emit_event(const TEventData& event_data);
    private:
        /**
         * @var m_world
         * 
         * @brief The internal data structure for an ECS world.
         * 
         * This variable is a raw pointer to the underlying data structure of an ECS world instead of a
         * `std::unique_ptr<ecs_world_t>` to easily interface with the C functions that mutate the ECS world
         * (otherwise every function call has `m_world.get()`).
         */
        ecs_world_t* m_world;

        std::unique_ptr<ApplicationContext> m_app_ctx;

        void release();
    };

    class JAGE_API Entity
    {
    public:
        Entity(const World& world, std::string_view name);
        Entity();
        ~Entity();

        /**
         * ECS entities are not meant to be copied, only moved from one another.
         * 
         * Cloning will be implemented in the future for duplicating ECS entities.
         */

        Entity(const Entity& other) = delete;
        Entity& operator=(const Entity& other) = delete;
        Entity(Entity&& other) noexcept;
        Entity& operator=(Entity&& other) noexcept;

        template<typename T> void AddComponent();
        template<typename T> void AddComponent(const T* component);

        template<typename T> const T* GetComponent();

        template<typename T> void RemoveComponent();
    public:
        ecs_world_t* m_world;
        std::string m_name;
        ecs_entity_t m_entity;

        void release();
    };
}