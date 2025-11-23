#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    namespace ECS
    {
        struct Position { float x, y, z; };
        struct Rotation { float x, y, z; };
        struct Scale    { float x { 1.0f }, y { 1.0f }, z { 1.0f }; };

        // forward declare Entity class to be used by World class
        class JAGE_API Entity;

        class JAGE_API World
        {
        public:
            static std::unique_ptr<World> Create();
            virtual ~World() = default;

            virtual void* world() = 0;

            virtual std::unique_ptr<Entity> CreateEntity(std::string_view name = "") = 0;
        };

        class JAGE_API Entity
        {
        protected:
            std::string m_name;
        public:
            static std::unique_ptr<Entity> Create(World* world, std::string_view name = "");
            Entity(std::string_view name = "") : m_name { name } {}
            virtual ~Entity() = default;

            virtual void* entity() = 0;

            std::string_view name() const { return m_name; }

            // add some more components here
            
            virtual void AddComponent_Position(const Position& component) = 0;
            virtual void AddComponent_Rotation(const Rotation& component) = 0;
            virtual void AddComponent_Scale(const Scale& component) = 0;

            virtual void RemoveComponent_Position() = 0;
            virtual void RemoveComponent_Rotation() = 0;
            virtual void RemoveComponent_Scale() = 0;

            virtual const Position& GetComponent_Position() = 0;
            virtual const Rotation& GetComponent_Rotation() = 0;
            virtual const Scale& GetComponent_Scale() = 0;
        };
    }
}