#pragma once

#include "./about_view.h"
#include "./start_game_view.h"
#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class MainView final : public MenuView {
        std::vector<std::string> menus() override {
            return {"�½���Ϸ", "����浵", "��Ϸ˵��", "�����Ŷ�", "�˳���Ϸ"};
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
                // ���ش浵�ɹ�
                GameDashboardView view;
                jump(view);
            } else {
                NoticeView view("�浵����ʧ�ܣ���Ÿ�����û������ɡ�");
                jump(view);
            }
        }

        void about() {
            AboutView view;
            jump(view);
        }

        void dev_team() {
            NoticeView view("���\nǮ�\n����\n������");
            jump(view);
        }
    };
} // namespace kun::views
