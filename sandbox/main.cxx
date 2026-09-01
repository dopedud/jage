#include "JAGE/core.h"
#include "JAGE/layers.h"

using namespace JAGE;

int main(int argc, char** argv)
{
    Init(argc, argv);

    bool running { true };

    APP_MSG_TRACE("Creating a window.");
    Window::Properties window_properties {};
    std::unique_ptr<Window> window { Window::Create(window_properties) };

    window->PushLayer(std::make_unique<GameLayer>(window.get()));
    window->PushOverlay(std::make_unique<ImguiLayer>(window.get()));

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

    // Time::SetTargetFPS(60);

    APP_MSG_TRACE("Running the game loop.");
    while (running)
    {
        window->OnUpdate();
    }

    APP_MSG_INFO("Exiting application.");

    window.reset();

    Destroy();

    return 0;
}
