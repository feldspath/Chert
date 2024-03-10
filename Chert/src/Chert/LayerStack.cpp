#include "Core.h"
#include "LayerStack.h"

namespace chert {
    LayerStack::LayerStack() {
        layerInsertIndex = 0;
    }

    LayerStack::~LayerStack() {
        for (auto& layer : layers) {
            layer->onDetach();
        }
    }

    void LayerStack::pushLayer(std::shared_ptr<Layer> layer)
    {
        layers.insert(layers.begin() + layerInsertIndex, layer);
        layerInsertIndex++;
        layer->onAttach();
    }

    void LayerStack::detachLayer(std::shared_ptr<Layer> layer) {
        auto layerIt = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
        if (layerIt != layers.end()) {
            layer->onDetach();
            layers.erase(layerIt);
            layerInsertIndex--;
        }
    }

    void LayerStack::pushOverlay(std::shared_ptr<Layer> overlay) {
        layers.push_back(overlay);
        overlay->onAttach();
    }

    void LayerStack::detachOverlay(std::shared_ptr<Layer> overlay) {
        auto layerIt = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
        if (layerIt != layers.end()) {
            overlay->onDetach();
            layers.erase(layerIt);
        }
    }
}
