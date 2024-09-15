#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace chert {
static GLenum shaderDataTypeToOpenGLType(ShaderDataType type) {
    switch (type) {
    case chert::ShaderDataType::Float:
        return GL_FLOAT;
    case chert::ShaderDataType::Float2:
        return GL_FLOAT;
    case chert::ShaderDataType::Float3:
        return GL_FLOAT;
    case chert::ShaderDataType::Float4:
        return GL_FLOAT;
    case chert::ShaderDataType::Mat3:
        return GL_FLOAT;
    case chert::ShaderDataType::Mat4:
        return GL_FLOAT;
    case chert::ShaderDataType::Int:
        return GL_INT;
    case chert::ShaderDataType::Int2:
        return GL_INT;
    case chert::ShaderDataType::Int3:
        return GL_INT;
    case chert::ShaderDataType::Int4:
        return GL_INT;
    }

    CHERT_CORE_ASSERT(false, "Unknown ShaderDataType");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray() { glGenVertexArrays(1, &vertexArrayId); }

OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &vertexArrayId); }

void OpenGLVertexArray::bind() { glBindVertexArray(vertexArrayId); }

void OpenGLVertexArray::unbind() { glBindVertexArray(0); }

void OpenGLVertexArray::addVertexBuffer(Ref<VertexBuffer> vertexBuffer) {
    CHERT_CORE_ASSERT(vertexBuffer->getLayout().isInitialized(), "Layout is uninitialized");

    glBindVertexArray(vertexArrayId);
    vertexBuffer->bind();
    vertexBuffers.push_back(vertexBuffer);

    auto &layout = vertexBuffer->getLayout();

    for (const auto &e : layout) {
        glEnableVertexAttribArray(vertexAttribIndex);
        glVertexAttribPointer(vertexAttribIndex, e.primitiveCount,
                              shaderDataTypeToOpenGLType(e.type), GL_FALSE, layout.getTotalSize(),
                              (char *)0 + e.offset);
        vertexAttribIndex++;
    }

    glBindVertexArray(0);
}

void OpenGLVertexArray::setIndexBuffer(Ref<IndexBuffer> indexBuffer) {
    glBindVertexArray(vertexArrayId);
    indexBuffer->bind();
    this->indexBuffer = indexBuffer;
    glBindVertexArray(0);
}
} // namespace chert