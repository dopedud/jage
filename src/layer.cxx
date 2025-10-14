#include "JAGE/core.h"
#include "JAGE/layers/imgui_layer.h"
#include "log.h"

/**
 * DEFINING LAYER AND LAYERSTACK CLASS
 */
namespace JAGE
{
    Layer::Layer(std::string_view name) : m_name { name }
    {
        JAGE_MSG_TRACE("Initialised a layer with name: " + m_name);
    }

    LayerStack::LayerStack(Window* window) : window { window }, layer_insert { layers.begin() }
    {
        JAGE_MSG_TRACE("Initialised LayerStack.");
    }

    LayerStack::~LayerStack()
    {
        JAGE_MSG_TRACE("Destroying LayerStack.");

        for (Layer* layer : layers) delete layer;

        JAGE_MSG_TRACE("Destroyed LayerStack.");
    }

    void LayerStack::OnRender()
    {
        for (Layer* layer : layers) layer->OnRender();
    }

    void LayerStack::OnEvent(const Event& e)
    {
        for (auto it = layers.end(); it != layers.begin();)
        {
            if (e.handled()) break;
            (*(--it))->OnEvent(e);
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        JAGE_MSG_TRACE("Pushing layer named: " + std::string{ layer->name() });
        
        layer_insert = layers.emplace(layer_insert, layer);
        layer->OnAttach();

        JAGE_MSG_TRACE("Pushed layer named: " + std::string{ layer->name() });
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        JAGE_MSG_TRACE("Pushing overlay named: " + std::string{ overlay->name() });

        layers.emplace_back(overlay);
        overlay->OnAttach();
        
        JAGE_MSG_TRACE("Pushed overlay named: " + std::string{ overlay->name() });
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        JAGE_MSG_TRACE("Poping layer named: " + std::string{ layer->name() });

        auto it { std::find(layers.begin(), layers.end(), layer) };

        if (it != layers.end())
        {
            layers.erase(it);
            layer_insert--;
        }

        layer->OnDetach();

        JAGE_MSG_TRACE("Poped layer named: " + std::string{ layer->name() });
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        JAGE_MSG_TRACE("Poping overlay named: " + std::string{ overlay->name() });

        auto it { std::find(layers.begin(), layers.end(), overlay) };

        if (it != layers.end()) layers.erase(it);

        overlay->OnDetach();

        JAGE_MSG_TRACE("Poped overlay named: " + std::string{ overlay->name() });
    }
}
/**
 * END DEFINING LAYER AND LAYERSTACK CLASS
 */
