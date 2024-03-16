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
        void setUniform(const std::string& name, const glm::mat4& mat) override;
        
    private:
        unsigned int programId = 0;
    };
}