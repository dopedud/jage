#include "JAGE/core.h"
#include "JAGE/layers/imgui_layer.h"

using namespace JAGE;

// TEMPORARY LAYER
class ExampleLayer : public Layer
{
public:
    ExampleLayer() : Layer("Example Layer") {}
    
    void OnAttach() override {}
    void OnDetach() override {}
    void OnUpdate() override {}
    void OnEvent(const Event& e) override { APP_MSG_INFO(m_name + " - " + std::string{ e.to_string() }); }
};
// END TEMPORARY LAYER

int main(int argc, char** argv)
{
    JAGE::Init(argc, argv);

    bool running { true };

    APP_MSG_INFO("Creating a window.");
    std::unique_ptr<Window> window { std::make_unique<Window>() };

    APP_MSG_INFO("Creating a layer stack.");
    LayerStack layerstack;
    layerstack.PushLayer(new ExampleLayer{});
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
        layerstack.OnUpdate();
        window->OnUpdate();
    }

    APP_MSG_DEBUG("SHOULD ONLY GET HERE WHEN EXIT IS INTENTIONAL");

    return 0;
}
