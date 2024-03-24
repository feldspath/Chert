#pragma once

#include "Camera.h"

namespace chert {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(glm::vec3 position, glm::quat rotation, float aspectRatio)
        : Camera(position, rotation) {
        projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    }

    glm::mat4 getViewProjectionMatrix() const override {
        return projectionMatrix * getViewMatrix();
    }

    void setAspectRatio(float aspectRatio) override {
        projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    }

private:
    glm::mat4 projectionMatrix;
};
} // namespace chert