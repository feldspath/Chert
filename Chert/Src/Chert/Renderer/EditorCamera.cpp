#include "EditorCamera.h"

namespace chert {
glm::mat4 EditorCamera::getViewProjectionMatrix() const {
    auto &cameraProjection = camera.getProjectionMatrix();
    auto cameraView =
        glm::inverse(transform.modelMatrix() * glm::toMat4(TransformComponent::rotateZupToYup()));
    return cameraProjection * cameraView;
}
void EditorCamera::onUpdate(float timestep) {
    float speed = 3.0f;
    if (Input::isKeyPressed(CHERT_KEY_W)) {
        transform.position += speed * timestep * transform.front();
    }
    if (Input::isKeyPressed(CHERT_KEY_S)) {
        transform.position -= speed * timestep * transform.front();
    }
    if (Input::isKeyPressed(CHERT_KEY_D)) {
        transform.position += speed * timestep * transform.right();
    }
    if (Input::isKeyPressed(CHERT_KEY_A)) {
        transform.position -= speed * timestep * transform.right();
    }
}

void EditorCamera::onMouseMoved(const MouseMovedEvent &e) {
    if (Input::isMouseButtonPressed(1)) {
        double dx = (e.getMouseX() - previousMouseX) * 0.3f;
        double dy = (e.getMouseY() - previousMouseY) * 0.3f;

        glm::vec3 up{0.0f, 0.0f, 1.0f};
        if (transform.up().z < 0.0f) {
            // Invert up vector if camera is upside down
            up *= -1.0f;
        }

        auto rotation = glm::mat4(glm::rotate(glm::mat4(1.0f), glm::radians(-(float)dx), up));

        auto right = glm::normalize(glm::cross(transform.position, up));
        rotation = glm::rotate(rotation, glm::radians((float)dy), right);
        transform.position = glm::mat3(rotation) * (transform.position - center) + center;
        transform.rotation = glm::quat(rotation) * transform.rotation;
    }
    previousMouseX = e.getMouseX();
    previousMouseY = e.getMouseY();
}

void EditorCamera::onMouseScrolled(const MouseScrolledEvent &e) {
    transform.position *= 1.0f - (float)e.getYOffset() * 0.08f;
}
} // namespace chert