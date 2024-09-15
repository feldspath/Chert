#include "ContentBrowserPanel.h"
#include "imgui.h"

#include "Chert/Resources/ResourceManager.h"
#include "Chert/Scene/Components/Mesh.h"
#include "Chert/Scene/Entity/Entity.h"

namespace chert {
const std::filesystem::path ContentBrowserPanel::assetPath = "Editor/assets";

void ContentBrowserPanel::render() {
    ImGui::Begin("Content Browser");

    // Back button
    if (ImGui::Button("<----")) {
        currentDirectory = currentDirectory.parent_path();
    }

    // Folder content & navigation
    for (const auto &directoryEntry : std::filesystem::directory_iterator(currentDirectory)) {
        const auto &path = directoryEntry.path();
        if (ImGui::Button(path.filename().string().c_str())) {
            if (std::filesystem::is_directory(path)) {
                currentDirectory = path;
            } else if (path.extension().compare("obj")) {
                Entity newEntity = scene->createEntity(path.stem().string());
                Ref<Model> model = ResourceManager::loadModel(path.string());
                if (model) {
                    newEntity.addComponent<MeshComponent>(model);
                }
            }
        }
    }

    ImGui::End();
}
} // namespace chert