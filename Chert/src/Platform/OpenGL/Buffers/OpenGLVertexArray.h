#pragma once

#include <vector>
#include "Chert/Renderer/Buffers/VertexArray.h"
#include "Chert/Renderer/Buffers/IndexBuffer.h"

namespace chert {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();
        OpenGLVertexArray(const OpenGLVertexArray&) = delete;
        OpenGLVertexArray& operator=(const OpenGLVertexArray&) = delete;
        void bind() override;
        void unbind() override;
        void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
        void setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) override;
        std::shared_ptr<IndexBuffer>& getIndexBuffer() override { return indexBuffer; }

    private:
        unsigned int vertexArrayId = 0;
        std::vector <std::shared_ptr<VertexBuffer>> vertexBuffers;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}