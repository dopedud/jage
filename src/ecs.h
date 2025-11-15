#pragma once

#include "JAGE/ecs.h"

#include <flecs.h>

namespace JAGE
{
    namespace ECS
    {
        class FlecsWorld : public World
        {
        public:
            FlecsWorld();
            ~FlecsWorld();

            void* world() override { return &m_world; }

            std::unique_ptr<Entity> CreateEntity(World* world, std::string_view name = "") override;
            void DestroyEntity(Entity* entity) override;
            void DestroyEntity(std::string_view name) override;
        private:
            flecs::world m_world;
        };

        class FlecsEntity : public Entity
        {
        public:
            FlecsEntity(World* world, std::string_view name = "");
            ~FlecsEntity();
        protected:
            void AddComponent_Impl(std::type_index type, const void* component) override;
            void* GetComponent_Impl(std::type_index type) override;
        private:
        flecs::world* m_world;
        flecs::entity m_entity;
        };
    }
}