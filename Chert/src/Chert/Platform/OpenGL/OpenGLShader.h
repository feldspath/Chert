#pragma once

#include <string>
#include "Chert/Renderer/Shader.h"

namespace chert {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(std::string& vertexShaderSrc, std::string& fragmentShaderSrc);
        ~OpenGLShader();
        OpenGLShader(const Shader&) = delete;
        OpenGLShader& operator=(const Shader&) = delete;

        void bind() override;
        void unbind() override;

    private:
        unsigned int programId = 0;
    };
}