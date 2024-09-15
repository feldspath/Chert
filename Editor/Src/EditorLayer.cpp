#include "EditorLayer.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

namespace chert {
void EditorLayer::onAttach() {
    // Create scene
    scene = makeRef<Scene>();

    // Create camera
    scene->camera = scene->createEntity("Camera");
    auto &cameraComponent = scene->camera.addComponent<CameraComponent>();
    cameraComponent.camera.setAspectRatio(Application::get().getWindow()->aspectRatio());
    scene->camera.getComponent<TransformComponent>().position = glm::vec3{0.0f, -5.0f, 0.0f};

    // Create light
    Entity light = scene->createEntity("Light");
    light.addComponent<DirLightComponent>(glm::vec3(0.0f, 1.0f, 0.0f));

    // Load object from file
    Ref<Model> model = ResourceManager::loadModel("Editor/Assets/Models/monke.obj");

    // Create a mesh from obj file
    auto mesh = scene->createEntity("Monke");
    mesh.addComponent<MeshComponent>(model);

    // Create scene hierarchy panel
    sceneHierarchyPanel = SceneHierarchyPanel(scene);

    // Create content browser panel
    contentBrowserPanel = ContentBrowserPanel(scene);

    // Init editor camera
    editorCamera.setAspectRatio(Application::get().getWindow()->aspectRatio());
}

void EditorLayer::update(float timestep) { scene->updateEditor(timestep, editorCamera); }

void EditorLayer::renderGui() {
    static bool showDemo = true;
    ImGui::ShowDemoWindow(&showDemo);
    sceneHierarchyPanel.render();
    contentBrowserPanel.render();
}

bool EditorLayer::onWindowResize(const WindowResizeEvent &e) {
    const auto &window = Application::get().getWindow();
    editorCamera.setAspectRatio(window->aspectRatio());
    return true;
}

bool EditorLayer::onMouseScrolled(const MouseScrolledEvent &e) {
    editorCamera.onMouseScrolled(e);
    return true;
}

bool EditorLayer::onMouseMoved(const MouseMovedEvent &e) {
    editorCamera.onMouseMoved(e);
    return true;
}

void EditorLayer::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowResizeEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onWindowResize));
    dispatcher.dispatch<MouseScrolledEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onMouseScrolled));
    dispatcher.dispatch<MouseMovedEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onMouseMoved));
}
} // namespace chert