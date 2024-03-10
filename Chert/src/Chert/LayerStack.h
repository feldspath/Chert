#pragma once

#include <vector>
#include <memory>
#include "Layer.h"

namespace chert {
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void pushLayer(std::shared_ptr<Layer> layer);
        void detachLayer(std::shared_ptr<Layer> layer);
        void pushOverlay(std::shared_ptr<Layer> overlay);
        void detachOverlay(std::shared_ptr<Layer> overlay);
        
        std::vector<std::shared_ptr<Layer>>::iterator begin() { return layers.begin(); }
        std::vector<std::shared_ptr<Layer>>::iterator end() { return layers.end(); }
    private:
        int layerInsertIndex;
        std::vector<std::shared_ptr<Layer>> layers;
    };
}
