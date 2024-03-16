#pragma once

#include "Chert/Renderer/RenderAPI.h"

namespace chert {
class OpenGLRenderAPI : public RenderAPI {
protected:
    void setClearColorImpl(const glm::vec4 &color) override;
    void clearImpl() override;
    void drawIndexedImpl(Ref<VertexArray> &vertexArray) override;
};
} // namespace chert