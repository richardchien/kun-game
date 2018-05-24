#pragma once

#include "engine/engine.h"
#include "sub_view.h"

namespace kun::views {
    using namespace engine;

    class MainView : public MenuView {
    private:
        std::vector<std::string> menus() override {
            return {"开始新游戏", "载入存档", "游戏说明", "开发团队", "退出游戏"};
        }

        enum MenuItem {
            MENU_ITEM_START_NEW_GAME = 0,
            MENU_ITEM_LOAD_SAVED_GAME,
            MENU_ITEM_ABOUT,
            MENU_ITEM_DEV_TEAM,
            MENU_ITEM_EXIT,
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
                menu.break_loop();
                break;
            case MENU_ITEM_EXIT:
                exit(0);
                break;
            default:
                break;
            }
        }

        void start_new_game() {
            SubView view;
            jump(view);
        }

        void loaded_saved_game() {}
        void about() {}
        void dev_team() {}
    };
} // namespace kun::views
