#include "OpenGLShader.h"
#include "Chert/Core.h"
#include "glad/glad.h"
#include <vector>

#include "glm/gtc/type_ptr.hpp"

namespace chert {

OpenGLShader::OpenGLShader(std::string &vertexShaderSrc, std::string &fragmentShaderSrc) {
    // Vertex shader compilation
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *source = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &source, 0);
    glCompileShader(vertexShader);

    int isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        int maxLength = 128;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog.data());

        glDeleteShader(vertexShader);
        CHERT_CORE_ASSERT(false, "Failed to compile vertex shader: {0}", infoLog.data());
        return;
    }

    // Fragment shader compilation
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        int maxLength = 128;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog.data());

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        CHERT_CORE_ASSERT(false, "Failed to compile fragment shader: {0}", infoLog.data());
        return;
    }

    // Program linking
    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);

    int isLinked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        int maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, infoLog.data());

        glDeleteProgram(programId);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        CHERT_CORE_CRITICAL("Failed to link shader program: {0}", infoLog.data());
        return;
    }

    glDetachShader(programId, vertexShader);
    glDetachShader(programId, fragmentShader);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(programId); }

void OpenGLShader::bind() { glUseProgram(programId); }

void OpenGLShader::unbind() { glUseProgram(0); }

void OpenGLShader::setUniform(const std::string &name, const glm::mat4 &mat) {
    glUseProgram(programId);
    auto uniformLocation = glGetUniformLocation(programId, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat));
}
} // namespace chert
