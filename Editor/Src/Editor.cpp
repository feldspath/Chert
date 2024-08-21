#include "Chert.h"
#include "Chert/Core/EntryPoint.h"
#include "EditorLayer.h"

class Sandbox : public chert::Application {
private:
    std::shared_ptr<chert::Layer> editorLayer;

public:
    Sandbox() : chert::Application(chert::WindowProps()) {}

    void init() override {
        editorLayer = std::make_shared<chert::EditorLayer>();
        pushLayer(editorLayer);
    }
};

std::unique_ptr<chert::Application> chert::createApplication() {
    return std::make_unique<Sandbox>();
}