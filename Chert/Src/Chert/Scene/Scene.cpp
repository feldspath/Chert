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

void Scene::updateRuntime(std::shared_ptr<Renderer> &renderer, float timestep) {
    // Update the scripts
    registry.view<NativeScriptComponent>().each([&](auto entity, auto &script) {
        // TODO: handle script instantiation properly
        if (!script.script) {
            script.script = script.instantiateScript();
            script.script->entity = {entity, weak_from_this()};
        }
        script.script->onUpdate(timestep);
    });

    // Passing the camera
    // TODO: handle this crash properly
    CHERT_ASSERT(camera.isInitialized(), "Scene camera is not set");
    auto &cameraProjection = camera.getComponent<CameraComponent>().camera.getProjectionMatrix();
    auto &cameraTransform = camera.getComponent<TransformComponent>();
    auto cameraView = glm::inverse(cameraTransform.modelMatrix() *
                                   glm::toMat4(TransformComponent::rotateZupToYup()));
    renderer->beginScene(cameraProjection * cameraView);

    // Passing the lights
    registry.view<DirLightComponent, TransformComponent>().each(
        [&](auto entity, auto &light, auto &transform) {
            renderer->submitLight(light, transform);
        });

    // Passing the meshes
    registry.view<TransformComponent, MeshComponent>().each(
        [&](auto entity, auto &transform, auto &mesh) {
            renderer->submitModel(mesh.model, renderer->defaultShader, transform.modelMatrix());
        });

    renderer->endScene();
}

void Scene::updateEditor(std::shared_ptr<Renderer> &renderer, float timestep,
                         const EditorCamera &editorCamera) {
    // Passing the camera
    renderer->beginScene(editorCamera.getViewProjectionMatrix());

    // Passing the lights
    registry.view<DirLightComponent, TransformComponent>().each(
        [&](auto entityID, auto &light, auto &transform) {
            renderer->submitLight(light, transform);
        });

    // Passing the meshes
    registry.view<TransformComponent, MeshComponent>().each(
        [&](auto entity, auto &transform, auto &mesh) {
            renderer->submitModel(mesh.model, renderer->defaultShader, transform.modelMatrix());
        });

    renderer->endScene();
}
} // namespace chert