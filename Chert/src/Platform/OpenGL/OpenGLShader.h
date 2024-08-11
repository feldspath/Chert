#pragma once

#include "Chert/Renderer/Shader.h"
#include <string>

namespace chert {
class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::array<std::string, shaderTypeCount()> &sources);
    OpenGLShader(const std::string &shaderFilePath);
    ~OpenGLShader();
    OpenGLShader(const Shader &) = delete;
    OpenGLShader &operator=(const Shader &) = delete;

    void bind() override;
    void unbind() override;
    void setUniform(const std::string &name, const glm::mat4 &mat) override;
    void setUniform(const std::string &name, const glm::vec3 &vec) override;
    void setUniform(const std::string &name, const glm::vec4 &vec) override;
    void setUniform(const std::string &name, int value) override;
    void setUniform(const std::string &name, float value) override;

private:
    unsigned int programId = 0;
};
} // namespace chert