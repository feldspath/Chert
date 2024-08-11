#pragma once

#include "Chert/Core/Core.h"
#include "glm/gtc/type_ptr.hpp"

namespace chert {
struct LightComponent {
public:
    LightComponent() = default;
    LightComponent(glm::vec3 color, float intensity) : color(color), intensity(intensity) {}
    glm::vec3 color = {1.0f, 1.0f, 1.0f};
    float intensity = 1.0f;
};

struct DirLightComponent : public LightComponent {
public:
    DirLightComponent() = default;
    DirLightComponent(glm::vec3 direction, glm::vec3 color, float intensity = 1.0f)
        : LightComponent(color, intensity), direction(direction) {}
    glm::vec3 direction = {1.0f, 0.0f, 0.0f};
};
} // namespace chert