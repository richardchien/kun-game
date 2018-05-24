#pragma once

#include "./menu.h"
#include "./menu_view.h"

namespace kun::engine {
    using namespace engine;

    // 在整个页面居中显示一个菜单的视图
    class TextView : public MenuView {
    protected:
        void draw() override {
            canvas_->fill_and_set_background_color(Colors::WHITE);
            canvas_->set_foreground_color(Colors::BLACK);
            canvas_->draw_border({1, 1, 1, 1}, 2);
        }

        void loop() override {
            Menu menu(*canvas_, menus(), [this](Menu &menu, const int index) { on_select(menu, index); });
            menu.show();
        }

        virtual std::string text() = 0;
    };
} // namespace kun::engine
