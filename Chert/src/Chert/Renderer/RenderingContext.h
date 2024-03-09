#pragma once

namespace chert {
    class RenderingContext {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };
}