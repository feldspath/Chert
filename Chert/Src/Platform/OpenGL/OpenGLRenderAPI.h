#pragma once

#include "Chert/Renderer/RenderAPI.h"

namespace chert {
class OpenGLRenderAPI : public RenderAPI {
protected:
    void setClearColorImpl(const glm::vec4 &color) override;
    void clearImpl() override;
    void drawIndexedImpl(Ref<VertexArray> &vertexArray) override;
    void setViewportImpl(unsigned int x, unsigned int y, unsigned int width,
                         unsigned int height) override;
    void unbindCurrentVertexArrayImpl() override;
};
} // namespace chert