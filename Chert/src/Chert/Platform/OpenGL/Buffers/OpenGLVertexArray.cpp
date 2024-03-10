#include "OpenGLVertexArray.h"
#include "glad/glad.h"


namespace chert {
    static GLenum shaderDataTypeToOpenGLType(ShaderDataType type) {
        switch (type) {
        case chert::ShaderDataType::Float: return GL_FLOAT;
        case chert::ShaderDataType::Float2: return GL_FLOAT;
        case chert::ShaderDataType::Float3: return GL_FLOAT;
        case chert::ShaderDataType::Float4: return GL_FLOAT;
        case chert::ShaderDataType::Mat3: return GL_FLOAT;
        case chert::ShaderDataType::Mat4: return GL_FLOAT;
        case chert::ShaderDataType::Int: return GL_INT;
        case chert::ShaderDataType::Int2: return GL_INT;
        case chert::ShaderDataType::Int3: return GL_INT;
        case chert::ShaderDataType::Int4: return GL_INT;
        }

        CHERT_CORE_ASSERT(false, "Unknow ShaderDataType");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &vertexArrayId);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &vertexArrayId);
    }

    void OpenGLVertexArray::bind() {
        glBindVertexArray(vertexArrayId);
    }

    void OpenGLVertexArray::unbind() {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) {
        CHERT_CORE_ASSERT(vertexBuffer->getLayout().isInitialized(), "Layout is uninitialized");

        glBindVertexArray(vertexArrayId);
        vertexBuffer->bind();
        vertexBuffers.push_back(vertexBuffer);
        
        unsigned int index = 0;
        for (const auto& e : vertexBuffer->getLayout()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, e.primitiveCount, shaderDataTypeToOpenGLType(e.type), GL_FALSE, e.size, (char*)0 + e.offset);
            index++;
        }
    }

    void OpenGLVertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) {
        glBindVertexArray(vertexArrayId);
        indexBuffer->bind();
        this->indexBuffer = indexBuffer;
    }
}