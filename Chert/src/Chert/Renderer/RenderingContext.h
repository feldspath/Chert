#pragma once

#include <string>
#include "Chert/Renderer/Shader.h"
#include "Chert/Renderer/Buffers/VertexBuffer.h"
#include "Chert/Renderer/Buffers/IndexBuffer.h"

namespace chert {
    class RenderingContext {
    public:
        virtual ~RenderingContext() = default;
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
        virtual std::unique_ptr<Shader> createShader(std::string& vertexShaderSrc, std::string& fragmentShaderSrc) = 0;
        virtual std::unique_ptr<VertexBuffer> createVertexBuffer(float* vertices, unsigned int size) = 0;
        virtual std::unique_ptr<IndexBuffer> createIndexBuffer(unsigned int* indices, unsigned int count) = 0;
    };
}