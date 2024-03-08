#pragma once

#include "Chert/Application.h"

#ifdef CHERT_PLATFORM_WINDOWS

int main() {
    chert::Application::initApplication();
    chert::Application::get().run();
}

#endif