#pragma once

#include <memory>
#include "RenderingContext.h"

namespace chert {
    class Renderer {
    public:
        Renderer(std::shared_ptr<RenderingContext> context);
        void render();

    private:
        std::shared_ptr<RenderingContext> context;
        std::unique_ptr<Shader> shader;

        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;
    };
}