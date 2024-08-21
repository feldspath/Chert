#pragma once

#include "Chert/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace chert {
class OpenGLContext : public RenderingContext {
public:
    OpenGLContext(GLFWwindow *window);
    void init() override;
    void swapBuffers() override;
    Ref<Shader>
    createShader(const std::array<std::string, Shader::shaderTypeCount()> &sources) override;
    Ref<Shader> createShader(const std::string &shaderFilePath) override;
    Ref<VertexBuffer> createVertexBuffer(float *vertices, unsigned int size) override;
    Ref<IndexBuffer> createIndexBuffer(unsigned int *indices, unsigned int count) override;
    Ref<VertexArray> createVertexArray() override;

private:
    GLFWwindow *window;
};
} // namespace chert