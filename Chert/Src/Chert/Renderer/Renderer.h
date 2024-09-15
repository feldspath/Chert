#pragma once

#include <memory>

#include "Chert/Core/Core.h"
#include "Chert/Scene/Components/Light.h"
#include "Chert/Scene/Components/Transform.h"
#include "Chert/Scene/Model/Model.h"
#include "RenderingContext.h"

#define CHERT_MAX_DIR_LIGHT (size_t)10

namespace chert {
class Scene;

class Renderer {
public:
    Renderer(std::shared_ptr<RenderingContext> context);

    void setClearColor(const glm::vec4 &color);
    void clear();
    void beginScene(const glm::mat4 &viewProjectionMatrix);
    void submitLight(const DirLightComponent &light, const TransformComponent &transform);
    void endScene();
    void submitModel(Ref<Model> &vertexArray, Ref<Shader> &shader, const glm::mat4 &transform);
    void onWindowResize(const WindowResizeEvent &e);

    inline std::shared_ptr<RenderingContext> &getRenderContext() { return context; }

    Ref<Shader> defaultShader;

private:
    std::shared_ptr<RenderingContext> context;
    bool sceneInProgress = false;

    struct SceneData {
        glm::mat4 viewProjectionMatrix;
        std::vector<std::pair<DirLightComponent, TransformComponent>> dirLights;
    };

    SceneData sceneData;
};
} // namespace chert
