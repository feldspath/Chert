#include "Chert/Log.h"
#include "Chert/Events/Event.h"

namespace chert {
std::shared_ptr<spdlog::logger> Log::coreLogger;
std::shared_ptr<spdlog::logger> Log::appLogger;

void Log::init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    coreLogger = spdlog::stdout_color_mt("CHERT");
    coreLogger->set_level(spdlog::level::trace);

    appLogger = spdlog::stdout_color_mt("APP");
    appLogger->set_level(spdlog::level::trace);
}
} // namespace chert