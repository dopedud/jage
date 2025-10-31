#include "JAGE/core.h"
#include "JAGE/layers.h"

using namespace JAGE;

int main(int argc, char** argv)
{
    LogInit();

    bool running { true };

    APP_MSG_INFO("Creating a window.");
    std::unique_ptr<Window> window { Window::Create() };

    window->PushLayer(new GameLayer{ window.get() });
    window->PushOverlay(new ImguiLayer{ window.get() });

    Input::SetActiveWindow(window.get());

    std::function<bool(const WindowCloseEvent&)> OnWindowClose {
        [&running](const WindowCloseEvent& e) -> bool
        {
            running = false;
            return true;
        }
    };

    APP_MSG_TRACE("Setting event callback for window.");
    window->set_eventcallback([OnWindowClose](const Event& e) -> void
    {
        EventDispatcher dispatcher { e };
        dispatcher.dispatch<WindowCloseEvent>(OnWindowClose);
    });

    while (running)
    {
        window->OnRender();
    }

    window.reset();

    APP_MSG_INFO("Exiting application.");

    return 0;
}
