#include "JAGE/core.h"

int main(int argc, char** argv)
{
    using namespace JAGE;

    JAGE::Init(argc, argv);

    LayerStack layerstack;

    bool running = true;

    APP_MSG_INFO("Creating a window.");
    std::unique_ptr<Window> window = std::make_unique<Window>();

    std::function<bool(const WindowCloseEvent&)> OnWindowClose =
    [&running](const WindowCloseEvent& e) -> bool
    {
        running = false;
        return true;
    };

    APP_MSG_INFO("Setting event callback for window.");
    window->set_eventcallback([&layerstack, OnWindowClose](const Event& e) -> void
    {
        EventDispatcher dispatcher { e };
        dispatcher.dispatch<WindowCloseEvent>(OnWindowClose);

        for (auto it = layerstack.end(); it != layerstack.begin(); --it)
        {
            (*it)->OnEvent(e);
            if (e.handled()) break;
        }
    });

    while (running)
    {
        layerstack.OnUpdate();
        window->OnUpdate();
    }

    return 0;
}
