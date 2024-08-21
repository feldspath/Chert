#pragma once

#include "Chert/Core/Layer.h"

namespace chert {
class ImguiLayer : public Layer {

public:
    void onAttach() override;
    void onDetach() override;
    void begin();
    void end();

private:
    float time = 0.0f;
};
} // namespace chert