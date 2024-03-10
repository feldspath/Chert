#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace chert {
    class VertexArray {
    public:
        virtual ~VertexArray() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
        virtual void setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) = 0;
        virtual std::shared_ptr<IndexBuffer>& getIndexBuffer() = 0;
    };
}