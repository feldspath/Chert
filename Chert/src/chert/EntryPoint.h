#pragma once

#ifdef CHERT_PLATFORM_WINDOWS

extern chert::Application* chert::CreateApplication();

int main() {
    printf("Lauching Chert...\n");
    auto app = chert::CreateApplication();
    app->run();
    delete app;
}

#endif