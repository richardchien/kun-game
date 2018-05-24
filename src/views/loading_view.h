#pragma once

#include "./main_view.h"
#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class LoadingView final : public View {
        void draw() override {
            canvas_->fill_and_set_background_color(Colors::BLACK);
            canvas_->set_foreground_color(Colors::WHITE);
            canvas_->draw_border({1, 1, 1, 1}, 2);

            canvas_->set_foreground_color(Colors::CYAN);

            Int margin_top = 7;
            canvas_->draw_text("��  ӭ  ��  ��",
                               Attribute()
                                   .add_aligning(Alignings::HORIZONTAL_CENTER)
                                   .add_aligning(Alignings::TOP)
                                   .set_margin_top(margin_top));
            margin_top += 2;
            canvas_->draw_text("����е����ϵ���Ϸ",
                               Attribute()
                                   .add_aligning(Alignings::HORIZONTAL_CENTER)
                                   .add_aligning(Alignings::TOP)
                                   .set_margin_top(margin_top));
        }

        void loop() override {
            // ������Ϸ���ٵ�
            load();

            // ���û����ո�
            wait_for_keypress(' ');

            // �û����˿ո�
            MainView main_view;
            jump(main_view);
        }

        bool loaded_ = false;

        // ��װ�ڼ���
        void load() {
            unsigned long waited_time = 0;
            const unsigned long total_waited_time = 100; // ���� 5 ��

            auto loading_flag = 0;
            std::string loading_text(13, '=');
            std::string loading_active_text = " ";
            const auto attr = Attribute()
                                  .set_margin_bottom(7)
                                  .add_aligning(Alignings::HORIZONTAL_CENTER)
                                  .add_aligning(Alignings::BOTTOM);

            while (waited_time < total_waited_time) {
                auto s = loading_text;
                s.replace(loading_flag, loading_active_text.size(), loading_active_text);
                canvas_->draw_text(s, attr);
                loading_flag = (loading_flag + 1) % (loading_text.size() - loading_active_text.size());

                Sleep(100);
                waited_time += 100;
            }

            const auto loading_text_rect = canvas_->get_calculated_rect(Size(loading_text.size(), 1), attr);
            const auto loading_text_bg_rect =
                loading_text_rect.resized({canvas_->get_size().width - 8, loading_text_rect.height()});
            canvas_->get_screen().clear(loading_text_rect);
            canvas_->draw_text("> ���ո���� <", attr);
            canvas_->fill_foreground_color(Colors::CYAN | Colors::INTENSITY, loading_text_rect);

            loaded_ = true;
        }
    };
} // namespace kun::views
