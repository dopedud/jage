#include "JAGE/renderer.h"

#include "platform/glfw/window.h"
#include "log.h"

namespace JAGE
{
    Window::Properties::Properties
    (
        std::string_view title,
        unsigned width,
        unsigned height,
        bool vsync
    )
    : title { title }
    , width { width }
    , height { height }
    , vsync { vsync } {}

    Window::Window(const Properties& properties) 
    : data {}
    , layers {}
    , layer_insert_index {}
    , m_renderer {}
    , m_debug_renderer {}
    { data.properties = properties; }

    std::unique_ptr<Window> Window::Create(const Properties& properties)
    { return std::make_unique<GLFWWindow>(properties); }

    unsigned Window::width() const { return data.properties.width; }
    unsigned Window::height() const { return data.properties.height; }

    float Window::aspect_ratio() const
    { return static_cast<float>(data.properties.width) / static_cast<float>(data.properties.height); }

    bool Window::vsync() const { return data.properties.vsync; }

    Renderer* Window::renderer() const { return m_renderer.get(); }
    DebugRenderer* Window::debug_renderer() const { return m_debug_renderer.get(); }
        
    void Window::set_eventcallback(const EventCallbackFn& callback) { data.callback = callback; }

    void Window::OnEvent(const Event& e)
    {
        for (std::vector<std::unique_ptr<Layer>>::iterator it = layers.end(); it != layers.begin();)
        {
            if (e.handled()) break;
            (*(--it))->OnEvent(e);
        }
    }

    void Window::PushLayer(std::unique_ptr<Layer> layer)
    {
        std::string name { layer->name() };
        JAGE_MSG_TRACE("Pushing layer named: " + name);

        layer->OnAttach();
        layers.emplace(layers.begin() + layer_insert_index, std::move(layer));
        layer_insert_index++;

        JAGE_MSG_TRACE("Pushed layer named: " + name);
    }

    void Window::PushOverlay(std::unique_ptr<Layer> overlay)
    {
        std::string name { overlay->name() };
        JAGE_MSG_TRACE("Pushing overlay named: " + name);

        overlay->OnAttach();
        layers.emplace_back(std::move(overlay));

        JAGE_MSG_TRACE("Pushed overlay named: " + name);
    }

    // void Window::PopLayer(std::unique_ptr<Layer> layer)
    // {
    //     std::string name { layer->name() };
    //     JAGE_MSG_TRACE("Popping layer named: " + layer->name());

    //     layer->OnDetach();

    //     auto it { std::find(layers.begin(), layers.end(), layer) };

    //     if (it != layers.end())
    //     {
    //         layers.erase(it);
    //         layer_insert_index--;
    //     }

    //     JAGE_MSG_TRACE("Popped layer named: " + layer->name());
    // }

    // void Window::PopOverlay(std::unique_ptr<Layer> overlay)
    // {
    //     JAGE_MSG_TRACE("Popping overlay named: " + overlay->name());

    //     overlay->OnDetach();

    //     auto it { std::find(layers.begin(), layers.end(), overlay) };

    //     if (it != layers.end()) layers.erase(it);

    //     JAGE_MSG_TRACE("Popped overlay named: " + overlay->name());
    // }

    Layer::Layer(Window* window, std::string_view name) : m_window { window }, m_name { name }
    { JAGE_MSG_TRACE("Initialised a layer with name: " + m_name); }
}
