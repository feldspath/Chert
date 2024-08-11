#include "Chert.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

class ExampleLayer : public chert::Layer {
public:
    void onAttach() override {
        float vertices[] = {
            -0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f, 0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f, 0.5f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f,
        };

        unsigned int indices[] = {0, 1, 2, 1, 2, 3};

        auto &renderContext = chert::Application::get().getRenderContext();
        chert::Ref<chert::VertexBuffer> vertexBuffer =
            renderContext->createVertexBuffer(vertices, sizeof(vertices));
        chert::Ref<chert::IndexBuffer> indexBuffer = renderContext->createIndexBuffer(indices, 6);

        chert::BufferLayout layout = {
            {chert::ShaderDataType::Float3, "a_Position"},
            {chert::ShaderDataType::Float3, "a_Normal"},
        };

        vertexBuffer->setLayout(layout);
        auto vertexArray = renderContext->createVertexArray();
        vertexArray->setIndexBuffer(indexBuffer);
        vertexArray->addVertexBuffer(vertexBuffer);

        // Create scene
        scene = std::make_shared<chert::Scene>();

        // Camera is not an entity
        scene->camera =
            std::make_shared<chert::PerspectiveCamera>(glm::vec3{0.0f, -5.0f, 0.0f}, glm::quat());

        // Create light
        chert::Entity light = scene->createEntity();
        light.addComponent<chert::DirLightComponent>(glm::vec3(0.0f, 1.0f, 0.0f),
                                                     glm::vec3(1.0f, 1.0f, 1.0f));

        // Create a mesh from vertex array
        chert::Entity mesh = scene->createEntity();
        mesh.addComponent<chert::MeshComponent>(vertexArray);
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