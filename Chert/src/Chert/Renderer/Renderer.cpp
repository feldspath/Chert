#include <algorithm>

#include "Buffers/BufferLayout.h"
#include "Chert/Events/Event.h"
#include "RenderAPI.h"
#include "Renderer.h"

#include "glm/gtc/type_ptr.hpp"

namespace chert {
Renderer::Renderer(std::shared_ptr<RenderingContext> context) : context(context) {
    defaultShader = context->createShader("Sandbox/assets/default.glsl");
    sceneData.viewProjectionMatrix = glm::mat4();
}

void Renderer::setClearColor(const glm::vec4 &color) { RenderAPI::setClearColor(color); }

void Renderer::clear() { RenderAPI::clear(); }

void Renderer::beginScene(const Ref<Camera> &camera, const std::vector<Ref<DirLight>> &dirLights) {
    CHERT_ASSERT(!sceneInProgress, "Scene already in progress, call endScene "
                                   "before calling beginScene again");
    if (CHERT_MAX_DIR_LIGHT < sceneData.dirLights.size()) {
        CHERT_CORE_WARN("Renderer only supports up to {} DirLights but {} were provided. Ignoring "
                        "the other ones.",
                        CHERT_MAX_DIR_LIGHT, sceneData.dirLights.size());
    }
    sceneData.viewProjectionMatrix = camera->getViewProjectionMatrix();
    sceneData.dirLights = dirLights;
    sceneInProgress = true;
}

void Renderer::endScene() {
    CHERT_ASSERT(sceneInProgress,
                 "Scene not in progress, call beginScene to start rendering a scene");
    sceneInProgress = false;
}

void Renderer::submit(Ref<VertexArray> &vertexArray, Ref<Shader> &shader, glm::mat4 tranform) {
    vertexArray->bind();
    shader->bind();
    shader->setUniform("viewProjectionMatrix", sceneData.viewProjectionMatrix);
    shader->setUniform("modelMatrix", tranform);

    int dirLightCount = std::min(CHERT_MAX_DIR_LIGHT, sceneData.dirLights.size());
    for (int i = 0; i < dirLightCount; ++i) {
        const auto &dirLight = sceneData.dirLights[i];
        shader->setUniform("dirLights[" + std::to_string(i) + "].direction", dirLight->direction);
        shader->setUniform("dirLights[" + std::to_string(i) + "].color", dirLight->color);
    }
    shader->setUniform("dirLightCount", dirLightCount);
    RenderAPI::drawIndexed(vertexArray);
}

void Renderer::onWindowResize(const WindowResizeEvent &e) {
    RenderAPI::setViewport(0, 0, e.getWidth(), e.getHeight());
}
} // namespace chert