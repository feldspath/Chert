#include "Chert.h"

class Sandbox : public chert::Application {
public:
    Sandbox() : chert::Application(chert::WindowProps()) {}
};

chert::Application* chert::CreateApplication() {
    return new Sandbox();
}