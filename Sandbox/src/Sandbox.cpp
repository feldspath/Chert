#include "Chert.h"
#include "Panels/SceneHierarchyPanel.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

class ExampleLayer : public chert::Layer {
public:
    void onAttach() override {
        // Create scene
        scene = chert::makeRef<chert::Scene>();

        // Camera is not an entity
        // scene->camera = chert::makeRef<chert::PerspectiveCamera>(
        //    glm::vec3{0.0f, -5.0f, 0.0f}, glm::quat_identity<float, glm::defaultp>());
        scene->camera = chert::makeRef<chert::PerspectiveCamera>(glm::vec3{0.0f, -5.0f, 0.0f},
                                                                 glm::vec3{0.0f, 0.0f, 0.0f});

        // Create light
        chert::Entity light = scene->createEntity("light");
        light.addComponent<chert::DirLightComponent>(glm::vec3(0.0f, 1.0f, 0.0f));

        // Load object from file
        chert::Ref<chert::Model> model =
            chert::ResourceManager::loadModel("Sandbox/assets/monke.obj");

        // Create a mesh from obj file
        mesh = scene->createEntity("monke");
        mesh.addComponent<chert::MeshComponent>(model);

        // Create scene hierarchy panel
        sceneHierarchyPanel = chert::SceneHierarchyPanel(scene);
    }

    void onDetach() override {}

    void update(float timestep) override {
        auto &camera = scene->camera;
        float speed = 3.0f;
        if (chert::Input::isKeyPressed(CHERT_KEY_W)) {
            camera->transform.position.y += speed * timestep;
        }
        if (chert::Input::isKeyPressed(CHERT_KEY_S)) {
            camera->transform.position.y -= speed * timestep;
        }
        if (chert::Input::isKeyPressed(CHERT_KEY_D)) {
            camera->transform.position.x += speed * timestep;
        }
        if (chert::Input::isKeyPressed(CHERT_KEY_A)) {
            camera->transform.position.x -= speed * timestep;
        }

        scene->update();
    }

    void renderGui() override {
        static bool showDemo = true;
        ImGui::ShowDemoWindow(&showDemo);
        sceneHierarchyPanel.render();
    }

    bool onWindowResize(const chert::WindowResizeEvent &e) {
        const auto &window = chert::Application::get().getWindow();
        scene->camera->setAspectRatio(window->aspectRatio());
        return true;
    }

    bool onMouseScrolled(const chert::MouseScrolledEvent &e) {
        scene->camera->transform.position *= 1.0f - (float)e.getYOffset() * 0.08f;
        return true;
    }

    bool onMouseMoved(const chert::MouseMovedEvent &e) {
        if (chert::Input::isMouseButtonPressed(1)) {
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

    void onEvent(chert::Event &e) override {
        chert::EventDispatcher dispatcher(e);
        dispatcher.dispatch<chert::WindowResizeEvent>(
            CHERT_BIND_EVENT_FN(ExampleLayer::onWindowResize));
        dispatcher.dispatch<chert::MouseScrolledEvent>(
            CHERT_BIND_EVENT_FN(ExampleLayer::onMouseScrolled));
        dispatcher.dispatch<chert::MouseMovedEvent>(
            CHERT_BIND_EVENT_FN(ExampleLayer::onMouseMoved));
    }

private:
    chert::Ref<chert::Scene> scene;
    chert::Entity mesh;

    chert::SceneHierarchyPanel sceneHierarchyPanel;

    double previousMouseX = 0.0;
    double previousMouseY = 0.0;
};

class Sandbox : public chert::Application {
private:
    std::shared_ptr<ExampleLayer> layer;

public:
    Sandbox() : chert::Application(chert::WindowProps()) {}

    void init() override {
        layer = std::make_shared<ExampleLayer>();
        pushLayer(layer);
    }
};

std::unique_ptr<chert::Application> chert::createApplication() {
    return std::make_unique<Sandbox>();
}