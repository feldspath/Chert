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

    inline void checkInitialization() {
        CHERT_ASSERT(isInitialized(), "The entity is not initialized");
    }

    inline bool isInitialized() { return handle != entt::null; }

    template <typename T, typename... Args> T &addComponent(Args &&...args) {
        checkInitialization();
        auto sceneRef = scene.lock();
        CHERT_ASSERT(!hasComponent<T>(),
                     "The entity already has the component, cannot add it multiple times");
        return sceneRef->registry.emplace<T>(handle, std::forward<Args>(args)...);
    }

    template <typename T> void removeComponent() {
        checkInitialization();
        auto sceneRef = scene.lock();
        CHERT_ASSERT(hasComponent<T>(), "The entity does not have the component, cannot remove it");
        sceneRef->registry.remove<T>(handle);
    }

    template <typename T> bool hasComponent() {
        checkInitialization();
        return scene.lock()->registry.all_of<T>(handle);
    }

    template <typename T> T &getComponent() {
        checkInitialization();
        auto sceneRef = scene.lock();
        CHERT_ASSERT(hasComponent<T>(), "The entity does not have the component");
        return sceneRef->registry.get<T>(handle);
    }

    inline uint32_t getID() {
        checkInitialization();
        return entt::entt_traits<entt::entity>::to_entity(handle);
    }

    inline bool operator==(const Entity &other) const { return handle == other.handle; }
    inline bool operator!=(const Entity &other) const { return handle != other.handle; }

    static Entity nullEntity() { return Entity(); }

private:
    entt::entity handle = entt::null;
    std::weak_ptr<Scene> scene;
};
} // namespace chert