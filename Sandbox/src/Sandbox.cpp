#include "Chert.h"

class Sandbox : public chert::Application {

};

chert::Application* chert::CreateApplication() {
    return new Sandbox();
}