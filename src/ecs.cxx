#include "JAGE/ecs.h"

namespace JAGE
{
    World::World() : m_world {}
    {
        // m_world.component<Position>();
        // m_world.component<Rotation>();
        // m_world.component<Scale>();
    }

    Entity World::CreateEntity(std::string_view name)
    {
        return Entity{ this, name };
    }

    Entity::Entity(World* world, std::string_view name)
    : m_name { name }
    , m_world { world->world() }
    , m_entity { m_world->entity(name.data()) }
    {
        m_entity.add<Position>();
        m_entity.add<Rotation>();
        m_entity.add<Scale>();
    }

    Entity::~Entity()
    {
        m_entity.destruct();
    }
}