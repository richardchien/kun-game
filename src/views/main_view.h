#pragma once

#include "./about_view.h"
#include "./start_game_view.h"
#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class MainView final : public MenuView {
        std::vector<std::string> menus() override {
            return {"新建游戏", "载入存档", "游戏说明", "开发团队", "退出游戏"};
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
                break;
            case MENU_ITEM_EXIT:
                exit(0);
                break;
            default:
                break;
            }
        }

        void start_new_game() {
            StartGameView view;
            jump(view);
        }

        void loaded_saved_game() {
            if (Game::load_saved()) {
                // 加载存档成功
                GameDashboardView view;
                jump(view);
            } else {
                NoticeView view("存档加载失败，大概根本就没保存过吧。");
                jump(view);
            }
        }

        void about() {
            AboutView view;
            jump(view);
        }

        void dev_team() {
            NoticeView view("俞慧\n钱宇超\n冯瑞\n王雨樵");
            jump(view);
        }
    };
} // namespace kun::views
