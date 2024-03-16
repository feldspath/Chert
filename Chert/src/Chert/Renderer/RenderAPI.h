#pragma once

#include "Buffers/VertexArray.h"
#include <glm/glm.hpp>
#include <memory>

namespace chert {
class RenderAPI {
protected:
    RenderAPI() = default;

public:
    static inline void setClearColor(const glm::vec4 &color) {
        instance->setClearColorImpl(color);
    }
    static inline void clear() { instance->clearImpl(); }
    static inline void drawIndexed(std::shared_ptr<VertexArray> &vertexArray) {
        instance->drawIndexedImpl(vertexArray);
    }
    static void init();

protected:
    virtual void setClearColorImpl(const glm::vec4 &color) = 0;
    virtual void clearImpl() = 0;
    virtual void
    drawIndexedImpl(std::shared_ptr<VertexArray> &vertexBuffer) = 0;

private:
    static std::unique_ptr<RenderAPI> RenderAPI::instance;
};

std::unique_ptr<RenderAPI> createRenderAPI();
} // namespace chert