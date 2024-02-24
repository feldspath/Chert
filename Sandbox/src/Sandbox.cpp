#include "Chert.h"

class Sandbox : public chert::Application {

};

chert::Application* chert::CreateApplication() {
    CHERT_DEBUG("Creating application");
    return new Sandbox();
}