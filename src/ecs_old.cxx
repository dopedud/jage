#include "ecs_old.h"

namespace JAGE
{
    namespace ECS
    {
        std::unique_ptr<World> World::Create()
        {
            return std::make_unique<FlecsWorld>();
        }

        FlecsWorld::FlecsWorld() : m_world {} {}

        std::unique_ptr<Entity> FlecsWorld::CreateEntity(std::string_view name)
        {
            return Entity::Create(this, name);
        }

        std::unique_ptr<Entity> Entity::Create(World* world, std::string_view name)
        {
            return std::make_unique<FlecsEntity>(world, name);
        }

        FlecsEntity::FlecsEntity(World* world, std::string_view name)
        : Entity{ name }
        , m_world { static_cast<flecs::world*>(world->world()) }
        , m_entity { m_world->entity(name.data()) }
        {
            m_entity.add<Position>();
            m_entity.add<Rotation>();
            m_entity.add<Scale>();
        }

        FlecsEntity::~FlecsEntity() { m_entity.destruct(); }

        void FlecsEntity::AddComponent_Position(const Position& component) { m_entity.set<Position>(component); }
        void FlecsEntity::AddComponent_Rotation(const Rotation& component) { m_entity.set<Rotation>(component); }
        void FlecsEntity::AddComponent_Scale(const Scale& component) { m_entity.set<Scale>(component); }

        void FlecsEntity::RemoveComponent_Position() { m_entity.remove<Position>(); }
        void FlecsEntity::RemoveComponent_Rotation() { m_entity.remove<Rotation>(); }
        void FlecsEntity::RemoveComponent_Scale() { m_entity.remove<Scale>(); }

        const Position& FlecsEntity::GetComponent_Position() { return m_entity.get<Position>(); }
        const Rotation& FlecsEntity::GetComponent_Rotation() { return m_entity.get<Rotation>(); }
        const Scale& FlecsEntity::GetComponent_Scale() { return m_entity.get<Scale>(); }
    }
}