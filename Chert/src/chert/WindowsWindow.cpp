#include "Chert/Log.h"
#include "WindowsWindow.h"

namespace chert {
    Window* Window::create(const WindowProps& props) {
        return new WindowsWindow(props);
    }

    static bool isGLFWInitialized = false;

    WindowsWindow::WindowsWindow(WindowProps props) {
        init(props);
    }

    WindowsWindow::~WindowsWindow() {
        shutdown();
    }

    void WindowsWindow::update() {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    unsigned int WindowsWindow::getWidth() const {
        return data.width;
    }
    unsigned int WindowsWindow::getHeight() const {
        return data.height;
    }

    void WindowsWindow::init(const WindowProps& props) {
        data.title = props.title;
        data.height = props.height;
        data.width = props.width;

        CHERT_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!isGLFWInitialized) {
            int success = glfwInit();
            CHERT_CORE_ASSERT(success, "Failed to initialized GLFW");
            isGLFWInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(props.width, props.height, props.title.c_str(), NULL, NULL);
        CHERT_CORE_ASSERT(window, "Failed to create GLFW window");

        glfwMakeContextCurrent(window);
    }

    void WindowsWindow::shutdown() {
        glfwTerminate();
    }
}