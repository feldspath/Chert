#include "OpenGLContext.h"
#include "Buffers/OpenGLIndexBuffer.h"
#include "Buffers/OpenGLVertexArray.h"
#include "Buffers/OpenGLVertexBuffer.h"
#include "Chert/Core/Core.h"
#include "OpenGLShader.h"
// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#define GET_OPENGL_STRING(name) std::string(reinterpret_cast<const char *>(glGetString(name)))

namespace chert {
OpenGLContext::OpenGLContext(GLFWwindow *window) : window(window) {}

void OpenGLContext::init() {
    glfwMakeContextCurrent(window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    CHERT_CORE_ASSERT(status, "Failed to initialized GLAD");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto vendor = GET_OPENGL_STRING(GL_VENDOR);
    auto version = GET_OPENGL_STRING(GL_VERSION);
    auto renderer = GET_OPENGL_STRING(GL_RENDERER);
    auto glslVersion = GET_OPENGL_STRING(GL_SHADING_LANGUAGE_VERSION);

    CHERT_CORE_INFO(R"(OpenGL info: 
    Vendor:         {}
    Renderer:       {}
    OpenGL version: {}
    GLSL version:   {})",
                    vendor, renderer, version, glslVersion);

    glEnable(GL_DEPTH_TEST);
}

void OpenGLContext::swapBuffers() { glfwSwapBuffers(window); }

Ref<Shader>
OpenGLContext::createShader(const std::array<std::string, Shader::shaderTypeCount()> &sources) {

    return std::make_shared<OpenGLShader>(sources);
}

Ref<Shader> OpenGLContext::createShader(const std::string &shaderFilePath) {
    return std::make_shared<OpenGLShader>(shaderFilePath);
}

Ref<VertexBuffer> OpenGLContext::createVertexBuffer(float *vertices, unsigned int size) {
    return std::make_shared<OpenGLVertexBuffer>(vertices, size);
}

Ref<IndexBuffer> OpenGLContext::createIndexBuffer(unsigned int *indices, unsigned int count) {
    return std::make_shared<OpenGLIndexBuffer>(indices, count);
}

Ref<VertexArray> OpenGLContext::createVertexArray() {
    return std::make_shared<OpenGLVertexArray>();
}
} // namespace chert