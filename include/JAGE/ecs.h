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
        glm::vec3 rotation; // angles in degrees
        glm::vec3 scale;

        glm::mat4 rotation_matrix();
    };

    struct Camera
    { 
        glm::mat4 view_matrix;

        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 front;

        float speed;
        float sensitivity;
    };

    JAGE_API void CameraSystem_Initialise(ecs_iter_t* it);
    JAGE_API void CameraSystem(ecs_iter_t* it);

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

        template<typename T> void RemoveComponent();
    private:
        std::string m_name;
        ecs_world_t* m_world;
        ecs_entity_t m_entity;
    };
}