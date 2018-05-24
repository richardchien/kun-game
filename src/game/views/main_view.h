#pragma once

#include "engine/engine.h"

#include "./about_view.h"
#include "./test_view.h"

namespace kun::views {
    using namespace engine;

    class MainView final : public MenuView {
        std::vector<std::string> menus() override {
            return {"新建游戏", "载入存档", "游戏说明", "开发团队", "退出游戏", "测试"};
        }

        enum MenuItem {
            MENU_ITEM_START_NEW_GAME = 0,
            MENU_ITEM_LOAD_SAVED_GAME,
            MENU_ITEM_ABOUT,
            MENU_ITEM_DEV_TEAM,
            MENU_ITEM_EXIT,
            MENU_IETM_TEST,
        };

        void on_select(Menu &menu, const int index) override {
            switch (index) {
            case MENU_ITEM_START_NEW_GAME:
                start_new_game();
                break;
            case MENU_ITEM_LOAD_SAVED_GAME:
                loaded_saved_game();
                break;
            case MENU_ITEM_ABOUT:
                about();
                break;
            case MENU_ITEM_DEV_TEAM:
                dev_team();
                break;
            case MENU_ITEM_EXIT:
                exit(0);
                break;
            case MENU_IETM_TEST:
                test();
                break;
            default:
                break;
            }
        }

        void start_new_game() {}

        void loaded_saved_game() {}

        void about() {
            AboutView view;
            jump(view);
        }

        void dev_team() {}

        void test() {
            TestView view;
            jump(view);
        }
    };
} // namespace kun::views
