#include "JAGE/layers/imgui_layer.h"
#include "log.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace JAGE
{
    ImguiLayer::ImguiLayer(Window* window) : Layer("IMGUI Layer"), window { window } {}

    void ImguiLayer::OnAttach()
    {
        JAGE_MSG_TRACE("Attaching IMGUI layer to layer stack.");

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        io.IniFilename = nullptr;
        // io.DisplaySize = ImVec2{ window->width(), window->height() };


        ImGui::StyleColorsDark();

        bool imgui_glfw_success { ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(window->handle()), false) };
        bool imgui_opengl3_success { ImGui_ImplOpenGL3_Init("#version 460") };

        JAGE_ASSERT(imgui_glfw_success, "IMGUI failed to load with GLFW backend.")
        JAGE_ASSERT(imgui_opengl3_success, "IMGUI failed to load OpenGL loader.")

        JAGE_MSG_TRACE("Attached IMGUI layer to layer stack.");
    }

    void ImguiLayer::OnDetach()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImguiLayer::OnRender()
    {
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImguiLayer::OnEvent(const Event& e)
    {
        EventDispatcher dispatcher { e };
        dispatcher.dispatch<WindowFocusEvent>([this](const WindowFocusEvent& e) -> bool { return OnWindowFocusEvent(e); });
        dispatcher.dispatch<KeyEvent>([this](const KeyEvent& e) -> bool { return OnKeyEvent(e); });
        dispatcher.dispatch<CharEvent>([this](const CharEvent& e) -> bool { return OnCharEvent(e); });
        dispatcher.dispatch<MouseButtonEvent>([this](const MouseButtonEvent& e) -> bool { return OnMouseButtonEvent(e); });
        dispatcher.dispatch<MouseEnterEvent>([this](const MouseEnterEvent& e) -> bool { return OnMouseEnterEvent(e); });
        dispatcher.dispatch<MouseMovedEvent>([this](const MouseMovedEvent& e) -> bool { return OnMouseMovedEvent(e); });
        dispatcher.dispatch<MouseScrolledEvent>([this](const MouseScrolledEvent& e) -> bool { return OnMouseScrolledEvent(e); });
    }

    bool ImguiLayer::OnWindowFocusEvent(const WindowFocusEvent& e)
    {
        ImGui_ImplGlfw_WindowFocusCallback(static_cast<GLFWwindow*>(window->handle()), e.focused());        // Since 1.84
        return true;
    }

    bool ImguiLayer::OnKeyEvent(const KeyEvent& e)
    {
        ImGui_ImplGlfw_KeyCallback(static_cast<GLFWwindow*>(window->handle()), e.key(), e.scancode(), e.action(), e.mods());
        return true;
    }

    bool ImguiLayer::OnCharEvent(const CharEvent& e)
    {
        ImGui_ImplGlfw_CharCallback(static_cast<GLFWwindow*>(window->handle()), e.codepoint());
        return true;
    }
    
    bool ImguiLayer::OnMouseButtonEvent(const MouseButtonEvent& e)
    {
        ImGui_ImplGlfw_MouseButtonCallback(static_cast<GLFWwindow*>(window->handle()), e.button(), e.action(), e.mods());
        return true;
    }
    
    bool ImguiLayer::OnMouseEnterEvent(const MouseEnterEvent& e)
    {
        ImGui_ImplGlfw_CursorEnterCallback(static_cast<GLFWwindow*>(window->handle()), e.entered());
        return true;
    }
    
    bool ImguiLayer::OnMouseMovedEvent(const MouseMovedEvent& e)
    {
        ImGui_ImplGlfw_CursorPosCallback(static_cast<GLFWwindow*>(window->handle()), e.mouseX(), e.mouseY());
        return true;
    }
    
    bool ImguiLayer::OnMouseScrolledEvent(const MouseScrolledEvent& e)
    {
        ImGui_ImplGlfw_ScrollCallback(static_cast<GLFWwindow*>(window->handle()), e.offsetX(), e.offsetY());
        return true;
    }
}