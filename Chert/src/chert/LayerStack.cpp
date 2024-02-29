#include "Core.h"
#include "LayerStack.h"

namespace chert {
    LayerStack::LayerStack()
    {
        layerInsertIt = layers.begin();
    }
    void LayerStack::pushLayer(std::shared_ptr<Layer> layer)
    {
        CHERT_ASSERT(!layer->isOverlay(), "Cannot push an overlay as a layer. Use pushOverlay instead.");
        layerInsertIt = layers.insert(layerInsertIt, layer);
    }
    void LayerStack::detachLayer(std::shared_ptr<Layer> layer)
    {
        auto layerIt = std::find(layers.begin(), layerInsertIt, layer);
        if (layerIt != layers.end()) {
            layers.erase(layerIt);
            refreshInsertIt();
        }
    }
    void LayerStack::pushOverlay(std::shared_ptr<Layer> overlay)
    {
        CHERT_ASSERT(overlay->isOverlay(), "Cannot push a layer as an overlay. Use pushLayer instead.");
        layers.push_back(overlay);
    }
    void LayerStack::detachOverlay(std::shared_ptr<Layer> overlay)
    {
        auto layerIt = std::find(layerInsertIt, layers.end(), overlay);
        if (layerIt != layers.end()) {
            layers.erase(layerIt);
        }
    }
    void LayerStack::refreshInsertIt()
    {
        auto it = layers.begin();
        while (!(*it)->isOverlay()) {
            it++;
        }
        layerInsertIt = it;
    }
}
