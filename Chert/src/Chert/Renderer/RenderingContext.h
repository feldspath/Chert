#pragma once

#include <string>
#include "Chert/Renderer/Shader.h"

namespace chert {
    class RenderingContext {
    public:
        virtual ~RenderingContext() = default;
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
        virtual std::unique_ptr<Shader> createShader(std::string& vertexShaderSrc, std::string& fragmentShaderSrc) = 0;
    };
}