#pragma once

#include <memory>

#include "Chert/Scene/Camera.h"
#include "Chert/Scene/Components/Light.h"
#include "RenderingContext.h"
#include "glm/glm.hpp"

#define CHERT_MAX_DIR_LIGHT (size_t)10

namespace chert {
class Scene;

class Renderer {
public:
    Renderer(std::shared_ptr<RenderingContext> context);

    void setClearColor(const glm::vec4 &color);
    void clear();
    void beginScene(const Ref<Scene> scene);
    void endScene();
    void submit(Ref<VertexArray> &vertexArray, Ref<Shader> &shader,
                glm::mat4 tranform = glm::mat4(1.0f));
    void onWindowResize(const WindowResizeEvent &e);

    inline std::shared_ptr<RenderingContext> &getRenderContext() { return context; }

    Ref<Shader> defaultShader;

private:
    std::shared_ptr<RenderingContext> context;
    bool sceneInProgress = false;

    struct SceneData {
        glm::mat4 viewProjectionMatrix;
        std::vector<DirLightComponent> dirLights;
    };

    SceneData sceneData;
};
} // namespace chert
