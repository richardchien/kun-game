#pragma once

#include "./menu.h"
#include "./view.h"

namespace kun::engine {
    using namespace engine;

    // 在整个页面居中显示一个菜单的视图
    class MenuView : public View {
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

        virtual std::vector<std::string> menus() = 0;
        virtual void on_select(Menu &menu, int index) = 0;
    };
} // namespace kun::engine
