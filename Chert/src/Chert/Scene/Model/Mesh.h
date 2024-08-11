#pragma once

#include <string>

#include "Chert/Renderer/Buffers/VertexArray.h"

namespace chert {
class Mesh {
public:
    Mesh() = default;
    Mesh(Ref<VertexArray> vertexArray) : vertexArray(vertexArray) {}

    Ref<VertexArray> vertexArray;
};
} // namespace chert