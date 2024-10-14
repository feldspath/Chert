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

void EditorLayer::update(float timestep) {

    auto &renderer = Application::get().getRenderer();
    renderer->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    renderer->clear();

    switch (sceneState) {
    case chert::EditorLayer::Edit: {
        editorCamera.onUpdate(timestep);
        scene->updateEditor(renderer, timestep, editorCamera);
        break;
    }
    case chert::EditorLayer::Play: {
        scene->updateRuntime(renderer, timestep);
        break;
    }
    default:
        break;
    }
}

void EditorLayer::renderGui() {
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    // Menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                Application::get().close();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    static bool showDemo = true;
    ImGui::ShowDemoWindow(&showDemo);

    sceneHierarchyPanel.render();
    contentBrowserPanel.render();

    static char *stopText = "Stop";
    static char *startText = "Start";

    ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_NoDecoration);
    if (ImGui::Button(sceneState == Edit ? startText : stopText)) {
        switch (sceneState) {
        case chert::EditorLayer::Edit: {
            // start playing scene
            sceneState = Play;
            break;
        }
        case chert::EditorLayer::Play: {
            // stop scene
            sceneState = Edit;
            break;
        }
        default:
            break;
        }
    }
    ImGui::End();
}

bool EditorLayer::onWindowResize(const WindowResizeEvent &e) {
    const auto &window = Application::get().getWindow();
    if (sceneState == Edit) {
        editorCamera.setAspectRatio(window->aspectRatio());
    }
    return true;
}

bool EditorLayer::onMouseScrolled(const MouseScrolledEvent &e) {
    if (sceneState == Edit) {
        editorCamera.onMouseScrolled(e);
    }
    return true;
}

bool EditorLayer::onMouseMoved(const MouseMovedEvent &e) {
    if (sceneState == Edit) {
        editorCamera.onMouseMoved(e);
    }
    return true;
}

void EditorLayer::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowResizeEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onWindowResize));
    dispatcher.dispatch<MouseScrolledEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onMouseScrolled));
    dispatcher.dispatch<MouseMovedEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onMouseMoved));

    if (sceneState == Play) {
        scene->onEvent(e);
    }
}
} // namespace chert