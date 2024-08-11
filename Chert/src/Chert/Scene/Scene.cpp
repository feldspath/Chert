#include "Scene.h"
#include "Chert/Core/Application.h"
#include "Components/Light.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"
#include "Entity/Entity.h"

namespace chert {
Entity Scene::createEntity() {
    Entity entity(registry.create(), weak_from_this());
    entity.addComponent<TransformComponent>();
    return entity;
}

void Scene::update() {
    auto &renderer = Application::get().getRenderer();
    renderer->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    renderer->clear();
    renderer->beginScene(shared_from_this());

    auto meshesView = registry.view<TransformComponent, MeshComponent>();
    for (auto &entity : meshesView) {
        auto [transform, mesh] = meshesView.get<TransformComponent, MeshComponent>(entity);
        renderer->submit(mesh.model, renderer->defaultShader);
    }

    renderer->endScene();
}
} // namespace chert