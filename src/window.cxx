#include "JAGE/core.h"

#include "platform/glfw/window.h"
#include "log.h"

namespace JAGE
{
    unsigned Window::width() const { return data.properties.width; }
    unsigned Window::height() const { return data.properties.height; }

    bool Window::vsync() const { return data.properties.vsync; }
        
    void Window::set_eventcallback(const EventCallbackFn& callback) { data.callback = callback; }

    float Window::aspect_ratio() const
    {
        return static_cast<float>(data.properties.width) / static_cast<float>(data.properties.height);
    }

    Layer::Layer(Window* window, std::string_view name) : window { window }, m_name { name }
    {
        JAGE_MSG_TRACE("Initialised a layer with name: " + m_name);
    }

    std::unique_ptr<Window> Window::Create(const WindowProperties& properties)
    {
        return std::make_unique<GLFWWindow>(properties);
    }

    void Window::OnEvent(const Event& e)
    {
        for (auto it = layers.end(); it != layers.begin();)
        {
            if (e.handled()) break;
            (*(--it))->OnEvent(e);
        }
    }

    void Window::PushLayer(Layer* layer)
    {
        JAGE_MSG_TRACE("Pushing layer named: " + layer->name());

        layers.emplace(layers.begin() + layer_insert_index, layer);
        layer_insert_index++;
        layer->OnAttach();

        JAGE_MSG_TRACE("Pushed layer named: " + layer->name());
    }

    void Window::PushOverlay(Layer* overlay)
    {
        JAGE_MSG_TRACE("Pushing overlay named: " + overlay->name());

        layers.emplace_back(overlay);
        overlay->OnAttach();

        JAGE_MSG_TRACE("Pushed overlay named: " + overlay->name());
    }

    void Window::PopLayer(Layer* layer)
    {
        JAGE_MSG_TRACE("Popping layer named: " + layer->name());

        auto it { std::find(layers.begin(), layers.end(), layer) };

        if (it != layers.end())
        {
            layers.erase(it);
            layer_insert_index--;
        }

        layer->OnDetach();

        JAGE_MSG_TRACE("Popped layer named: " + layer->name());
    }

    void Window::PopOverlay(Layer* overlay)
    {
        JAGE_MSG_TRACE("Popping overlay named: " + overlay->name());

        auto it { std::find(layers.begin(), layers.end(), overlay) };

        if (it != layers.end()) layers.erase(it);

        overlay->OnDetach();

        JAGE_MSG_TRACE("Popped overlay named: " + overlay->name());
    }
}
