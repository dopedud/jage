#include "JAGE/core.h"
#include "JAGE/layers.h"
#include "JAGE/math.h"

using namespace JAGE;

int main(int argc, char** argv)
{
    bool running { true };

    Init(argc, argv);

    APP_MSG_INFO("Creating a window.");
    std::unique_ptr<Window> window { Window::Create() };

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

    // Time::SetTargetFPS(240);

    while (running)
    {
        Time::StartLoop();

        window->OnRender();

        Time::EndLoop();
    }

    APP_MSG_INFO("Exiting application.");

    window.reset();

    Destroy();

    return 0;
}
