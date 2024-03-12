#pragma once

#include "Chert/Renderer/Buffers/IndexBuffer.h"

namespace chert {
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
        ~OpenGLIndexBuffer();
        OpenGLIndexBuffer(const OpenGLIndexBuffer&) = delete;
        OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;
        void bind() override;
        void unbind() override;
        inline unsigned int getCount() const override { return count; }

    private:
        unsigned int bufferId = 0;
        unsigned int count;
    };
}