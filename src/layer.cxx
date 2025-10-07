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

    LayerStack::LayerStack()
    {
        JAGE_MSG_TRACE("Initialising LayerStack.");

        layer_insert = layers.begin();

        JAGE_MSG_TRACE("Initialised LayerStack.");
    }

    LayerStack::~LayerStack()
    {
        JAGE_MSG_TRACE("Destroying LayerStack.");

        for (Layer* layer : layers) delete layer;

        JAGE_MSG_TRACE("Destroyed LayerStack.");
    }

    void LayerStack::OnUpdate()
    {
        for (Layer* layer : layers) layer->OnUpdate();
    }

    void LayerStack::OnEvent(const Event& e)
    {
        for (auto it = layers.end(); it != layers.begin();)
        {
            (*(--it))->OnEvent(e);
            if (e.handled()) break;
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
        auto it { std::find(layers.begin(), layers.end(), layer) };

        if (it != layers.end())
        {
            layers.erase(it);
            layer_insert--;
        }

        layer->OnDetach();
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it { std::find(layers.begin(), layers.end(), overlay) };

        if (it != layers.end()) layers.erase(it);

        overlay->OnDetach();
    }
}
/**
 * END DEFINING LAYER AND LAYERSTACK CLASS
 */
