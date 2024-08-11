#include "Chert.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

class ExampleLayer : public chert::Layer {
public:
    void onAttach() override {
        // Create scene
        scene = chert::makeRef<chert::Scene>();

        // Camera is not an entity
        scene->camera =
            chert::makeRef<chert::PerspectiveCamera>(glm::vec3{0.0f, -5.0f, 0.0f}, glm::quat());

        // Create light
        chert::Entity light = scene->createEntity();
        light.addComponent<chert::DirLightComponent>(glm::vec3(0.0f, 1.0f, 0.0f),
                                                     glm::vec3(1.0f, 1.0f, 1.0f));

        // Load object from file
        chert::Ref<chert::Model> model =
            chert::ResourceManager::loadModel("Sandbox/assets/monke.obj");

        // Create a mesh from obj file
        chert::Entity mesh = scene->createEntity();
        mesh.addComponent<chert::MeshComponent>(model);
    }

    void onDetach() override {}

    void update(float timestep) override {
        auto &camera = scene->camera;
        float speed = 3.0f;
        if (chert::Input::isKeyPressed(CHERT_KEY_W)) {
            camera->position.y += speed * timestep;
        }
        if (chert::Input::isKeyPressed(CHERT_KEY_S)) {
            camera->position.y -= speed * timestep;
        }
        if (chert::Input::isKeyPressed(CHERT_KEY_D)) {
            camera->position.x += speed * timestep;
        }
        if (chert::Input::isKeyPressed(CHERT_KEY_A)) {
            camera->position.x -= speed * timestep;
        }

        scene->update();
    }

    void renderGui() override {
        // ImGui::ColorEdit3("Light Color", glm::value_ptr(light->color));
        // ImGui::SliderFloat3("Light Direction", glm::value_ptr(light->direction), -1.0f, 1.0f);
        static bool showDemo = true;
        ImGui::ShowDemoWindow(&showDemo);
    }

    bool onWindowResize(const chert::WindowResizeEvent &e) {
        const auto &window = chert::Application::get().getWindow();
        scene->camera->setAspectRatio(window->aspectRatio());
        return true;
    }

    void onEvent(chert::Event &e) override {
        chert::EventDispatcher dispatcher(e);
        dispatcher.dispatch<chert::WindowResizeEvent>(
            CHERT_BIND_EVENT_FN(ExampleLayer::onWindowResize));
    }

private:
    chert::Ref<chert::Scene> scene;
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