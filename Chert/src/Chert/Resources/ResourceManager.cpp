#include "ResourceManager.h"
#include "Chert/Core/Application.h"

namespace chert {
Ref<Model> ResourceManager::loadModel(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        CHERT_CORE_ERROR("Failed to load mesh at path {0}: {1}", path, importer.GetErrorString());
        return nullptr;
    }

    return processScene(scene->mRootNode, scene);
}

Ref<Model> ResourceManager::processScene(aiNode *root, const aiScene *scene) {
    Ref<Model> model = makeRef<Model>();
    processNode(model, root, scene);
    return model;
}

void ResourceManager::processNode(Ref<Model> model, aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *aiMesh = scene->mMeshes[node->mMeshes[i]];
        model->addMesh(processMesh(aiMesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(model, node->mChildren[i], scene);
    }
}

Ref<Mesh> ResourceManager::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
        if (mesh->mTextureCoords[0]) {
            vertex.texCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        } else {
            vertex.texCoords = {0.0f, 0.0f};
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    auto vertexBuffer =
        VertexBuffer::create((float *)vertices.data(), sizeof(Vertex) * vertices.size());
    vertexBuffer->setLayout(Vertex::getLayout());
    auto indexBuffer = IndexBuffer::create(indices.data(), indices.size());
    auto vertexArray = VertexArray::create();
    vertexArray->setIndexBuffer(indexBuffer);
    vertexArray->addVertexBuffer(vertexBuffer);

    return makeRef<Mesh>(vertexArray);
}
} // namespace chert