#pragma once

#include "Chert/Scene/Model/Model.h"

namespace chert {
struct MeshComponent {
    MeshComponent() = default;
    MeshComponent(Ref<Model> model) : model(model) {}
    Ref<Model> model;
};
} // namespace chert