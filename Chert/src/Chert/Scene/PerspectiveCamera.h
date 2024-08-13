#pragma once

#include "Camera.h"

namespace chert {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(glm::vec3 position, glm::quat rotation) : Camera(position, rotation) {
        setAspectRatio(chert::Application::get().getWindow()->aspectRatio());
    }
    PerspectiveCamera(glm::vec3 position, glm::vec3 target) : Camera(position) {
        transform.lookAt(target);
        setAspectRatio(chert::Application::get().getWindow()->aspectRatio());
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