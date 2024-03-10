#pragma once

#include "Chert/Renderer/Buffers/VertexBuffer.h"

namespace chert {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, unsigned int size);
        ~OpenGLVertexBuffer();
        OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
        OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;
        void bind() override;
        void unbind() override;

    private:
        unsigned int bufferId = 0;
    };
}