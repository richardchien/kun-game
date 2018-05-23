#pragma once

#include <conio.h>

#include "./canvas.h"
#include "./screen.h"

namespace kun::engine {
    class View {
    public:
        using Attribute = Canvas::Attribute;
        using Alignings = Canvas::Alignings;

        virtual ~View() = default;
        View() = default;

        // 在指定控制台上显示当前 View
        virtual void display_on(Screen &screen) {
            screen.clear();
            Canvas canvas(screen);
            draw(canvas);
            loop(canvas);
        }

    protected:
        // 绘制 View
        virtual void draw(Canvas &canvas) {}

        // 进入主循环
        virtual void loop(Canvas &canvas) {}

        static int wait_for_keypress(const int expected_ch = '\0') {
            while (true) {
                if (_kbhit()) {
                    const auto ch = _getch();
                    if (expected_ch == '\0' || ch == expected_ch) {
                        return ch;
                    }
                }
                Sleep(100);
            }
        }
    };
} // namespace kun::engine
