#pragma once

#include "glm/glm.hpp"
#include <string>

namespace chert {
class Shader {

public:
    virtual ~Shader() = default;
    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void setUniform(const std::string &name, const glm::mat4 &mat) = 0;
};
} // namespace chert