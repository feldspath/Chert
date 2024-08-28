#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace chert {
struct TransformComponent {
    // Default position: in the center of the world
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    // Default rotation: no rotation
    glm::quat rotation = glm::quat_identity<float, glm::defaultp>();
    // Default scale: 1 in all directions
    glm::vec3 scale = {1.0f, 1.0f, 1.0f};

    /// Rotation from a world pointing up in the z direction to a world pointing up in the y
    /// direction
    static glm::quat rotateZupToYup() {
        // Rotation from OpenGL space to camera space
        return glm::rotate(glm::quat_identity<float, glm::defaultp>(), glm::radians(90.0f),
                           glm::vec3(1.0f, 0.0f, 0.0f));
    }

    /// Rotation from a world pointing up in the y direction to a world pointing up in the z
    /// direction
    static glm::quat rotateYupToZup() {
        return glm::rotate(glm::quat_identity<float, glm::defaultp>(), glm::radians(-90.0f),
                           glm::vec3(1.0f, 0.0f, 0.0f));
    }

    /// Convert to matrix form
    glm::mat4 modelMatrix() const {
        return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) *
               glm::scale(glm::mat4(1.0f), scale);
    }

    /// Make the front of the transform point to target
    void lookAt(const glm::vec3 &target) {
        rotation = glm::quatLookAt(glm::normalize(target - position), glm::vec3(0.0f, 0.0f, 1.0f)) *
                   rotateYupToZup();
    }

    glm::vec3 right() const { return glm::rotate(rotation, glm::vec3(1.0f, 0.0f, 0.0f)); }
    glm::vec3 front() const { return glm::rotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f)); }
    glm::vec3 up() const { return glm::rotate(rotation, glm::vec3(0.0f, 0.0f, 1.0f)); }
};
} // namespace chert