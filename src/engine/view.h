#pragma once

#include <conio.h>

#include "./canvas.h"
#include "./screen.h"

namespace kun::engine {
    // 用于统一游戏各页面的绘制和主循环
    class View {
    public:
        using Attribute = Canvas::Attribute;
        using Alignings = Canvas::Alignings;

        virtual ~View() = default;
        View() = default;

        // 在指定控制台上显示当前 View
        virtual void display_on(Screen &screen) {
            canvas_ = std::make_shared<Canvas>(screen);
            redraw();
            loop();
        }

        static int wait_for_keypress(const int expected_ch = '\0') {
            while (true) {
                if (_kbhit()) {
                    const auto ch = _getch();
                    if (expected_ch == '\0' || ch == expected_ch) {
                        return ch;
                    }
                }
                Sleep(20);
            }
        }

    protected:
        std::shared_ptr<Canvas> canvas_ = nullptr;

        // 绘制 View
        virtual void draw() {}

        void redraw() {
            canvas_->clear();
            draw();
        }

        // 主循环
        virtual void loop() {}

        void jump(View &new_view) {
			// 显示新页面，进入它的主循环
			new_view.display_on(canvas_->get_screen());
            // redraw(); // 从下一个页面返回，重新绘制当前页面
        }
    };
} // namespace kun::engine
