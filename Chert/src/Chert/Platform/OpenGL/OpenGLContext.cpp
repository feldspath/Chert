#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Chert/Core.h"
#include "OpenGLContext.h"

namespace chert {
    OpenGLContext::OpenGLContext(std::shared_ptr<GLFWwindow> window) : window(window) {}

    void OpenGLContext::init() {
        glfwMakeContextCurrent(window.get());
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CHERT_CORE_ASSERT(status, "Failed to initialized GLAD");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void OpenGLContext::swapBuffers() {
        glfwSwapBuffers(window.get());
    }
}