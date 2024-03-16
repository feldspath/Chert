#pragma once

#include "BufferLayout.h"

namespace chert {
class VertexBuffer {

public:
    virtual ~VertexBuffer() = default;
    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void setLayout(const BufferLayout &layout) = 0;
    virtual const BufferLayout &getLayout() = 0;
};
} // namespace chert