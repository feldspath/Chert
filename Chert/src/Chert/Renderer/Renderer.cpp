#include "Renderer.h"
#include "Buffers/BufferLayout.h"
#include "RenderAPI.h"

namespace chert {
Renderer::Renderer(std::shared_ptr<RenderingContext> context)
    : context(context) {
    std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 viewProjectionMatrix;

            void main() {
                gl_Position = viewProjectionMatrix * vec4(a_Position, 1.0);
            }
        )";

    std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            void main() {
                color = vec4(0.1, 0.6, 0.3, 1.0);
            }
        )";

    shader = context->createShader(vertexSrc, fragmentSrc);
}

void Renderer::setClearColor(const glm::vec4 &color) {
    RenderAPI::setClearColor(color);
}

void Renderer::clear() { RenderAPI::clear(); }

void Renderer::beginScene(const Camera &camera) {
    CHERT_ASSERT(!sceneInProgress, "Scene already in progress, call endScene "
                                   "before calling beginScene again");
    shader->bind();
    sceneData.viewProjectionMatrix = camera.getViewProjectionMatrix();
    shader->setUniform("viewProjectionMatrix", sceneData.viewProjectionMatrix);
    sceneInProgress = true;
}

void Renderer::endScene() {
    CHERT_ASSERT(
        sceneInProgress,
        "Scene not in progress, call beginScene to start rendering a scene");
    sceneInProgress = false;
}

void Renderer::submit(std::shared_ptr<VertexArray> &vertexArray) {
    vertexArray->bind();
    RenderAPI::drawIndexed(vertexArray);
}
} // namespace chert