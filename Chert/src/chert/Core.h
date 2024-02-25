#pragma once

#ifndef CHERT_PLATFORM_WINDOWS
    #error Chert only supports Windows...
#endif

#define CHERT_CORE_ASSERT(cond, ...) if (!cond) { CHERT_CORE_ERROR(__VA_ARGS__); std::abort(); }
#define CHERT_ASSERT(cond, ...) if (!cond) { CHERT_ERROR(__VA_ARGS__);  std::abort(); }