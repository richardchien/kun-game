#pragma once

#include <Windows.h>
#include <conio.h>
#include <memory>

#include "./canvas.h"
#include "./screen.h"

namespace kun::engine {
    // ����ͳһ��Ϸ��ҳ��Ļ��ƺ���ѭ��
    class View {
    public:
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
                Sleep(10);
            }
        }

    protected:
        using Attribute = Canvas::Attribute;
        using Alignings = Canvas::Alignings;
        using Margin = Canvas::Margin;

        std::shared_ptr<Canvas> canvas_ = nullptr;

        // ���� View �ľ�̬���ݣ���������ʵ��
        virtual void draw() {
            canvas_->fill_and_set_background_color(Colors::WHITE);
            canvas_->set_foreground_color(Colors::BLACK);
            canvas_->draw_border({1, 1, 1, 1}, 2);
        }

        // ��ѭ��������Ӧ����������д������ʵ����Ӧ��ѭ��
        // ���˺������غ��������� View �Ͳ�����Ч�ˣ������ͨ�� jump ��ʾ�ģ�����ص���һ��ҳ��Ŀ���
        virtual void loop() {}

        // ����֮���ٻ���
        void redraw() {
            canvas_->clear();
            draw();
        }

        // ��ȡ��ȥ�˱߽�Ŀɻ��Ʒ�Χ
        Rect get_inner_boundary() const {
            const auto full_size = canvas_->get_size();
            // draw ���Ƶı߽������� 2 ����ȡ������� 3 �����
            return canvas_->get_rect().resized({full_size.width - 2 * 2, full_size.height - 3 * 2});
        }

        void jump(View &new_view) {
            // ��ʾ��ҳ�棬����������ѭ��
            new_view.display_on(canvas_->get_screen());

            // ����һ��ҳ�淵�أ����»��Ƶ�ǰҳ�棬
            // �����ǰҳ�ǲ˵���ͼ����ʵ���� jump ���� on_select ������õģ�
            // �����ػ�ҳ��֮��on_select ���أ�Menu ����Լ���������˵���
            redraw();
        }
    };
} // namespace kun::engine
