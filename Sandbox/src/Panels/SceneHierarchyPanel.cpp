#include "SceneHierarchyPanel.h"
#include "Chert/Core/Application.h"
#include "Chert/Resources/ResourceManager.h"
#include "Chert/Scene/Components/Mesh.h"
#include "Chert/Scene/Components/Tag.h"
#include "imgui.h"

namespace chert {
void SceneHierarchyPanel::render() {
    // Menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                Application::get().close();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    // Scene hierarchy
    ImGui::Begin("Scene Hierarchy");
    scene->registry.view<TagComponent>().each([&](auto entityID, auto &tag) {
        Entity entity(entityID, scene);
        drawEntityNode(entity);
    });

    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
        selectionContext = Entity::nullEntity();
    }

    ImGui::End();

    // Properties
    ImGui::Begin("Properties");
    if (selectionContext != Entity::nullEntity()) {
        displayComponents(selectionContext);
    }
    ImGui::End();
}

void SceneHierarchyPanel::drawEntityNode(Entity entity) {
    auto &tag = entity.getComponent<TagComponent>().tag;

    ImGuiTreeNodeFlags flags = ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
                               ImGuiTreeNodeFlags_OpenOnArrow;
    bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity.getID(), flags, tag.c_str());
    if (ImGui::IsItemClicked()) {
        selectionContext = entity;
    }

    if (opened) {
        ImGui::TreePop();
    }
}

template <typename Component>
static void displayComponentNode(Entity &entity, const char *componentName,
                                 std::function<void(Component &)> &&displayFunction,
                                 bool removable = true) {
    if (entity.hasComponent<Component>()) {
        auto &comp = entity.getComponent<Component>();
        if (removable) {
            bool shouldKeep = true;
            if (ImGui::CollapsingHeader(componentName, &shouldKeep,
                                        ImGuiTreeNodeFlags_DefaultOpen)) {
                displayFunction(comp);
            }
            if (!shouldKeep) {
                entity.removeComponent<Component>();
            }
        } else {
            if (ImGui::CollapsingHeader(componentName, ImGuiTreeNodeFlags_DefaultOpen)) {
                displayFunction(comp);
            }
        }
    }
}

void SceneHierarchyPanel::displayComponents(Entity entity) {
    ImGui::Text("Entity ID: %d", entity.getID());

    displayComponentNode<TagComponent>(
        entity, "Tag",
        [](auto &tag) {
            // Display tag component and edit it
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, tag.tag.c_str());
            if (ImGui::InputText("Name", buffer, sizeof(buffer))) {
                tag = std::string(buffer);
            }
        },
        false);

    displayComponentNode<TransformComponent>(
        entity, "Transform",
        [](auto &transform) {
            ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.1f);

            // Convert rotation quaternion to euler angles
            glm::vec3 rotation = glm::degrees(glm::eulerAngles(transform.rotation));
            if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.1f)) {
                transform.rotation = glm::quat(glm::radians(rotation));
            }

            ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
        },
        false);

    displayComponentNode<DirLightComponent>(entity, "Light", [](auto &light) {
        ImGui::ColorEdit3("Color", glm::value_ptr(light.color));
        ImGui::DragFloat("Intensity", &light.intensity, 0.1f);
    });
}
} // namespace chert