#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"
#include "JAGE/math.h"

#include <flecs.h>

namespace JAGE
{
    struct JAGE_API Transform
    {
        glm::vec3 position;
        glm::quat orientation;
        glm::vec3 scale;

        // each data below has to be modified via ECS system based on the 3 data above

        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 forward;

        glm::vec3 euler_angles;
        glm::mat4 transformation_matrix;
    };

    struct JAGE_API Camera
    { 
        glm::mat4 view_matrix;
        glm::mat4 projection_matrix;

        float move_speed;
        float zoom_speed;
        float sensitivity;

        float pitch;
        float yaw;
        float fov;
    };

    struct JAGE_API MeshRenderer
    {
        Mesh* mesh;
        Material* material;
    };

    JAGE_API void CameraSystem_Initialise(ecs_iter_t* it);
    JAGE_API void RenderSystem_Initialise(ecs_iter_t* it);

    JAGE_API void TransformSystem(ecs_iter_t* it);
    JAGE_API void CameraSystem(ecs_iter_t* it);
    JAGE_API void RenderSystem(ecs_iter_t* it);

    struct JAGE_API ApplicationContext
    {
        Window* window;
        unsigned value;
    };

    class JAGE_API Entity
    {
    public:
        Entity(const World& world, std::string_view name = "");
        Entity();
        ~Entity();

        template<typename T> void AddComponent();
        template<typename T> void AddComponent(const T* component);

        template<typename T> const T& GetComponent();
        template<typename T> T& GetComponentMutable();

        template<typename T> void RemoveComponent();
    private:
        ecs_world_t* m_ecs_world;
        std::string m_name;
        ecs_entity_t m_entity;
    };

    class JAGE_API World
    {
    public:
        World(ApplicationContext app_ctx);
        World();
        ~World();

        /**
         * ECS worlds are not meant to be copied, only moved from one another.
         */

        World(const World& other) = delete;
        World& operator=(const World& other) = delete;
        World(World&& other) noexcept;
        World& operator=(World&& other) noexcept;

        Entity entity();

        void progress(float deltatime);
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

        ApplicationContext m_app_ctx;

        void release();
    };
}