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
    void submit(std::shared_ptr<VertexArray> &vertexArray);

    inline RenderingContext &getRenderContext() { return *context; }

private:
    std::shared_ptr<RenderingContext> context;
    std::unique_ptr<Shader> shader;
    bool sceneInProgress = false;

    struct SceneData {
        glm::mat4 viewProjectionMatrix;
    };

    SceneData sceneData;
};
} // namespace chert
