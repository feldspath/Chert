#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace chert {
class VertexArray {
public:
    virtual ~VertexArray() = default;
    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) = 0;
    virtual void setIndexBuffer(Ref<IndexBuffer> indexBuffer) = 0;
    virtual Ref<IndexBuffer> &getIndexBuffer() = 0;
};
} // namespace chert