#pragma once

#include "Chert/Renderer/Buffers/VertexBuffer.h"

namespace chert {
class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(float *vertices, unsigned int size);
    ~OpenGLVertexBuffer();
    OpenGLVertexBuffer(const OpenGLVertexBuffer &) = delete;
    OpenGLVertexBuffer &operator=(const OpenGLVertexBuffer &) = delete;
    void bind() override;
    void unbind() override;
    inline void setLayout(const BufferLayout &layout) override {
        this->layout = layout;
    }
    inline const BufferLayout &getLayout() override { return layout; }

private:
    unsigned int bufferId = 0;
    BufferLayout layout;
};
} // namespace chert