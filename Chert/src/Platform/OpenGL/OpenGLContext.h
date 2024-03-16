#pragma once

#include "Chert/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace chert {
    class OpenGLContext : public RenderingContext {
    public:
        OpenGLContext(GLFWwindow* window);
        void init() override;
        void swapBuffers() override;
        std::unique_ptr<Shader> createShader(std::string& vertexShaderSrc, std::string& fragmentShaderSrc) override;
        std::unique_ptr<VertexBuffer> createVertexBuffer(float* vertices, unsigned int size) override;
        std::unique_ptr<IndexBuffer> createIndexBuffer(unsigned int* indices, unsigned int count) override;
        std::unique_ptr<VertexArray> createVertexArray() override;

    private:
        GLFWwindow* window;
    };
}