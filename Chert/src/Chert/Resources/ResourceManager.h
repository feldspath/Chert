#pragma once

#include <filesystem>

#include "Chert/Core/Core.h"
#include "Chert/Scene/Model/Model.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "glm/gtc/type_ptr.hpp"

namespace chert {
class ResourceManager {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;

        static BufferLayout getLayout() {
            return {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float3, "a_Normal"},
                {ShaderDataType::Float2, "a_TexCoords"},
            };
        }
    };

    ResourceManager() = delete;

    static Ref<Model> loadModel(const std::filesystem::path &path);
    static Ref<Model> processScene(aiNode *root, const aiScene *scene);
    static void processNode(Ref<Model> model, aiNode *node, const aiScene *scene);
    static Ref<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
};
} // namespace chert