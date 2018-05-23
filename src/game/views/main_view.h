#pragma once

#include "engine/engine.h"

namespace kun {
    using namespace engine;

    class MainView : public View {
    public:
        void draw(Canvas &canvas) override {
            canvas.fill_and_set_background_color(Colors::BLACK | Colors::INTENSITY)
                .set_foreground_color(Colors::WHITE)
                .draw_border({1, 1, 1, 1}, 2, '*', '*', '*');
        }

        void loop(Canvas &canvas) override {
            while (true) {
                Sleep(200);
            }
        }
    };
} // namespace kun
