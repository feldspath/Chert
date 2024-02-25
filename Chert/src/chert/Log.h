#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Chert/Core.h"

namespace chert {

    class CHERT_API Log
    {
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
        inline static std::shared_ptr<spdlog::logger>& getAppLogger() { return appLogger; }

    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> appLogger;
    };

}

#define CHERT_CORE_TRACE(...) ::chert::Log::getCoreLogger()->trace(__VA_ARGS__)
#define CHERT_CORE_DEBUG(...) ::chert::Log::getCoreLogger()->debug(__VA_ARGS__)
#define CHERT_CORE_INFO(...) ::chert::Log::getCoreLogger()->info(__VA_ARGS__)
#define CHERT_CORE_WARN(...) ::chert::Log::getCoreLogger()->warn(__VA_ARGS__)
#define CHERT_CORE_ERROR(...) ::chert::Log::getCoreLogger()->error(__VA_ARGS__)
#define CHERT_CORE_FATAL(...) ::chert::Log::getCoreLogger()->critical(__VA_ARGS__)

#define CHERT_TRACE(...) ::chert::Log::getAppLogger()->trace(__VA_ARGS__)
#define CHERT_DEBUG(...) ::chert::Log::getAppLogger()->debug(__VA_ARGS__)
#define CHERT_INFO(...) ::chert::Log::getAppLogger()->info(__VA_ARGS__)
#define CHERT_WARN(...) ::chert::Log::getAppLogger()->warn(__VA_ARGS__)
#define CHERT_ERROR(...) ::chert::Log::getAppLogger()->error(__VA_ARGS__)
#define CHERT_FATAL(...) ::chert::Log::getAppLogger()->critical(__VA_ARGS__)
