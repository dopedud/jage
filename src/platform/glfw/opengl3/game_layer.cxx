#include "JAGE/layers.h"

#include "platform/input.h"
#include "log.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace JAGE
{
    GameLayer::GameLayer(Window* window) : Layer("Game Layer") {}

    void GameLayer::OnAttach() {}
    void GameLayer::OnDetach() {}

    void GameLayer::OnRender() {}

    void GameLayer::OnEvent(const Event& e)
    {
        JAGE_MSG_DEBUG("Game Layer | " + std::string{ e.to_string() });
    }
}