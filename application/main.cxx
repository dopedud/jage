#include "JAGE/core.h"

int main(int argc, char** argv)
{
    using namespace JAGE;

    JAGE::Init(argc, argv);

    bool running = true;

    APP_MSG_INFO("Creating a window.");
    std::unique_ptr<Window> window = std::make_unique<Window>();

    std::function<bool(WindowCloseEvent&)> OnWindowClose =
    [&running](WindowCloseEvent& e) -> bool
    {
        running = false;
        return true;
    };

    APP_MSG_INFO("Setting event callback for window.");
    window->set_eventcallback([OnWindowClose](Event& e) -> void
    {
        APP_LOG_INFO("{}", e.to_string());

        EventDispatcher dispatcher { e };
        dispatcher.dispatch<WindowCloseEvent>(OnWindowClose);
    });

    while (running)
    {
        window->OnUpdate();
    }

    return 0;
}
