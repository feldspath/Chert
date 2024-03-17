#pragma once

#include "Chert/Core/Application.h"

#ifdef CHERT_PLATFORM_WINDOWS

int main() {
    chert::Application::initApplication();
    chert::Application::get().run();
    chert::Application::get().shutdown();
}

#endif