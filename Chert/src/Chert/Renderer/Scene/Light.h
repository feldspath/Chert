#pragma once

#include <glm/glm.hpp>

namespace chert {
class Light {
public:
    Light(glm::vec3 color) : color(color) {}
    glm::vec3 color;
};
} // namespace chert