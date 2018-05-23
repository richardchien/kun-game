#pragma once

#include "engine/engine.h"

#include "./main_view.h"

namespace kun {
    using namespace engine;

    class LoadingView : public View {
    public:
        void draw(Canvas &canvas) override {
            canvas.fill_and_set_background_color(Colors::BLACK)
                .set_foreground_color(Colors::WHITE)
                .draw_border({1, 1, 1, 1}, 2);

            canvas.set_foreground_color(Colors::CYAN);

            Int margin_top = 7;
            canvas.draw_text("��  ӭ  ��  ��",
                             Attribute()
                                 .add_aligning(Alignings::HORIZONTAL_CENTER)
                                 .add_aligning(Alignings::TOP)
                                 .set_margin_top(margin_top));
            margin_top += 2;
            canvas.draw_text("����е����ϵ���Ϸ",
                             Attribute()
                                 .add_aligning(Alignings::HORIZONTAL_CENTER)
                                 .add_aligning(Alignings::TOP)
                                 .set_margin_top(margin_top));
        }

        void loop(Canvas &canvas) override {
            unsigned long waited_time = 0;
            const unsigned long total_waited_time = 3000;

            auto loading_flag = 0;
            std::string loading_text = "=========";
            const auto attr = Attribute()
                                  .set_margin_bottom(7)
                                  .add_aligning(Alignings::HORIZONTAL_CENTER)
                                  .add_aligning(Alignings::BOTTOM);
            // ���� 3 ��
            while (waited_time < total_waited_time) {
                auto s = loading_text;
                s.replace(loading_flag, 1, "*");
                canvas.draw_text(s, attr);
                loading_flag = (loading_flag + 1) % loading_text.size();

                Sleep(100);
                waited_time += 100;
            }

            const auto loading_text_rect = canvas.get_calculated_rect(Size(loading_text.size(), 1), attr);
            const auto loading_text_bg_rect =
                loading_text_rect.expanded(canvas.get_size().width - 8, loading_text_rect.height());
            canvas.get_screen().clear(loading_text_rect);
            canvas.draw_text("���ո����", attr);
            canvas.fill_foreground_color(Colors::CYAN | Colors::INTENSITY, loading_text_rect);

            // ���û����ո�
            wait_for_keypress(' ');

            // �û����˿ո�
            MainView main_view;
            main_view.display_on(canvas.get_screen());
        }
    };
} // namespace kun
