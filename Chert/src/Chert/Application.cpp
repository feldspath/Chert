#include "Chert/Application.h"
#include "Chert/Log.h"
#include "Chert/Events/ApplicationEvent.h"
#include "Chert/Input.h"

#include "glad/glad.h"

namespace chert {
    std::unique_ptr<Application> Application::instance;

    void Application::initApplication() {
        Log::init();
        CHERT_CORE_ASSERT(!instance, "Application is already initialized");
        CHERT_CORE_INFO("Lauching Chert...");
        instance = chert::createApplication();
        instance->Application::init();
        instance->init();
        Input::init();
    }

    Application::Application(WindowProps windowProps) {
        window = Window::create(windowProps);
        window->setEventCallback(CHERT_BIND_EVENT_FN(Application::onEvent));
    }

    void Application::init() {
        imguiLayer.init();

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
        };

        unsigned int indices[] = {
            0, 1, 2
        };

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;

            void main() {
                gl_Position = vec4(a_Position, 1.0);
            }

        )";

        std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            void main() {
                color = vec4(0.1, 0.6, 0.3, 1.0);
            }

        )";

        shader = window->getRenderingContext().createShader(vertexSrc, fragmentSrc);
        shader->bind();
    }

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(CHERT_BIND_EVENT_FN(Application::onWindowClose));

        for (auto layerIt = layerStack.end(); layerIt != layerStack.begin(); ) {
            (*--layerIt)->onEvent(e);
            bool handled = std::visit([](auto&& e) -> bool {
                return e.isHandled();
                }, e);
            if (handled) {
                break;
            }
        }
    }

    void Application::run() {
        while (running) {
            imguiLayer.begin();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            for (auto layer : layerStack) {
                layer->update();
            }
            imguiLayer.update();

            imguiLayer.end();

            window->update();
        }
    }

    bool Application::onWindowClose(const WindowCloseEvent& e) {
        running = false;
        return true;
    }

    void Application::pushLayer(std::shared_ptr<Layer> layer) {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(std::shared_ptr<Layer> overlay) {
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::detachLayer(std::shared_ptr<Layer> layer) {
        layer->onDetach();
        layerStack.detachLayer(layer);
    }

    void Application::detachOverlay(std::shared_ptr<Layer> overlay) {
        overlay->onDetach();
        layerStack.detachOverlay(overlay);
    }

}