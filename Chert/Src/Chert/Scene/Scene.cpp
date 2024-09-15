#include "Scene.h"
#include "Chert/Core/Application.h"
#include "Chert/Scene/Components/Camera.h"
#include "Components/Light.h"
#include "Components/Mesh.h"
#include "Components/NativeScript.h"
#include "Components/Tag.h"
#include "Components/Transform.h"
#include "Entity/Entity.h"

namespace chert {
Entity Scene::createEntity(const std::string &name) {
    Entity entity(registry.create(), weak_from_this());
    entity.addComponent<TransformComponent>();
    entity.addComponent<TagComponent>(name);
    return entity;
}

void Scene::destroyEntity(Entity entity) { registry.destroy(entity.handle); }

void Scene::update(float timestep) {
    {
        auto view = registry.view<NativeScriptComponent>();
        for (auto &entity : view) {
            auto &script = view.get<NativeScriptComponent>(entity);
            // TODO: remove this
            if (!script.script) {
                script.script = script.instantiateScript();
                script.script->entity = {entity, weak_from_this()};
            }
            script.script->onUpdate(timestep);
        }
    }

    auto &renderer = Application::get().getRenderer();
    renderer->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    renderer->clear();

    // Passing the camera
    CHERT_ASSERT(camera.isInitialized(), "Scene camera is not set");
    auto &cameraProjection = camera.getComponent<CameraComponent>().camera.getProjectionMatrix();
    auto &cameraTransform = camera.getComponent<TransformComponent>();
    auto cameraView = glm::inverse(cameraTransform.modelMatrix() *
                                   glm::toMat4(TransformComponent::rotateZupToYup()));
    renderer->beginScene(cameraProjection * cameraView);

    // Passing the lights
    registry.view<DirLightComponent, TransformComponent>().each(
        [&](auto entityID, auto &light, auto &transform) {
            renderer->submitLight(light, transform);
        });

    // Passing the meshes
    auto meshesView = registry.view<TransformComponent, MeshComponent>();
    for (auto &entity : meshesView) {
        auto [transform, mesh] = meshesView.get<TransformComponent, MeshComponent>(entity);
        renderer->submitModel(mesh.model, renderer->defaultShader, transform.modelMatrix());
    }

    renderer->endScene();
}
} // namespace chert