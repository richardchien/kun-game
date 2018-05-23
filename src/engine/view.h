#pragma once

#include "./canvas.h"
#include "./screen.h"

namespace kun::engine {
    class View {
    public:
        virtual ~View() = default;
        View() = default;

        // 在指定控制台上显示当前 View
        virtual void display_on(Screen &screen) {
            Canvas canvas(screen);
            draw(canvas);
            loop(canvas);
        }

    protected:
        // 绘制 View
        virtual void draw(Canvas &canvas) {}

        // 进入主循环
        virtual void loop(Canvas &canvas) {}
    };
} // namespace kun::engine
