#pragma once

#include "Camera.h"

namespace chert {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(glm::vec3 position, glm::quat rotation) : Camera(position, rotation) {
        projectionMatrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
    }

    glm::mat4 getViewProjectionMatrix() const override {
        return projectionMatrix * getViewMatrix();
    }

private:
    glm::mat4 projectionMatrix;
};
} // namespace chert