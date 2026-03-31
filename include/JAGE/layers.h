#pragma once

#include "JAGE/ecs.h"

namespace JAGE
{
    class JAGE_API GameLayer final : public Layer
    {
    public:
        GameLayer(Window* window);

        void OnAttach() override;
        void OnDetach() override;

        void OnUpdate() override;

        void OnEvent(const Event& e) override;
    private:
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<DebugRenderer> debug_renderer;

        std::unique_ptr<Shader> shader;
        Material mat1;
        Material mat2;
        std::unique_ptr<Texture> texture;
        std::unique_ptr<Mesh> mesh1;
        std::unique_ptr<Mesh> mesh2;

        World world;
        Entity camera;
        Entity object1;
        Entity object2;
    };

    class JAGE_API ImguiLayer final : public Layer
    {
    public:
        ImguiLayer(Window* window);

        void OnAttach() override;
        void OnDetach() override;

        void OnUpdate() override;

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
