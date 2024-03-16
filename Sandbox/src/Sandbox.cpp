#include "Chert.h"

class ExampleLayer : public chert::Layer {
public:
    void onEvent(chert::Event &e) override {}

    void onAttach() override {
        float vertices[] = {
            -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, -0.5f,
            -0.5f, 0.0f, 0.5f,  0.5f, 0.0f, 0.5f,
        };

        unsigned int indices[] = {0, 1, 2, 1, 2, 3};

        auto &renderContext = chert::Application::getRenderContext();
        chert::Ref<chert::VertexBuffer> vertexBuffer =
            renderContext->createVertexBuffer(vertices, sizeof(vertices));
        chert::Ref<chert::IndexBuffer> indexBuffer =
            renderContext->createIndexBuffer(indices, 6);

        chert::BufferLayout layout = {
            {chert::ShaderDataType::Float3, "a_Position"},
        };

        vertexBuffer->setLayout(layout);
        vertexArray = renderContext->createVertexArray();
        vertexArray->setIndexBuffer(indexBuffer);
        vertexArray->addVertexBuffer(vertexBuffer);

        camera = std::make_shared<chert::PerspectiveCamera>(
            glm::vec3{0.0f, -5.0f, 0.0f}, glm::quat());
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

        auto &renderer = chert::Application::getRenderer();
        renderer->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        renderer->clear();
        renderer->beginScene(camera);
        renderer->submit(vertexArray, renderer->defaultShader);
        renderer->endScene();
    }

private:
    chert::Ref<chert::VertexArray> vertexArray;
    chert::Ref<chert::Camera> camera;
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