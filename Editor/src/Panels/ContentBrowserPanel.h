#pragma once

#include <filesystem>

#include "Chert/Scene/Scene.h"

namespace chert {

class ContentBrowserPanel {
public:
    ContentBrowserPanel() = default;
    ContentBrowserPanel(Ref<Scene> scene) : scene(scene), currentDirectory(assetPath){};

    void render();

private:
    static const std::filesystem::path assetPath;

    Ref<Scene> scene;
    std::filesystem::path currentDirectory;
};
} // namespace chert