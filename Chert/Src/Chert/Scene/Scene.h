#pragma once

#include <memory>

#include "Chert/Core/Core.h"
#include "Chert/Renderer/EditorCamera.h"
#include "Chert/Scene/Entity/entity.h"
#include "entt/entt.hpp"

namespace chert {

class Scene : public std::enable_shared_from_this<Scene> {
    friend class Entity;
    friend class Renderer;
    friend class SceneHierarchyPanel;

public:
    Entity createEntity(const std::string &name = "Unnamed Entity");
    void destroyEntity(Entity entity);
    void updateRuntime(float timestep);
    void updateEditor(float timestep, const EditorCamera &editorCamera);

    Entity camera;

private:
    entt::registry registry;
};

} // namespace chert