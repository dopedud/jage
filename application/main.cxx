#include "JAGE/core.h"
#include "JAGE/layers.h"
#include "JAGE/math.h"

using namespace JAGE;

int main(int argc, char** argv)
{
    Init(argc, argv);

    bool running { true };

    APP_MSG_TRACE("Creating a window.");
    WindowProperties window_properties {};
    std::unique_ptr<Window> window { Window::Create(window_properties) };

    Input::SetActiveWindow(window.get());

    window->PushLayer(new GameLayer{ window.get() });
    window->PushOverlay(new ImguiLayer{ window.get() });

    std::function<bool(const WindowCloseEvent&)> OnWindowClose
    {
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

    // Time::SetTargetFPS(100);

    while (running)
    {
        window->OnRender();
    }

    APP_MSG_INFO("Exiting application.");

    window.reset();

    Destroy();

    return 0;
}
