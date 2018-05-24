#pragma once

#include <Windows.h>
#include <conio.h>
#include <memory>

#include "./canvas.h"
#include "./screen.h"

namespace kun::engine {
    // 用于统一游戏各页面的绘制和主循环
    class View {
    public:
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
                Sleep(10);
            }
        }

    protected:
        using Attribute = Canvas::Attribute;
        using Alignings = Canvas::Alignings;
        using Margin = Canvas::Margin;

        std::shared_ptr<Canvas> canvas_ = nullptr;

        // 绘制 View 的静态内容，留给子类实现
        virtual void draw() {
            canvas_->fill_and_set_background_color(Colors::WHITE);
            canvas_->set_foreground_color(Colors::BLACK);
            canvas_->draw_border({1, 1, 1, 1}, 2);
        }

        // 主循环，子类应该自行在重写方法中实现相应的循环
        // 当此函数返回后，其所属的 View 就不再有效了，如果是通过 jump 显示的，将会回到上一级页面的控制
        virtual void loop() {}

        // 清屏之后再绘制
        void redraw() {
            canvas_->clear();
            draw();
        }

        // 获取除去了边界的可绘制范围
        Rect get_inner_boundary() const {
            const auto full_size = canvas_->get_size();
            // draw 绘制的边界左右有 2 个宽度、上下有 3 个宽度
            return canvas_->get_rect().resized({full_size.width - 2 * 2, full_size.height - 3 * 2});
        }

        void jump(View &new_view) {
            // 显示新页面，进入它的主循环
            new_view.display_on(canvas_->get_screen());

            // 从下一个页面返回，重新绘制当前页面，
            // 如果当前页是菜单视图，那实际上 jump 是在 on_select 里面调用的，
            // 这里重绘页面之后，on_select 返回，Menu 类会自己重新输出菜单项
            redraw();
        }
    };
} // namespace kun::engine
