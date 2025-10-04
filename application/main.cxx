#include "JAGE/core.h"

using namespace JAGE;

class ExampleLayer : public Layer
{
public:
    ExampleLayer() : Layer("Example") {}
    
    void OnEvent(const Event& e) override { APP_MSG_INFO(m_name + " - " + std::string{ e.to_string() }); }
};

int main(int argc, char** argv)
{

    JAGE::Init(argc, argv);

    LayerStack layerstack;
    layerstack.PushLayer(new ExampleLayer{});

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

        layerstack.OnEvent(e);
    });

    while (running)
    {
        layerstack.OnUpdate();
        window->OnUpdate();
    }

    APP_MSG_DEBUG("SHOULD ONLY GET HERE WHEN EXIT IS INTENTIONAL");

    return 0;
}
