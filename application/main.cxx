#include "JAGE/core.h"
#include "JAGE/layers/imgui_layer.h"

using namespace JAGE;

int main(int argc, char** argv)
{
    JAGE::Init(argc, argv);

    bool running { true };

    APP_MSG_INFO("Creating a window.");
    std::unique_ptr<Window> window { Window::create() };
    window->PushOverlay(new ImguiLayer{ window.get() });

    std::function<bool(const WindowCloseEvent&)> OnWindowClose {
        [&running](const WindowCloseEvent& e) -> bool
        {
            running = false;
            return true;
        }
    };

    APP_MSG_INFO("Setting event callback for window.");
    window->set_eventcallback([OnWindowClose](const Event& e) -> void
    {
        EventDispatcher dispatcher { e };
        dispatcher.dispatch<WindowCloseEvent>(OnWindowClose);
    });

    while (running)
    {
        window->OnClear();
        window->OnPollEvents();
        window->OnRender();
    }

    return 0;
}
