#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    namespace ECS
    {
        struct Position
        {
            float x, y, z;
        };

        class JAGE_API Entity;

        class JAGE_API World
        {
        public:
            static std::unique_ptr<World> Create();
            virtual ~World() = default;

            virtual void* world() = 0;

            virtual std::unique_ptr<Entity> CreateEntity(World* world, std::string_view name = "") = 0;
            virtual void DestroyEntity(Entity* entity) = 0;
            virtual void DestroyEntity(std::string_view name) = 0;
        };

        class JAGE_API Entity
        {
        public:
            static std::unique_ptr<Entity> Create(World* world, std::string_view name = "");
            virtual ~Entity() = default;

            template<typename T>
            void AddComponent(const T& component) { AddComponent_Impl(typeid(T), &component); }

            template<typename T>
            T* GetComponent() { return static_cast<T*>(GetComponent_Impl(typeid(T))); }

            std::string_view name() const { return m_name; }
        protected:
            std::string m_name;

            virtual void AddComponent_Impl(std::type_index type, const void* component) = 0;
            virtual void* GetComponent_Impl(std::type_index type) = 0;
        };
    }
}