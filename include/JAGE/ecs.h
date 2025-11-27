#pragma once

#include "JAGE/core.h"

#include "log.h"

#include <flecs.h>

namespace JAGE
{
    enum class ComponentType : uint8_t
    {
        Position, Rotation, Scale,
        Camera,
    };

    #define COMPONENT_TYPE(type) \
        static ComponentType static_type() { return ComponentType::type; } \
        ComponentType component_type() const { return static_type(); }

    struct Position { COMPONENT_TYPE(Position); float x {}, y {}, z {}; };
    struct Rotation { COMPONENT_TYPE(Rotation); float x {}, y {}, z {}; };
    struct Scale    { COMPONENT_TYPE(Scale); float x { 1.0f }, y { 1.0f }, z { 1.0f }; };

    struct Camera { COMPONENT_TYPE(Camera); };

    // forward declare Entity and System class to be used by World class
    class JAGE_API World;

    using SystemFunction = std::function<void(flecs::iter&)>;

    class JAGE_API Entity
    {
    private:
        flecs::world* m_world;
        flecs::entity m_entity;
    public:
        Entity(World* world, std::string_view name = "");
        Entity() = default;
        ~Entity();

        flecs::entity* entity();

        template<typename T> void AddComponent() { m_entity.add<T>(); }

        // not sure if setting an existing component would overwrite it, might come back here if there's a bug
        template<typename T> void AddComponent(const T& component) { m_entity.set<T>(component); }

        template<typename T> void RemoveComponent()
        { 
            if
            (
                T::static_type() == ComponentType::Position ||
                T::static_type() == ComponentType::Rotation ||
                T::static_type() == ComponentType::Scale
            )
            {
                JAGE_MSG_ERROR("JAGE error: cannot remove transform components.");
                return;
            }

            m_entity.remove<T>();
        }

        template<typename T> const T* GetComponent()
        {
            if (const T* result { m_entity.try_get<T>() })
            {
                JAGE_LOG_ERROR("JAGE error: unknown component type - {}, returning nullptr.", typeid(T).name());
                return nullptr;
            }
            else return result;
        }
    };

    template<typename... Components>
    class JAGE_API System
    {
    private:
        flecs::world* m_world;
        flecs::system m_system;
    public:
        System(World* world, SystemFunction func, std::string_view name = "")
        : m_world { world->world() }
        , m_system { m_world->system<Components...>(name.data()).run(func) }
        {}

        System() = default;

        ~System()
        {
            m_system.destruct();
        }

        flecs::system* system() { return &m_system; }
    };

    class JAGE_API World
    {
    private:
        flecs::world m_world;
    public:
        World();

        flecs::world* world();

        void progress(double deltatime);

        Entity CreateEntity(std::string_view name = "");

        template<typename... Components>
        System<Components...> CreateSystem(SystemFunction func, std::string_view name = "")
        {
            return System<Components...>{ this, name, func };
        }
    };
}