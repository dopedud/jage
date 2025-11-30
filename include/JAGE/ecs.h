#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"
#include "JAGE/math.h"

#include <flecs.h>

namespace JAGE
{
    JAGE_API inline flecs::world& World()
    {
        static flecs::world world;
        return world;
    }

    enum class ComponentType : uint8_t
    {
        Transform,
        Camera,
    };

    #define COMPONENT_TYPE(type) \
        static ComponentType static_type() { return ComponentType::type; } \
        ComponentType component_type() const { return static_type(); }

    struct Transform
    {
        COMPONENT_TYPE(Transform);
        glm::vec3 position {};
        glm::vec3 rotation {};
        glm::vec3 scale { 1.0f, 1.0f, 1.0f };
    };

    struct Camera { COMPONENT_TYPE(Camera); };

    JAGE_API void CameraMove(flecs::iter& it, size_t index, Camera& camera, Transform& transform);

    // NOTE: THIS LIBRARY IS NOT IN USE FOR NOW
    // ONLY IN USE FOR INCLUSION OF FLECS

    // // forward declare Entity and System class to be used by World class
    // class JAGE_API World;

    // using SystemFunction = std::function<void(flecs::iter&)>;

    // class JAGE_API Entity
    // {
    // private:
    //     flecs::world* m_world;
    //     flecs::entity m_entity;
    // public:
    //     Entity(World* world, std::string_view name = "");
    //     Entity() = default;
    //     ~Entity();

    //     flecs::entity* entity();

    //     template<typename T> void AddComponent() { m_entity.add<T>(); }

    //     // not sure if setting an existing component would overwrite it, might come back here if there's a bug
    //     template<typename T> void AddComponent(const T& component) { m_entity.set<T>(component); }

    //     template<typename T> void RemoveComponent()
    //     { 
    //         if
    //         (
    //             T::static_type() == ComponentType::Position ||
    //             T::static_type() == ComponentType::Rotation ||
    //             T::static_type() == ComponentType::Scale
    //         )
    //         {
    //             return;
    //         }

    //         m_entity.remove<T>();
    //     }

    //     template<typename T> const T* GetComponent()
    //     {
    //         if (const T* result { m_entity.try_get<T>() }) { return nullptr; }
    //         else return result;
    //     }
    // };

    // template<typename... Components>
    // class JAGE_API System
    // {
    // private:
    //     flecs::world* m_world;
    //     flecs::system m_system;
    // public:
    //     System(World* world, SystemFunction func, std::string_view name = "")
    //     : m_world { world->world() }
    //     , m_system { m_world->system<Components...>(name.data()).run(func) }
    //     {}

    //     System() = default;

    //     ~System()
    //     {
    //         m_system.destruct();
    //     }

    //     flecs::system* system() { return &m_system; }
    // };

    // class JAGE_API World
    // {
    // private:
    //     flecs::world m_world;
    // public:
    //     World();

    //     flecs::world* world();

    //     void progress(double deltatime);

    //     Entity CreateEntity(std::string_view name = "");

    //     template<typename... Components>
    //     System<Components...> CreateSystem(SystemFunction func, std::string_view name = "")
    //     {
    //         return System<Components...>{ this, name, func };
    //     }
    // };
}