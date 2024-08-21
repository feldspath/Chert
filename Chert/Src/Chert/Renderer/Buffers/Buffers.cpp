#include "Chert/Core/Application.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace chert {

Ref<IndexBuffer> IndexBuffer::create(unsigned int *indices, unsigned int count) {
    return Application::get().getRenderContext()->createIndexBuffer(indices, count);
}

Ref<VertexBuffer> VertexBuffer::create(float *vertices, unsigned int count) {
    return Application::get().getRenderContext()->createVertexBuffer(vertices, count);
}

Ref<VertexArray> VertexArray::create() {
    return Application::get().getRenderContext()->createVertexArray();
}

} // namespace chert