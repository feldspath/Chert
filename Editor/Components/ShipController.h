#pragma once

#include "Chert.h"

using namespace chert;

struct CameraReference {
    Entity camera;

    CameraReference(Entity camera) : camera(camera) {}
};

class ShipController : public NativeScript {
private:
    glm::vec3 velocity;

public:
    float speed = 300.0f;

    void onCreate() override { velocity = {0.0f, 0.0f, 0.0f}; }

    void onUpdate(float timestep) override {
        auto &transform = getComponent<TransformComponent>();
        glm::vec3 acceleration = {0.0f, 0.0f, 0.0f};

        if (Input::isKeyPressed(CHERT_KEY_D)) {
            acceleration += speed * timestep * transform.front();
        }
        if (Input::isKeyPressed(CHERT_KEY_C)) {
            acceleration -= speed * timestep * transform.front();
        }
        if (Input::isKeyPressed(CHERT_KEY_F)) {
            acceleration += speed * timestep * transform.right();
        }
        if (Input::isKeyPressed(CHERT_KEY_S)) {
            acceleration -= speed * timestep * transform.right();
        }

        velocity += acceleration * timestep;
        transform.position += velocity * timestep;
        auto &camera = getComponent<CameraReference>().camera;
        camera.getComponent<TransformComponent>().position += velocity * timestep;
    }
};