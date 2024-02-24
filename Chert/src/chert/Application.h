#pragma once

#include "Core.h"

namespace chert {
    class CHERT_API Application
    {
    public:
        void run();
    };

    Application* CreateApplication();
}


