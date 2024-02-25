#include "Chert/Application.h"
#include "Chert/Log.h"
#include "Chert/Events/ApplicationEvent.h"

#include "GLFW/glfw3.h"

namespace chert {
    Application::Application() {
        window = std::unique_ptr<Window>(Window::create());
    }

    Application::Application(WindowProps windowProps) {
        window = std::unique_ptr<Window>(Window::create(windowProps));
    }

    void Application::run() {
        while (true) {
            glClearColor(0, 0.8, 0.5, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            window->update();
        }

    }
}