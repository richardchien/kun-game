#pragma once

#include "./notice_view.h"
#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class AboutView final : public TextView {
        std::string text() override { return "开局一只鲲，进化全靠吞。\n\n可以看出，这是一款非常智障的游戏了……"; }

        std::vector<std::string> menus() override { return {"什么，我不觉得智障啊", "哦"}; }

        enum MenuItem {
            MENU_ITEM_I_AM_STUPID,
            MENU_ITEM_OH,
        };

        void on_select(Menu &menu, const int index) override {
            switch (index) {
            case MENU_ITEM_I_AM_STUPID: {
                NoticeView view("那就是你制杖了（");
                jump(view);
                break;
            }
            case MENU_ITEM_OH:
                menu.break_loop();
                break;
            default:
                break;
            }
        }
    };
} // namespace kun::views
