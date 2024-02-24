#pragma once

#include "chert/Log.h"

#ifdef CHERT_PLATFORM_WINDOWS

extern chert::Application* chert::CreateApplication();

int main() {
    chert::Log::init();
    CHERT_CORE_INFO("Lauching Chert...");
    auto app = chert::CreateApplication();
    app->run();
    delete app;
}

#endif