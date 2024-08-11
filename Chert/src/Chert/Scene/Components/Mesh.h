#pragma once

#include "Chert/Renderer/Buffers/VertexArray.h"

namespace chert {
struct MeshComponent {
    MeshComponent() = default;
    MeshComponent(Ref<VertexArray> vertexArray) : vertexArray(vertexArray) {}
    Ref<VertexArray> vertexArray;
};
} // namespace chert