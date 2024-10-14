#pragma once

#include <memory>

#include "Chert/Core/Core.h"
#include "Chert/Events/Event.h"
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
    void updateRuntime(std::shared_ptr<Renderer> &renderer, float timestep);
    void updateEditor(std::shared_ptr<Renderer> &renderer, float timestep,
                      const EditorCamera &editorCamera);
    void onEvent(const Event &event);

    Entity camera;

private:
    entt::registry registry;
};

} // namespace chert