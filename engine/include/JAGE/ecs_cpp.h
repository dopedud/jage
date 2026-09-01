#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"
#include "JAGE/math.h"
#include "JAGE/assets.h"

#include <flecs.h>

namespace JAGE
{
    struct JAGE_API Transform
    {
        glm::vec3 position {};
        glm::quat orientation { 1.0f, 0.0f, 0.0f, 0.0f };
        glm::vec3 scale { 1.0f };

        // each data below has to be modified via ECS system based on the 3 data above

        glm::vec3 right     { glm::normalize(orientation * glm::vec3{ 1.0f, 0.0f, 0.0f }) };
        glm::vec3 up        { glm::normalize(orientation * glm::vec3{ 0.0f, 1.0f, 0.0f }) };
        glm::vec3 forward   { glm::normalize(orientation * glm::vec3{ 0.0f, 0.0f, 1.0f }) };

        glm::vec3 euler_angles {};
        glm::mat4 transformation_matrix { 1.0f };
    };

    struct JAGE_API Camera
    { 
        glm::mat4 view_matrix { 1.0f };
        glm::mat4 projection_matrix { 1.0f };

        float move_speed { 1.01f };
        float zoom_speed { 100.0f };
        float sensitivity { 8.5f * 0.01f };

        float pitch {};
        float yaw {};
        float fov { 90.0f };
    };

    struct JAGE_API MeshRenderer
    {
        Mesh* mesh {};
        Material* material {};
    };

    void CameraMovementSystem_OnMouseScrolled(flecs::iter& it);

    void TransformSystem(flecs::iter& it);
    void CameraMovementSystem(flecs::iter& it);
    void CameraRenderSystem(flecs::iter& it);
    void MeshRenderSystem(flecs::iter& it);

    void DebugRenderSystem(flecs::iter& it);

    class JAGE_API World
    {
    public:
        struct JAGE_API ApplicationContext
        {
            Window* window;
            Renderer* renderer;
            DebugRenderer* debug_renderer;
        };

        World(ApplicationContext app_ctx);
        World();
        ~World() = default;

        /**
         * ECS worlds are not meant to be copied, only moved from one another.
         * 
         * Cloning will be implemented in the future for duplicating ECS worlds.
         * 
         * @{
         */
        World(const World&) = delete;
        World& operator=(const World&) = delete;
        World(World&& other) noexcept;
        World& operator=(World&& other) noexcept;
        /** @} */

        const flecs::world& world() const;

        void progress(float deltatime);

        /**
         * @fn emit_event
         * 
         * @brief Function to emit events for ECS entities to react.
         * 
         * @tparam TEventData The event data type.
         * @param event_data The event data to supply when emitting the event.
         */
        template<typename TEventData>
        void emit_event(const TEventData& event_data);
    private:
        flecs::world m_world;
        flecs::entity eventemitter;

        std::unique_ptr<ApplicationContext> m_app_ctx;
    };

    class JAGE_API Entity
    {
    public:
        static Entity EntityFromModelAsset(const ModelAsset* model_asset);
        static Entity EntityFromModelAsset(const ModelAsset* model_asset, const ModelNode* node);

        Entity(const World& world, std::string_view name);
        Entity();
        ~Entity() = default;

        template<typename T> void AddComponent();
        template<typename T> void AddComponent(const T& component);
        template<typename T> const T& GetComponent();
        template<typename T> void RemoveComponent();

        Entity child(std::string name);
    public:
        flecs::entity m_entity;
    };
}