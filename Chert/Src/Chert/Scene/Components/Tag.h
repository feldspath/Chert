#pragma once

#include <string>

namespace chert {
struct TagComponent {
    std::string tag;

    TagComponent() = default;
    TagComponent(const std::string &tag) : tag(tag) {}
};
} // namespace chert