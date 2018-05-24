#pragma once

#include <conio.h>

#include "./canvas.h"
#include "./screen.h"

namespace kun::engine {
    // ����ͳһ��Ϸ��ҳ��Ļ��ƺ���ѭ��
    class View {
    public:
        using Attribute = Canvas::Attribute;
        using Alignings = Canvas::Alignings;

        virtual ~View() = default;
        View() = default;

        // ��ָ������̨����ʾ��ǰ View
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

        // ���� View
        virtual void draw() {}

        void redraw() {
            canvas_->clear();
            draw();
        }

        // ��ѭ��
        virtual void loop() {}

        void jump(View &new_view) {
			// ��ʾ��ҳ�棬����������ѭ��
			new_view.display_on(canvas_->get_screen());
            // redraw(); // ����һ��ҳ�淵�أ����»��Ƶ�ǰҳ��
        }
    };
} // namespace kun::engine
