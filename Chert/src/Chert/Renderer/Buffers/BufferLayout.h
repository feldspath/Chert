#pragma once

#include <initializer_list>
#include <string>
#include <vector>

#include "Chert/Core.h"

namespace chert {
enum class ShaderDataType {
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
};

static unsigned int dataTypeSize(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Mat3:
        return 4 * 9;
    case ShaderDataType::Mat4:
        return 4 * 16;
    case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;
    }

    CHERT_CORE_ASSERT(false, "Unknown ShaderDataType");
    return 0;
}

static unsigned int dataTypePrimitiveCount(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
        return 1;
    case ShaderDataType::Float2:
        return 2;
    case ShaderDataType::Float3:
        return 3;
    case ShaderDataType::Float4:
        return 4;
    case ShaderDataType::Mat3:
        return 9;
    case ShaderDataType::Mat4:
        return 16;
    case ShaderDataType::Int:
        return 1;
    case ShaderDataType::Int2:
        return 2;
    case ShaderDataType::Int3:
        return 3;
    case ShaderDataType::Int4:
        return 4;
    }

    CHERT_CORE_ASSERT(false, "Unknown ShaderDataType");
    return 0;
}

struct BufferElement {
    std::string name;
    ShaderDataType type;
    unsigned int size;
    unsigned int offset;
    unsigned int primitiveCount;

    BufferElement(ShaderDataType type, const std::string &name)
        : name(name), type(type), offset(0), size(dataTypeSize(type)),
          primitiveCount(dataTypePrimitiveCount(type)) {}
};

class BufferLayout {
public:
    BufferLayout() {}
    BufferLayout(std::initializer_list<BufferElement> elements)
        : elements(elements) {
        unsigned int offset = 0;
        for (auto &e : this->elements) {
            e.offset = offset;
            offset += e.size;
        }
        totalSize = offset;
    }

    bool isInitialized() const { return totalSize != 0; }

    std::vector<BufferElement>::const_iterator begin() const {
        return elements.cbegin();
    }
    std::vector<BufferElement>::const_iterator end() const {
        return elements.cend();
    }

private:
    std::vector<BufferElement> elements;
    unsigned int totalSize = 0;
};
} // namespace chert