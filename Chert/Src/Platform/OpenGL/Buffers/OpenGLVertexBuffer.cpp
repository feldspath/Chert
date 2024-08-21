#include "OpenGLVertexBuffer.h"
#include "glad/glad.h"

namespace chert {
OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, unsigned int size) {
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &bufferId); }

void OpenGLVertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, bufferId); }

void OpenGLVertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
} // namespace chert