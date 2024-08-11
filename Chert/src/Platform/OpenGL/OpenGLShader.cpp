#include "OpenGLShader.h"
#include "Chert/Core/Core.h"
#include "glad/glad.h"
#include <algorithm>
#include <fstream>
#include <vector>

#include "glm/gtc/type_ptr.hpp"

namespace chert {

static inline GLuint shaderTypeToOpenGLType(ShaderType type) {
    switch (type) {
    case ShaderType::Vertex:
        return GL_VERTEX_SHADER;
    case ShaderType::Fragment:
        return GL_FRAGMENT_SHADER;
    default:
        CHERT_CORE_ASSERT(false, "Invalid shader type: {}", typeToString(type));
        return 0;
    }
}

static unsigned int compileShader(const std::string &src, ShaderType type) {
    unsigned int shader = glCreateShader(shaderTypeToOpenGLType(type));
    const char *source = src.c_str();
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    int isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        int maxLength = 128;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

        glDeleteShader(shader);
        CHERT_CORE_ASSERT(false, "Failed to compile {} shader: {}", typeToString(type),
                          infoLog.data());
        return 0;
    }

    return shader;
}

static auto parseShaderFile(const std::string &shaderFilePath) {
    auto fs = std::fstream(shaderFilePath);
    if (!fs.is_open()) {
        CHERT_CORE_ASSERT(false, "Failed to open shader file at {}", shaderFilePath);
    }
    std::string fileString(std::istreambuf_iterator<char>(fs), {});

    std::array<std::string, Shader::shaderTypeCount()> shaderSources;

    size_t currentPos = 0;
    while (currentPos != fileString.npos) {
        // get line that starts with #type
        auto typePos = fileString.find("#type", currentPos) + 5;
        auto lineLength = fileString.find_first_of('\n', typePos) - typePos;
        auto type = fileString.substr(typePos, lineLength);

        // Remove whitespace
        type.erase(remove_if(type.begin(), type.end(), isspace), type.end());
        std::transform(type.begin(), type.end(), type.begin(), ::tolower);

        int shaderIndex = static_cast<int>(Shader::shaderTypeFromString(type));
        if (!shaderSources[shaderIndex].empty()) {
            CHERT_CORE_ASSERT(false, "Shader type {} was defined multiple times in {}", type,
                              shaderFilePath);
        }

        currentPos = fileString.find("#type", typePos + lineLength);
        auto src_length = currentPos - (typePos + lineLength);
        auto src = fileString.substr(typePos + lineLength, src_length);
        shaderSources[shaderIndex] = src;
    }

    return shaderSources;
}

OpenGLShader::OpenGLShader(const std::array<std::string, shaderTypeCount()> &sources) {

    std::vector<unsigned int> shaders;
    shaders.reserve(shaderTypeCount());
    for (int t = 0; t < sources.size(); ++t) {
        if (!sources[t].empty()) {
            shaders.push_back(compileShader(sources[t], static_cast<ShaderType>(t)));
        }
    }

    // Program linking
    programId = glCreateProgram();
    for (auto shader : shaders) {
        glAttachShader(programId, shader);
    }

    glLinkProgram(programId);

    int isLinked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        int maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, infoLog.data());

        glDeleteProgram(programId);
        for (auto shader : shaders) {
            glDeleteShader(shader);
        }
        CHERT_CORE_CRITICAL("Failed to link shader program: {0}", infoLog.data());
        return;
    }

    for (auto shader : shaders) {
        glDetachShader(programId, shader);
    }
}

OpenGLShader::OpenGLShader(const std::string &shaderFilePath)
    : OpenGLShader(parseShaderFile(shaderFilePath)) {}

OpenGLShader::~OpenGLShader() { glDeleteProgram(programId); }

void OpenGLShader::bind() { glUseProgram(programId); }

void OpenGLShader::unbind() { glUseProgram(0); }

void OpenGLShader::setUniform(const std::string &name, const glm::mat4 &mat) {
    glUseProgram(programId);
    auto uniformLocation = glGetUniformLocation(programId, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat));
}
void OpenGLShader::setUniform(const std::string &name, const glm::vec3 &vec) {
    glUseProgram(programId);
    auto uniformLocation = glGetUniformLocation(programId, name.c_str());
    glUniform3fv(uniformLocation, 1, glm::value_ptr(vec));
}
void OpenGLShader::setUniform(const std::string &name, const glm::vec4 &vec) {
    glUseProgram(programId);
    auto uniformLocation = glGetUniformLocation(programId, name.c_str());
    glUniform4fv(uniformLocation, 1, glm::value_ptr(vec));
}
void OpenGLShader::setUniform(const std::string &name, int value) {
    glUseProgram(programId);
    auto uniformLocation = glGetUniformLocation(programId, name.c_str());
    glUniform1i(uniformLocation, value);
}
void OpenGLShader::setUniform(const std::string &name, float value) {
    glUseProgram(programId);
    auto uniformLocation = glGetUniformLocation(programId, name.c_str());
    glUniform1f(uniformLocation, value);
}
} // namespace chert
