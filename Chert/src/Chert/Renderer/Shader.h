#pragma once

#include "glm/glm.hpp"
#include <string>

namespace chert {
enum class ShaderType {
    Vertex,
    Fragment,
    Count,
    None,
};

inline std::string typeToString(ShaderType type) {
    switch (type) {
    case ShaderType::Vertex:
        return "Vertex";
    case ShaderType::Fragment:
        return "Fragment";
    default:
        return "None";
    }
}

class Shader {

public:
    virtual ~Shader() = default;
    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void setUniform(const std::string &name, const glm::mat4 &mat) = 0;
    virtual void setUniform(const std::string &name, const glm::vec3 &vec) = 0;
    virtual void setUniform(const std::string &name, const glm::vec4 &vec) = 0;
    virtual void setUniform(const std::string &name, int value) = 0;

    /// Input must be lowercase
    static ShaderType shaderTypeFromString(const std::string &shaderType) {
        if (shaderType == "vertex") {
            return ShaderType::Vertex;
        }
        if (shaderType == "fragment") {
            return ShaderType::Fragment;
        }
        return ShaderType::None;
    }

    static inline constexpr int shaderTypeCount() { return static_cast<int>(ShaderType::Count); }
};
} // namespace chert