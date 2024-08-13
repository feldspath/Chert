#pragma once

#include "Chert/Scene/Components/Transform.h"

namespace chert {
class Camera {
public:
    Camera(const glm::vec3 &position,
           const glm::quat &rotation = glm::quat_identity<float, glm::defaultp>()) {
        transform.position = position;
        transform.rotation = rotation;
    }
    virtual glm::mat4 getViewProjectionMatrix() const = 0;
    virtual void setAspectRatio(float aspectRatio) = 0;

    TransformComponent transform;

protected:
    glm::mat4 getViewMatrix() const { return glm::inverse(transform.modelMatrix()); }
};
} // namespace chert