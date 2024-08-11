#pragma once

#include "Chert/Core/Core.h"
#include "Chert/Scene/Scene.h"
#include "entt/entt.hpp"
#include <memory>

namespace chert {
class Entity {
public:
    Entity() = default;
    Entity(entt::entity entityHandle, std::weak_ptr<Scene> scene)
        : handle(entityHandle), scene(scene) {}

    template <typename T, typename... Args> T &addComponent(Args &&...args) {
        auto sceneRef = scene.lock();
        CHERT_ASSERT(!hasComponent<T>(),
                     "The entity already has the component, cannot add it multiple times");
        return sceneRef->registry.emplace<T>(handle, std::forward<Args>(args)...);
    }

    template <typename T> void removeComponent() {
        auto sceneRef = scene.lock();
        CHERT_ASSERT(hasComponent<T>(), "The entity does not have the component, cannot remove it");
        sceneRef->registry.remove<T>(handle);
    }

    template <typename T> bool hasComponent() { return scene.lock()->registry.all_of<T>(handle); }

private:
    entt::entity handle = entt::null;
    std::weak_ptr<Scene> scene;
};
} // namespace chert