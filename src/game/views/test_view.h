#pragma once

#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class TestView final : public MenuView {
        std::vector<std::string> menus() override { return {"返回上一级"}; }

        enum MenuItem {
            MENU_ITEM_RETURN = 0,
        };

        void on_select(Menu &menu, const int index) override {
            switch (index) {
            case MENU_ITEM_RETURN:
                menu.break_loop();
                break;
            default:
                break;
            }
        }
    };
} // namespace kun::views
