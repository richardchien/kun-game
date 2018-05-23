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

        // ��ָ������̨����ʾ��ǰ View
        virtual void display_on(Screen &screen) {
            screen.clear();
            Canvas canvas(screen);
            draw(canvas);
            loop(canvas);
        }

    protected:
        // ���� View
        virtual void draw(Canvas &canvas) {}

        // ������ѭ��
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
