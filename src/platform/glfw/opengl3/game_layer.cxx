#include "JAGE/layers.h"

#include "platform/input.h"
#include "log.h"

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer(window, "Game Layer") {}

    void GameLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching Game layer to layer stack.");



        JAGE_MSG_TRACE("Attaching IMGUI layer to layer stack.");
    }
    void GameLayer::OnDetach()
    {
        JAGE_MSG_TRACE("Detaching IMGUI layer to layer stack.");



        JAGE_MSG_TRACE("Detached IMGUI layer to layer stack.");
    }

    void GameLayer::OnRender()
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };


    }

    void GameLayer::OnEvent(const Event& e)
    {
        // JAGE_MSG_DEBUG("Game Layer | " + std::string{ e.to_string() });
    }
}
