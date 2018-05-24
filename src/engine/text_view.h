#pragma once

#include "./menu.h"
#include "./menu_view.h"

namespace kun::engine {
    using namespace engine;

    // 页面上部分显示文本，下部分显示菜单
    class TextView : public MenuView {
    protected:
        void draw() override {
            MenuView::draw();
            canvas_->draw_text(text(), get_inner_boundary().expanded(-2));
        }

        void loop() override {
            std::function<void(Menu &, int)> on_select_cb = [this](Menu &menu, const int index) {
                on_select(menu, index);
            };

            auto menu_vec = menus();
            if (menu_vec.empty()) {
                menu_vec.push_back("返回");
                on_select_cb = [](Menu &menu, const int index) { menu.break_loop(); };
            }

            Menu menu(*canvas_, menu_vec, on_select_cb);
            menu.show(get_inner_boundary().expanded(-2), Alignings::BOTTOM);
        }

        virtual std::string text() = 0;
        std::vector<std::string> menus() override { return {}; }
        void on_select(Menu &menu, int index) override {}
    };
} // namespace kun::engine
