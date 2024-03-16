#pragma once

#include "Chert/Renderer/Buffers/IndexBuffer.h"
#include "Chert/Renderer/Buffers/VertexArray.h"
#include <vector>

namespace chert {
class OpenGLVertexArray : public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();
    OpenGLVertexArray(const OpenGLVertexArray &) = delete;
    OpenGLVertexArray &operator=(const OpenGLVertexArray &) = delete;
    void bind() override;
    void unbind() override;
    void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) override;
    void setIndexBuffer(Ref<IndexBuffer> indexBuffer) override;
    Ref<IndexBuffer> &getIndexBuffer() override { return indexBuffer; }

private:
    unsigned int vertexArrayId = 0;
    unsigned int vertexAttribIndex = 0;
    std::vector<Ref<VertexBuffer>> vertexBuffers;
    Ref<IndexBuffer> indexBuffer;
};
} // namespace chert