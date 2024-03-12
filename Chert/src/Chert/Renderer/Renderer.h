#pragma once

#include <memory>
#include "glm/glm.hpp"
#include "RenderingContext.h"

namespace chert {
    class Renderer {
    public:
        Renderer(std::shared_ptr<RenderingContext> context);
        
        void setClearColor(const glm::vec4& color);
        void clear();
        void beginScene();
        void endScene();
        void submit(std::shared_ptr<VertexArray>& vertexArray);

        inline RenderingContext& getRenderContext() { return *context; }

    private:
        std::shared_ptr<RenderingContext> context;
        std::unique_ptr<Shader> shader;
        bool sceneInProgress = false;
    };
}
