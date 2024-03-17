#pragma once

#include "Camera.h"
#include "RenderingContext.h"
#include "Scene/DirLight.h"
#include "glm/glm.hpp"
#include <memory>

#define CHERT_MAX_DIR_LIGHT (size_t)10

namespace chert {
class Renderer {
public:
    Renderer(std::shared_ptr<RenderingContext> context);

    void setClearColor(const glm::vec4 &color);
    void clear();
    void beginScene(const Ref<Camera> &camera, const std::vector<Ref<DirLight>> &dirLights);
    void endScene();
    void submit(Ref<VertexArray> &vertexArray, Ref<Shader> &shader,
                glm::mat4 tranform = glm::mat4(1.0f));

    inline std::shared_ptr<RenderingContext> &getRenderContext() { return context; }

    Ref<Shader> defaultShader;

private:
    std::shared_ptr<RenderingContext> context;
    bool sceneInProgress = false;

    struct SceneData {
        glm::mat4 viewProjectionMatrix;
        std::vector<Ref<DirLight>> dirLights;
    };

    SceneData sceneData;
};
} // namespace chert
