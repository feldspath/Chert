#include "Renderer.h"

#include "glad/glad.h"

namespace chert {
    Renderer::Renderer(std::shared_ptr<RenderingContext> context) : context(context) {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
        };

        unsigned int indices[] = {
            0, 1, 2
        };

        vertexBuffer = context->createVertexBuffer(vertices, sizeof(vertices));
        indexBuffer = context->createIndexBuffer(indices, 3);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;

            void main() {
                gl_Position = vec4(a_Position, 1.0);
            }

        )";

        std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            void main() {
                color = vec4(0.1, 0.6, 0.3, 1.0);
            }

        )";

        shader =  context->createShader(vertexSrc, fragmentSrc);
    }
    void Renderer::render() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->bind();
        vertexBuffer->bind();
        indexBuffer->bind();
        glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, 0);
    }
}