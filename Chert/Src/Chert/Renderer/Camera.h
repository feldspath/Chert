#pragma once

#include <variant>

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace chert {
class Camera {
public:
    enum Type { Perspective = 0, Orthographic = 1 };
    struct OrthographicParameters {
        float size = 10.0f;
        float near = 0.1f;
        float far = 100.0f;
    };

    struct PerspectiveParameters {
        float fov = 45.0f;
        float near = 0.1f;
        float far = 100.0f;
    };

    Camera(Type type, float aspectRatio) : type(type), aspectRatio(aspectRatio) {
        cameraParams = PerspectiveParameters();
        computeProjectionMatrix();
    }
    Camera() : Camera(Perspective, 16.0f / 9.0f) {}

    void setType(Type type) {
        if (this->type == type) {
            return;
        }
        this->type = type;
        switch (type) {
        case Perspective: {
            cameraParams = PerspectiveParameters();
            break;
        }
        case Orthographic: {
            cameraParams = OrthographicParameters();
            break;
        }
        default:
            // Unreachable
            break;
        }
        computeProjectionMatrix();
    };

    void setOrthographic(OrthographicParameters params) {
        cameraParams = params;
        computeProjectionMatrix();
    }

    void setPerspective(PerspectiveParameters params) {
        cameraParams = params;
        computeProjectionMatrix();
    }

    void setAspectRatio(float aspectRatio) {
        this->aspectRatio = aspectRatio;
        computeProjectionMatrix();
    }

    void computeProjectionMatrix() {
        switch (type) {
        case Perspective: {
            auto parameters = std::get<PerspectiveParameters>(cameraParams);
            projectionMatrix = glm::perspective(glm::radians(parameters.fov), aspectRatio,
                                                parameters.near, parameters.far);
            break;
        }
        case Orthographic: {
            auto parameters = std::get<OrthographicParameters>(cameraParams);
            float base = parameters.size * 0.5f;
            projectionMatrix = glm::ortho(-base * aspectRatio, base * aspectRatio, -base, base,
                                          parameters.near, parameters.far);
            break;
        }
        }
    }

    const glm::mat4 &getProjectionMatrix() const { return projectionMatrix; }

    Type getType() const { return type; }
    OrthographicParameters &getOrthographicParameters() {
        return std::get<OrthographicParameters>(cameraParams);
    }
    PerspectiveParameters &getPerspectiveParameters() {
        return std::get<PerspectiveParameters>(cameraParams);
    }

private:
    Type type;
    glm::mat4 projectionMatrix;
    float aspectRatio;

    std::variant<OrthographicParameters, PerspectiveParameters> cameraParams;
};
} // namespace chert