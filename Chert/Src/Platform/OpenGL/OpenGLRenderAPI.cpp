#include "OpenGLRenderAPI.h"
#include "glad/glad.h"

namespace chert {
std::unique_ptr<RenderAPI> createRenderAPI() { return std::make_unique<OpenGLRenderAPI>(); }

void OpenGLRenderAPI::setClearColorImpl(const glm::vec4 &color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderAPI::clearImpl() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void OpenGLRenderAPI::drawIndexedImpl(Ref<VertexArray> &vertexArray) {
    glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
}
void OpenGLRenderAPI::setViewportImpl(unsigned int x, unsigned int y, unsigned int width,
                                      unsigned int height) {
    glViewport(x, y, width, height);
}
void OpenGLRenderAPI::unbindCurrentVertexArrayImpl() { glBindVertexArray(0); }
} // namespace chert