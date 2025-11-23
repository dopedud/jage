#pragma once

#include "JAGE/ecs_old.h"

#include <flecs.h>

namespace JAGE
{
    namespace ECS
    {
        class FlecsWorld : public World
        {
        public:
            FlecsWorld();

            void* world() override { return &m_world; }

            std::unique_ptr<Entity> CreateEntity(std::string_view name = "") override;
        private:
            flecs::world m_world;
        };

        class FlecsEntity : public Entity
        {
        public:
            FlecsEntity(World* world, std::string_view name = "");
            ~FlecsEntity();

            void* entity() override { return &m_entity; }

            void AddComponent_Position(const Position& component) override;
            void AddComponent_Rotation(const Rotation& component) override;
            void AddComponent_Scale(const Scale& component) override;

            void RemoveComponent_Position() override;
            void RemoveComponent_Rotation() override;
            void RemoveComponent_Scale() override;

            const Position& GetComponent_Position() override;
            const Rotation& GetComponent_Rotation() override;
            const Scale& GetComponent_Scale() override;
        private:
            flecs::world* m_world;
            flecs::entity m_entity;
        };
    }
}