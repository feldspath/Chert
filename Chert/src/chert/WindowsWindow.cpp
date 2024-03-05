#include "Chert/Events/ApplicationEvent.h"
#include "Chert/Events/KeyEvent.h"
#include "Chert/Events/MouseEvent.h"
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
        glfwSetWindowUserPointer(window, &data);

        // GLFW callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;

            Event e = WindowResizeEvent(width, height);
            data.eventCallback(e);
            });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            Event e = WindowCloseEvent();
            data.eventCallback(e);
            });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            Event e = MouseMovedEvent(xpos, ypos);
            data.eventCallback(e);
            });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                Event e = MouseButtonPressedEvent(button);
                data.eventCallback(e);
                break;
            }
            case GLFW_RELEASE:
            {
                Event e = MouseButtonReleasedEvent(button);
                data.eventCallback(e);
                break;
            }
            default:
                break;
            }
            });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                Event e = KeyPressedEvent(key);
                data.eventCallback(e);
                break;
            }
            case GLFW_RELEASE:
            {
                Event e = KeyReleasedEvent(key);
                data.eventCallback(e);
                break;
            }
            default:
                break;
            }
            });
    }

    void WindowsWindow::shutdown() {
        glfwTerminate();
    }
}