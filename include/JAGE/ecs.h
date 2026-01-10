#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"
#include "JAGE/math.h"

#include <flecs.h>

namespace JAGE
{
    struct Transform
    {
        glm::vec3 position;
        glm::quat orientation; // angles in degrees
        glm::vec3 scale;

        glm::vec3 right() const;
        glm::vec3 up() const;
        glm::vec3 forward() const;

        glm::mat4 transformation_matrix() const;

        void rotateGlobalX(float degrees);
        void rotateGlobalY(float degrees);
        void rotateGlobalZ(float degrees);
        void rotateLocalX(float degrees);
        void rotateLocalY(float degrees);
        void rotateLocalZ(float degrees);
    };

    struct Camera
    { 
        glm::mat4 view_matrix;

        float speed;
        float sensitivity;

        float fov;
    };

    JAGE_API void TransformSystem(ecs_iter_t* it);

    JAGE_API void CameraSystem_Initialise(ecs_iter_t* it);
    JAGE_API void CameraSystem(ecs_iter_t* it);
    JAGE_API void RenderSystem_Initialise(ecs_iter_t* it);
    JAGE_API void RenderSystem(ecs_iter_t* it);

    // JAGE_API void RendererSystem_Initialise(ecs_iter_it* it);
    // JAGE_API void RendererSystem(ecs_iter_it* it);

    class JAGE_API World
    {
    public:
        World();
        ~World();

        ecs_world_t* world() const;

        void progress(float deltatime);
    private:
        ecs_world_t* m_world; 
    };

    class JAGE_API Entity
    {
    public:
        Entity(World* world, std::string_view name = "");
        ~Entity();

        template<typename T> void AddComponent();
        template<typename T> void AddComponent(const T* component);

        template<typename T> const T* GetComponent();
        template<typename T> T* GetComponentMutable();

        template<typename T> void RemoveComponent();
    private:
        std::string m_name;
        ecs_world_t* m_world;
        ecs_entity_t m_entity;
    };
}