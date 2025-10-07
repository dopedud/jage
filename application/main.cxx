#include "JAGE/core.h"
#include "JAGE/layers/imgui_layer.h"

using namespace JAGE;

int main(int argc, char** argv)
{
    JAGE::Init(argc, argv);

    bool running { true };

    APP_MSG_INFO("Creating a window.");
    std::unique_ptr<Window> window { std::make_unique<Window>() };

    APP_MSG_INFO("Creating a layer stack.");
    LayerStack layerstack;
    layerstack.PushOverlay(new ImguiLayer{ window.get() });

    std::function<bool(const WindowCloseEvent&)> OnWindowClose {
        [&running](const WindowCloseEvent& e) -> bool
        {
            running = false;
            return true;
        }
    };

    APP_MSG_INFO("Setting event callback for window.");
    window->set_eventcallback([&layerstack, OnWindowClose](const Event& e) -> void
    {
        EventDispatcher dispatcher { e };
        dispatcher.dispatch<WindowCloseEvent>(OnWindowClose);

        layerstack.OnEvent(e);
    });

    while (running)
    {
        window->OnClear();
        window->OnPollEvents();
        layerstack.OnRender();
        window->OnRender();
    }

    return 0;
}
