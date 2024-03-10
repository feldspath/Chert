#include "Chert.h"

class TestLayer : public chert::Layer {
public:
    void onEvent(chert::Event& e) override {
    }
    void onAttach() override {
    }
    void onDetach() override {
    }
    void update() override {
    }
};
class Sandbox : public chert::Application {
private:
    std::shared_ptr<TestLayer> testLayer;
public:
    Sandbox() : chert::Application(chert::WindowProps()) {}

    ~Sandbox() {
        detachLayer(testLayer);
    }

    void init() override {
        testLayer = std::make_shared<TestLayer>();
        pushLayer(testLayer);
    }
};

std::unique_ptr<chert::Application> chert::createApplication() {
    return std::make_unique<Sandbox>();
}