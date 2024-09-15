#pragma once

#include "Camera.h"
#include "Chert/Core/Input.h"
#include "Chert/Events/MouseEvent.h"
#include "Chert/Scene/Components/Transform.h"
#include "glm/gtc/type_ptr.hpp"

namespace chert {
class EditorCamera {
public:
    EditorCamera() { transform.position = glm::vec3{0.0f, -5.0f, 0.0f}; }
    void onUpdate(float timestep);
    void onMouseMoved(const MouseMovedEvent &e);
    void onMouseScrolled(const MouseScrolledEvent &e);

    inline void setAspectRatio(float aspectRatio) { camera.setAspectRatio(aspectRatio); }
    inline void setCenter(const glm::vec3 &center) { this->center = center; }
    inline const TransformComponent &getTransform() const { return transform; }
    glm::mat4 getViewProjectionMatrix() const;

private:
    Camera camera;
    TransformComponent transform;
    glm::vec3 center = {0.0f, 0.0f, 0.0f};

    double previousMouseX = 0.0;
    double previousMouseY = 0.0;
};
} // namespace chert