#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace chert {
    class Camera {
    public:
        Camera(const glm::vec3& position, const glm::quat& rotation) : position(position), rotation(rotation) {}
        virtual glm::mat4 getViewProjectionMatrix() const = 0;

        glm::vec3 position;
        glm::quat rotation;

    protected:
        glm::mat4 getViewMatrix() const {
            glm::vec3 viewDir = rotation * glm::vec3(0.0f, 1.0f, 0.0f);
            return glm::lookAt(position, position + viewDir, glm::vec3(0.0f, 0.0f, 1.0f));
        }
    };
}