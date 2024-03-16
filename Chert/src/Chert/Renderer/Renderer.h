#pragma once

#include "Camera.h"
#include "RenderingContext.h"
#include "glm/glm.hpp"
#include <memory>

namespace chert {
class Renderer {
public:
    Renderer(std::shared_ptr<RenderingContext> context);

    void setClearColor(const glm::vec4 &color);
    void clear();
    void beginScene(const Camera &camera);
    void endScene();
    void submit(std::shared_ptr<VertexArray> &vertexArray,
                std::shared_ptr<Shader> shader,
                glm::mat4 tranform = glm::mat4(1.0f));

    inline RenderingContext &getRenderContext() { return *context; }

    std::shared_ptr<Shader> defaultShader;

private:
    std::shared_ptr<RenderingContext> context;
    bool sceneInProgress = false;

    struct SceneData {
        glm::mat4 viewProjectionMatrix;
    };

    SceneData sceneData;
};
} // namespace chert
