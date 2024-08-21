#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Mesh.h"

namespace chert {
class Model {
    friend class ResourceManager;

public:
    Model() = default;

    void addMesh(Ref<Mesh> mesh) { meshes.push_back(mesh); }
    const std::vector<Ref<Mesh>> &getMeshes() const { return meshes; }
    std::filesystem::path getPath() const { return path; }

private:
    std::vector<Ref<Mesh>> meshes;
    std::filesystem::path path;
};
} // namespace chert