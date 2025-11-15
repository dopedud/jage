#include "ecs.h"

namespace JAGE
{
    namespace ECS
    {
        std::unique_ptr<World> World::Create()
        {
            return std::make_unique<FlecsWorld>();
        }

        FlecsWorld::FlecsWorld() : m_world {} {}

        FlecsWorld::~FlecsWorld()
        {

        }

        std::unique_ptr<Entity> FlecsWorld::CreateEntity(World* world, std::string_view name)
        {
            std::unique_ptr<Entity> entity { Entity::Create(this, name) };
            m_world.entity();
        }

        std::unique_ptr<Entity> Entity::Create(World* world, std::string_view name)
        {
            return std::make_unique<FlecsEntity>(world, name);
        }

        FlecsEntity::FlecsEntity(std::string_view name) : m_name { name }
        {

        }
    }
}