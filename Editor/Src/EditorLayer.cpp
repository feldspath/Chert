#include "EditorLayer.h"

namespace chert {

class CameraController : public NativeScript {
public:
    void onUpdate(float timestep) override {
        auto &transform = getComponent<TransformComponent>();
        float speed = 3.0f;
        if (Input::isKeyPressed(CHERT_KEY_W)) {
            transform.position += speed * timestep * transform.front();
        }
        if (Input::isKeyPressed(CHERT_KEY_S)) {
            transform.position -= speed * timestep * transform.front();
        }
        if (Input::isKeyPressed(CHERT_KEY_D)) {
            transform.position += speed * timestep * transform.right();
        }
        if (Input::isKeyPressed(CHERT_KEY_A)) {
            transform.position -= speed * timestep * transform.right();
        }
    }
};
void EditorLayer::onAttach() {
    // Create scene
    scene = makeRef<Scene>();

    // Create camera
    scene->camera = scene->createEntity("Camera");
    auto &cameraComponent = scene->camera.addComponent<CameraComponent>();
    cameraComponent.camera.setType(Camera::Type::Perspective);
    cameraComponent.camera.setAspectRatio(Application::get().getWindow()->aspectRatio());
    scene->camera.getComponent<TransformComponent>().position = glm::vec3{0.0f, -5.0f, 0.0f};
    scene->camera.addComponent<NativeScriptComponent>().bind<CameraController>();

    // Create light
    Entity light = scene->createEntity("Light");
    light.addComponent<DirLightComponent>(glm::vec3(0.0f, 1.0f, 0.0f));

    // Load object from file
    Ref<Model> model = ResourceManager::loadModel("Editor/Assets/Models/monke.obj");

    // Create a mesh from obj file
    mesh = scene->createEntity("Monke");
    mesh.addComponent<MeshComponent>(model);

    // Create scene hierarchy panel
    sceneHierarchyPanel = SceneHierarchyPanel(scene);

    // Create content browser panel
    contentBrowserPanel = ContentBrowserPanel(scene);
}

void EditorLayer::update(float timestep) { scene->update(timestep); }

void EditorLayer::renderGui() {
    static bool showDemo = true;
    ImGui::ShowDemoWindow(&showDemo);
    sceneHierarchyPanel.render();
    contentBrowserPanel.render();
}

bool EditorLayer::onWindowResize(const WindowResizeEvent &e) {
    const auto &window = Application::get().getWindow();
    scene->camera.getComponent<CameraComponent>().camera.setAspectRatio(window->aspectRatio());
    return true;
}

bool EditorLayer::onMouseScrolled(const MouseScrolledEvent &e) {
    scene->camera.getComponent<TransformComponent>().position *=
        1.0f - (float)e.getYOffset() * 0.08f;
    return true;
}

bool EditorLayer::onMouseMoved(const MouseMovedEvent &e) {
    if (Input::isMouseButtonPressed(1)) {
        double dx = (e.getMouseX() - previousMouseX) * 0.3f;
        double dy = (e.getMouseY() - previousMouseY) * 0.3f;
        auto &cameraTransform = scene->camera.getComponent<TransformComponent>();

        glm::vec3 up{0.0f, 0.0f, 1.0f};
        if (cameraTransform.up().z < 0.0f) {
            // Invert up vector if camera is upside down
            up *= -1.0f;
        }

        auto rotation = glm::mat4(glm::rotate(glm::mat4(1.0f), glm::radians(-(float)dx), up));

        auto right = glm::normalize(glm::cross(cameraTransform.position, up));
        rotation = glm::rotate(rotation, glm::radians((float)dy), right);
        cameraTransform.position = glm::mat3(rotation) * cameraTransform.position;
        cameraTransform.rotation = glm::quat(rotation) * cameraTransform.rotation;
    }
    previousMouseX = e.getMouseX();
    previousMouseY = e.getMouseY();
    return true;
}

void EditorLayer::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowResizeEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onWindowResize));
    dispatcher.dispatch<MouseScrolledEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onMouseScrolled));
    dispatcher.dispatch<MouseMovedEvent>(CHERT_BIND_EVENT_FN(EditorLayer::onMouseMoved));
}
} // namespace chert