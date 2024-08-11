#pragma once

#include <string>
#include <vector>

#include "Mesh.h"

namespace chert {
class Model {
public:
    Model() = default;

    void addMesh(Ref<Mesh> mesh) { meshes.push_back(mesh); }
    const std::vector<Ref<Mesh>> &getMeshes() const { return meshes; }

private:
    std::vector<Ref<Mesh>> meshes;
};
} // namespace chert