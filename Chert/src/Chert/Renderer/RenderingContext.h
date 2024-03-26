#pragma once

#include "Chert/Renderer/Buffers/IndexBuffer.h"
#include "Chert/Renderer/Buffers/VertexArray.h"
#include "Chert/Renderer/Buffers/VertexBuffer.h"
#include "Chert/Renderer/Shader.h"
#include <string>

namespace chert {
class RenderingContext {
public:
    virtual ~RenderingContext() = default;
    virtual void init() = 0;
    virtual void swapBuffers() = 0;
    virtual Ref<Shader>
    createShader(const std::array<std::string, Shader::shaderTypeCount()> &sources) = 0;
    virtual Ref<Shader> createShader(const std::string &shaderFilePath) = 0;
    virtual Ref<VertexBuffer> createVertexBuffer(float *vertices, unsigned int size) = 0;
    virtual Ref<IndexBuffer> createIndexBuffer(unsigned int *indices, unsigned int count) = 0;
    virtual Ref<VertexArray> createVertexArray() = 0;
};
} // namespace chert