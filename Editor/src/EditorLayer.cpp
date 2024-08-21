#include "EditorLayer.h"

namespace chert {
void EditorLayer::onAttach() {
    // Create scene
    scene = makeRef<Scene>();

    // Camera is not an entity
    // scene->camera = makeRef<PerspectiveCamera>(
    //    glm::vec3{0.0f, -5.0f, 0.0f}, glm::quat_identity<float, glm::defaultp>());
    scene->camera =
        makeRef<PerspectiveCamera>(glm::vec3{0.0f, -5.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f});

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

void EditorLayer::update(float timestep) {
    auto &camera = scene->camera;
    float speed = 3.0f;
    if (Input::isKeyPressed(CHERT_KEY_W)) {
        camera->transform.position += speed * timestep * camera->transform.front();
    }
    if (Input::isKeyPressed(CHERT_KEY_S)) {
        camera->transform.position -= speed * timestep * camera->transform.front();
    }
    if (Input::isKeyPressed(CHERT_KEY_D)) {
        camera->transform.position += speed * timestep * camera->transform.right();
    }
    if (Input::isKeyPressed(CHERT_KEY_A)) {
        camera->transform.position -= speed * timestep * camera->transform.right();
    }

    scene->update();
}

void EditorLayer::renderGui() {
    static bool showDemo = true;
    ImGui::ShowDemoWindow(&showDemo);
    sceneHierarchyPanel.render();
    contentBrowserPanel.render();
}

bool EditorLayer::onWindowResize(const WindowResizeEvent &e) {
    const auto &window = Application::get().getWindow();
    scene->camera->setAspectRatio(window->aspectRatio());
    return true;
}

bool EditorLayer::onMouseScrolled(const MouseScrolledEvent &e) {
    scene->camera->transform.position *= 1.0f - (float)e.getYOffset() * 0.08f;
    return true;
}

bool EditorLayer::onMouseMoved(const MouseMovedEvent &e) {
    if (Input::isMouseButtonPressed(1)) {
        double dx = (e.getMouseX() - previousMouseX) * 0.3f;
        double dy = (e.getMouseY() - previousMouseY) * 0.3f;
        auto &camera = scene->camera;

        glm::vec3 up{0.0f, 0.0f, 1.0f};
        if (camera->transform.up().z < 0.0f) {
            // Invert up vector if camera is upside down
            up *= -1.0f;
        }

        auto rotation = glm::mat4(glm::rotate(glm::mat4(1.0f), glm::radians(-(float)dx), up));

        auto right = glm::normalize(glm::cross(camera->transform.position, up));
        rotation = glm::rotate(rotation, glm::radians((float)dy), right);
        camera->transform.position = glm::mat3(rotation) * camera->transform.position;
        camera->transform.rotation = glm::quat(rotation) * camera->transform.rotation;
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