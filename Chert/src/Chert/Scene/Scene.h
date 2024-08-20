#pragma once

#include <memory>

#include "Chert/Core/Core.h"
#include "Chert/Scene/Camera.h"
#include "entt/entt.hpp"

namespace chert {
class Entity;

class Scene : public std::enable_shared_from_this<Scene> {
    friend class Entity;
    friend class Renderer;
    friend class SceneHierarchyPanel;

public:
    Entity createEntity(const std::string &name = "UnnamedEntity");
    void update();

    Ref<Camera> camera;

private:
    entt::registry registry;
};

} // namespace chert