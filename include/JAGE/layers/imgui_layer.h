#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API ImguiLayer final : public Layer
    {
    public:
        ImguiLayer(Window* window);

        void OnAttach() override;
        void OnDetach() override;

        void OnRender() override;
    private:
        Window* window;

        bool OnMouseButtonEvent(const MouseButtonEvent& e) override;
        bool OnMouseMovedEvent(const MouseMovedEvent& e) override;
    };
}