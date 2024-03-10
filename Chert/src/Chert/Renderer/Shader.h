#pragma once

namespace chert {
    class Shader {

    public:
        virtual ~Shader() {}
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}