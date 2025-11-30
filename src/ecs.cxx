#include "JAGE/ecs.h"

#include "log.h"

namespace JAGE
{
    void CameraMove(flecs::iter& it, size_t index, Camera& camera, Transform& transform)
    {
        JAGE_LOG_DEBUG("{}", it.delta_time());

        glm::vec3 move_vector {};

        if (JAGE_IS_KEY_PRESSED(JAGE_KEY_D)) move_vector.x += 1.0f;
        if (JAGE_IS_KEY_PRESSED(JAGE_KEY_A)) move_vector.x -= 1.0f;
        if (JAGE_IS_KEY_PRESSED(JAGE_KEY_SPACE)) move_vector.y += 1.0f;
        if (JAGE_IS_KEY_PRESSED(JAGE_KEY_LEFT_CONTROL)) move_vector.y -= 1.0f;
        if (JAGE_IS_KEY_PRESSED(JAGE_KEY_W)) move_vector.z += 1.0f;
        if (JAGE_IS_KEY_PRESSED(JAGE_KEY_S)) move_vector.z -= 1.0f;

        JAGE_LOG_DEBUG("{}, {}, {}", move_vector.x, move_vector.y, move_vector.z);
    }

    // World::World() : m_world {}
    // {
    //     // m_world.component<Position>();
    //     // m_world.component<Rotation>();
    //     // m_world.component<Scale>();
    // }

    // flecs::world* World::world()
    // {
    //     return &m_world;
    // }

    // void World::progress(double deltatime)
    // {
    //     m_world.progress(deltatime / Time::SECONDS_TO_MILLI);
    // }

    // Entity World::CreateEntity(std::string_view name)
    // {
    //     return Entity{ this, name };
    // }

    // Entity::Entity(World* world, std::string_view name)
    // : m_world { world->world() }
    // , m_entity { m_world->entity(name.data()) }
    // {
    //     m_entity.add<Position>();
    //     m_entity.add<Rotation>();
    //     m_entity.add<Scale>();
    // }

    // Entity::~Entity()
    // {
    //     m_entity.destruct();
    // }

    // flecs::entity* Entity::entity()
    // {
    //     return &m_entity;
    // }
}