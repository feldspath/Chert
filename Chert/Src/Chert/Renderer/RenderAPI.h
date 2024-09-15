#pragma once

#include "Buffers/VertexArray.h"
#include <glm/glm.hpp>
#include <memory>

namespace chert {
class RenderAPI {
protected:
    RenderAPI() = default;

public:
    static inline void setClearColor(const glm::vec4 &color) { instance->setClearColorImpl(color); }
    static inline void clear() { instance->clearImpl(); }
    static inline void drawIndexed(Ref<VertexArray> &vertexArray) {
        instance->drawIndexedImpl(vertexArray);
    }
    static inline void setViewport(unsigned int x, unsigned int y, unsigned int width,
                                   unsigned int height) {
        instance->setViewportImpl(x, y, width, height);
    }
    static void init();
    static void unbindCurrentVertexArray() { instance->unbindCurrentVertexArrayImpl(); }

protected:
    virtual void setClearColorImpl(const glm::vec4 &color) = 0;
    virtual void clearImpl() = 0;
    virtual void drawIndexedImpl(Ref<VertexArray> &vertexBuffer) = 0;
    virtual void setViewportImpl(unsigned int x, unsigned int y, unsigned int width,
                                 unsigned int height) = 0;
    virtual void unbindCurrentVertexArrayImpl() = 0;

private:
    static std::unique_ptr<RenderAPI> RenderAPI::instance;
};

std::unique_ptr<RenderAPI> createRenderAPI();
} // namespace chert