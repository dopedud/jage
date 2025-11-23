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

    // forward declare Entity class to be used by World class
    class JAGE_API Entity;

    class JAGE_API World
    {
    private:
        flecs::world m_world;
    public:
        World();

        flecs::world* world() { return &m_world; }

        Entity CreateEntity(std::string_view name = "");
    };

    class JAGE_API Entity
    {
    private:
        std::string m_name;

        flecs::world* m_world;
        flecs::entity m_entity;
    public:
        Entity(World* world, std::string_view name = "");
        ~Entity();

        flecs::entity* entity() { return &m_entity; }

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

    //class JAGE_API System
    //{

    //};
}