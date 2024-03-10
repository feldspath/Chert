#pragma once

namespace chert {
    class IndexBuffer {

    public:
        virtual ~IndexBuffer() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual unsigned int getCount() const = 0;
    };
}