#pragma once

#include "Light.h"

namespace chert {
class DirLight : public Light {
public:
    DirLight(glm::vec3 direction, glm::vec3 color) : Light(color), direction(direction) {}
    glm::vec3 direction;
};
} // namespace chert