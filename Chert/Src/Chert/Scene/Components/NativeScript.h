#pragma once

#include <functional>
#include <memory>

#include "Chert/Scene/Entity/NativeScript.h"

namespace chert {
class NativeScriptComponent {
private:
    friend class Scene;
    std::unique_ptr<NativeScript> script;
    std::function<std::unique_ptr<NativeScript>()> instantiateScript;

public:
    // T derives from NativeScript
    template <typename T> void bind() {
        instantiateScript = []() { return std::make_unique<T>(); };
    }
};
} // namespace chert