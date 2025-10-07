#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API ImguiLayer : public Layer
    {
    public:
        ImguiLayer(Window* window);

        void OnAttach() override;
        void OnDetach() override;

        void OnRender() override;

        void OnEvent(const Event& e) override;
    private:
        Window* window;
    };
}