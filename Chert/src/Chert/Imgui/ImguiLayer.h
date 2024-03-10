#pragma once

namespace chert {
    class ImguiLayer {
        
    public:
        void init();
        void update();
        void begin();
        void end();

        ~ImguiLayer();

    private:
        float time = 0.0f;
    };
}