#pragma once

#include "Chert.h"
#include "Panels/ContentBrowserPanel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

namespace chert {
class EditorLayer : public Layer {
public:
    void onAttach() override;
    void onDetach() override {}
    void update(float timestep) override;
    void renderGui() override;
    bool onWindowResize(const WindowResizeEvent &e);
    bool onMouseScrolled(const MouseScrolledEvent &e);
    bool onMouseMoved(const MouseMovedEvent &e);
    void onEvent(Event &e) override;

private:
    Ref<Scene> scene;
    Entity mesh;

    SceneHierarchyPanel sceneHierarchyPanel;
    ContentBrowserPanel contentBrowserPanel;

    double previousMouseX = 0.0;
    double previousMouseY = 0.0;
};
} // namespace chert