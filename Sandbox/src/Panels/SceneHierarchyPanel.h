#pragma once

#include "Chert/Scene/Entity/Entity.h"
#include "Chert/Scene/Scene.h"

namespace chert {
class SceneHierarchyPanel {

public:
    SceneHierarchyPanel() = default;
    SceneHierarchyPanel(Ref<Scene> scene) : scene(scene) {}
    ~SceneHierarchyPanel() = default;

    void render();

private:
    void drawEntityNode(Entity entity);
    void displayComponents(Entity entity);

    Ref<Scene> scene;
    Entity selectionContext;
};
} // namespace chert