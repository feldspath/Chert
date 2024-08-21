#include "RenderAPI.h"
#include "Chert/Core/Log.h"

namespace chert {
std::unique_ptr<RenderAPI> RenderAPI::instance;

void RenderAPI::init() {
    CHERT_CORE_ASSERT(!instance, "RenderAPI is already initialized");
    instance = createRenderAPI();
}
} // namespace chert
