#include <algorithm>

#include "Buffers/BufferLayout.h"
#include "Chert/Events/Event.h"
#include "RenderAPI.h"
#include "Renderer.h"

#include "glm/gtc/type_ptr.hpp"

namespace chert {
Renderer::Renderer(std::shared_ptr<RenderingContext> context) : context(context) {
    std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Normal;

            uniform mat4 viewProjectionMatrix, modelMatrix;

            out vec3 normal;

            void main() {
                normal = normalize(vec3(modelMatrix * vec4(a_Normal, 0.0)));
                gl_Position = viewProjectionMatrix * modelMatrix * vec4(a_Position, 1.0);
            }
        )";

    std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec3 normal;

            struct LightDir {
                vec3 direction;
                vec3 color;
            };

            uniform LightDir dirLights[10];
            uniform int dirLightCount;

            void main() {
                vec3 lightSum = vec3(0.0);
                for (int i = 0; i < dirLightCount; ++i) {
                    lightSum += max(dot(normal, -normalize(dirLights[i].direction)), 0.0) * dirLights[i].color;
                }
                color = vec4(0.1, 0.6, 0.3, 1.0) * vec4(lightSum, 1.0);
            }
        )";

    defaultShader = context->createShader(vertexSrc, fragmentSrc);
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
    context->setViewport(0, 0, e.getWidth(), e.getHeight());
}
} // namespace chert