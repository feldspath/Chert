#pragma once

#include "Chert/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace chert {
    class OpenGLContext : public RenderingContext {
    public:
        OpenGLContext(std::shared_ptr<GLFWwindow> window);
        void init() override;
        void swapBuffers() override;

    private:
        std::shared_ptr<GLFWwindow> window;
    };
}