#pragma once

#include "glm/gtc/type_ptr.hpp"

namespace chert {
struct TransformComponent {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
};
} // namespace chert