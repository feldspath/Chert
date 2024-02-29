#include "Chert.h"

class TestLayer : public chert::Layer {
public:
    void onEvent(chert::Event& e) override {
        CHERT_INFO(e);
    }
    void onAttach() override {
        CHERT_INFO("Attached layer");
    }
    void onDetach() override {
        CHERT_INFO("Detached layer");
    }
    void update() override {
        //CHERT_INFO("Update");
    }
};
class Sandbox : public chert::Application {
public:
    Sandbox() : chert::Application(chert::WindowProps()) {
        pushLayer(std::make_shared<TestLayer>());
    }
};

chert::Application* chert::CreateApplication() {
    return new Sandbox();
}