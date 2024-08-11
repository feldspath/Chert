#include <algorithm>

#include "Buffers/BufferLayout.h"
#include "Chert/Events/Event.h"
#include "Chert/Scene/Components/Light.h"
#include "Chert/Scene/Components/Transform.h"
#include "Chert/Scene/Scene.h"
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

void Renderer::beginScene(const Ref<Scene> scene) {
    CHERT_ASSERT(!sceneInProgress, "Scene already in progress, call endScene "
                                   "before calling beginScene again");
    CHERT_ASSERT(scene->camera, "Scene camera is not set")
    sceneData.viewProjectionMatrix = scene->camera->getViewProjectionMatrix();

    // Copying all the DirLightComponents
    sceneData.dirLights.clear();
    auto lightsView = scene->registry.view<DirLightComponent>();
    for (auto lightEntity : lightsView) {
        auto &light = lightsView.get<DirLightComponent>(lightEntity);
        sceneData.dirLights.push_back(light);
    }
    if (CHERT_MAX_DIR_LIGHT < sceneData.dirLights.size()) {
        CHERT_CORE_WARN("Renderer only supports up to {} DirLights but {} were provided. Ignoring "
                        "the other ones.",
                        CHERT_MAX_DIR_LIGHT, sceneData.dirLights.size());
    }

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
        shader->setUniform("dirLights[" + std::to_string(i) + "].direction", dirLight.direction);
        shader->setUniform("dirLights[" + std::to_string(i) + "].color", dirLight.color);
        shader->setUniform("dirLights[" + std::to_string(i) + "].intensity", dirLight.intensity);
    }
    shader->setUniform("dirLightCount", dirLightCount);
    RenderAPI::drawIndexed(vertexArray);
}

void Renderer::onWindowResize(const WindowResizeEvent &e) {
    RenderAPI::setViewport(0, 0, e.getWidth(), e.getHeight());
}
} // namespace chert