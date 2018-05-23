#pragma once

#include "./canvas.h"
#include "./screen.h"

namespace kun::engine {
    class View {
    public:
        virtual ~View() = default;
        View() = default;

        // ��ָ������̨����ʾ��ǰ View
        virtual void display_on(Screen &screen) {
            Canvas canvas(screen);
            draw(canvas);
            loop(canvas);
        }

    protected:
        // ���� View
        virtual void draw(Canvas &canvas) {}

        // ������ѭ��
        virtual void loop(Canvas &canvas) {}
    };
} // namespace kun::engine
