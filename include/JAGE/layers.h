#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    class JAGE_API GameLayer final : public Layer
    {
    public:
        GameLayer(Window* window);

        void OnAttach() override;
        void OnDetach() override;

        void OnRender() override;
        
        void OnEvent(const Event& e) override;
    };

    class JAGE_API ImguiLayer final : public Layer
    {
    public:
        ImguiLayer(Window* window);

        void OnAttach() override;
        void OnDetach() override;

        void OnRender() override;
        
        void OnEvent(const Event& e) override;
    private:
        bool OnWindowFocusEvent(const WindowFocusEvent& e);
        bool OnKeyEvent(const KeyEvent& e);
        bool OnCharEvent(const CharEvent& e);
        bool OnMouseButtonEvent(const MouseButtonEvent& e);
        bool OnMouseEnterEvent(const MouseEnterEvent& e);
        bool OnMouseMovedEvent(const MouseMovedEvent& e);
        bool OnMouseScrolledEvent(const MouseScrolledEvent& e);
    };
}
