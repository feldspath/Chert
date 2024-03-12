#include "Input.h"

namespace chert {
    std::unique_ptr<Input> Input::instance;

    void Input::init() {
        CHERT_CORE_ASSERT(!instance, "Input handler is already initialized");
        instance = createInputHandler();
    }
}