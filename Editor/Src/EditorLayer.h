#pragma once

#include "Chert.h"
#include "Panels/ContentBrowserPanel.h"
#include "Panels/SceneHierarchyPanel.h"

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
    EditorCamera editorCamera;

    SceneHierarchyPanel sceneHierarchyPanel;
    ContentBrowserPanel contentBrowserPanel;

    enum SceneState {
        Edit,
        Play,
    } sceneState;
};
} // namespace chert