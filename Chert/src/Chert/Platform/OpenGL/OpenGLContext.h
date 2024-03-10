#pragma once

#include "Chert/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace chert {
    class OpenGLContext : public RenderingContext {
    public:
        OpenGLContext(std::shared_ptr<GLFWwindow> window);
        void init() override;
        void swapBuffers() override;
        std::unique_ptr<Shader> createShader(std::string& vertexShaderSrc, std::string& fragmentShaderSrc) override;

    private:
        std::shared_ptr<GLFWwindow> window;
    };
}