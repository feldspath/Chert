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
        vertexArray = renderContext->createVertexArray();
        vertexArray->setIndexBuffer(indexBuffer);
        vertexArray->addVertexBuffer(vertexBuffer);

        const auto &window = chert::Application::get().getWindow();
        camera = std::make_shared<chert::PerspectiveCamera>(glm::vec3{0.0f, -5.0f, 0.0f},
                                                            glm::quat(), window->aspectRatio());

        light = std::make_shared<chert::DirLight>(glm::vec3(0.0f, 1.0f, 0.0f),
                                                  glm::vec3(1.0f, 1.0f, 1.0f));
    }

    void onDetach() override {}

    void update(float timestep) override {
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

        auto &renderer = chert::Application::get().getRenderer();
        renderer->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        renderer->clear();
        renderer->beginScene(camera, {light});
        renderer->submit(vertexArray, renderer->defaultShader);
        renderer->endScene();
    }

    void renderGui() override {
        // ImGui::ColorEdit3("Light Color", glm::value_ptr(light->color));
        // ImGui::SliderFloat3("Light Direction", glm::value_ptr(light->direction), -1.0f, 1.0f);
        static bool showDemo = true;
        ImGui::ShowDemoWindow(&showDemo);
    }

    bool onWindowResize(const chert::WindowResizeEvent &e) {
        const auto &window = chert::Application::get().getWindow();
        camera->setAspectRatio(window->aspectRatio());
        return true;
    }

    void onEvent(chert::Event &e) override {
        chert::EventDispatcher dispatcher(e);
        dispatcher.dispatch<chert::WindowResizeEvent>(
            CHERT_BIND_EVENT_FN(ExampleLayer::onWindowResize));
    }

private:
    chert::Ref<chert::VertexArray> vertexArray;
    chert::Ref<chert::Camera> camera;
    chert::Ref<chert::DirLight> light;
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