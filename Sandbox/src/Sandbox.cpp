#include "Chert.h"

class TestLayer : public chert::Layer {
public:
    void onEvent(chert::Event& e) override {
        //CHERT_INFO(e);
    }
    void onAttach() override {
        CHERT_INFO("Attached layer");
    }
    void onDetach() override {
        CHERT_INFO("Detached layer");
    }
    void update() override {
        //CHERT_INFO("Update");
        CHERT_DEBUG("{0}, {1}", chert::Input::getMouseX(), chert::Input::getMouseY());
    }
};
class Sandbox : public chert::Application {
private:
    std::shared_ptr<TestLayer> testLayer;
    std::shared_ptr<chert::ImguiLayer> imguiLayer;
public:
    Sandbox() : chert::Application(chert::WindowProps()) {}

    ~Sandbox() {
        detachLayer(testLayer);
        detachOverlay(imguiLayer);
    }

    void init() override {
        testLayer = std::make_shared<TestLayer>();
        imguiLayer = std::make_shared<chert::ImguiLayer>();

        pushLayer(testLayer);
        pushOverlay(imguiLayer);
    }
};

std::unique_ptr<chert::Application> chert::createApplication() {
    return std::make_unique<Sandbox>();
}