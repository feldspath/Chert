#include "Chert.h"

class TestLayer : public chert::Layer {
public:
    void onEvent(chert::Event& e) override {
    }

    void onAttach() override {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
        };

        unsigned int indices[] = {
            0, 1, 2, 1, 2, 3
        };

        auto& renderContext = chert::Application::getRenderContext();
        std::shared_ptr<chert::VertexBuffer> vertexBuffer = renderContext.createVertexBuffer(vertices, sizeof(vertices));
        std::shared_ptr<chert::IndexBuffer> indexBuffer = renderContext.createIndexBuffer(indices, 6);

        chert::BufferLayout layout = {
            {chert::ShaderDataType::Float3, "a_Position"},
        };

        vertexBuffer->setLayout(layout);
        vertexArray = renderContext.createVertexArray();
        vertexArray->setIndexBuffer(indexBuffer);
        vertexArray->addVertexBuffer(vertexBuffer);
    }

    void onDetach() override {
    }

    void update() override {
        auto& renderer = chert::Application::getRenderer();

        renderer.setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        renderer.clear();
        renderer.beginScene();
        renderer.submit(vertexArray);
        renderer.endScene();
    }

private:
    std::shared_ptr<chert::VertexArray> vertexArray;
};

class Sandbox : public chert::Application {
private:
    std::shared_ptr<TestLayer> testLayer;
public:
    Sandbox() : chert::Application(chert::WindowProps()) {}

    void init() override {
        testLayer = std::make_shared<TestLayer>();
        pushLayer(testLayer);
    }
};

std::unique_ptr<chert::Application> chert::createApplication() {
    return std::make_unique<Sandbox>();
}