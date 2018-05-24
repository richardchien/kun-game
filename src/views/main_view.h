#pragma once

#include "sstream"

#include "./about_view.h"
#include "./start_game_view.h"
#include "./test_view.h"
#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class MainView final : public TextView {
        std::string text() override {
            return "           7PgBQQE5:          \n"
                   "        rKur.    .:LS2.       \n"
                   "     :QQL            .bBP     \n"
                   "    gB.                 IBi   \n"
                   "   BK       .             BU  \n"
                   "  BL    vB.B7     iBU:     B7 \n"
                   " sR      BB       JBP       B \n"
                   " B       .B       iB        qv\n"
                   "Id        i                 .E\n"
                   "RI                           M\n"
                   "2E                          .D\n"
                   " B     .B           rB      Pv\n"
                   " vQ     IBE   BB   QB:vv    B \n"
                   "  Qj      QB.uQB. BQ   7K  Br \n"
                   "   QP      .BQ .BBi     :SMv  \n"
                   "    DB:         :       7B1   \n"
                   "     .QQY            :bB1 gY..\n"
                   "        i11v::...:rY2L     5BB\n";
        }

        void draw_text() override {
            const auto ascii_art_text = text();
            std::istringstream iss(ascii_art_text);
            std::string first_line;
            std::getline(iss, first_line);
            const auto text_rect_width = first_line.size() / 2;
            const auto boundary = get_inner_boundary();
            canvas_->draw_text(ascii_art_text, boundary.expanded(text_rect_width - boundary.width(), -4));
        }

        std::vector<std::string> menus() override {
            return {
                "�½���Ϸ",
                "����浵",
                "��Ϸ˵��",
                "�����Ŷ�",
                "�˳���Ϸ",
                "�����˵�",
            };
        }

        enum MenuItem {
            MENU_ITEM_START_NEW_GAME = 0,
            MENU_ITEM_LOAD_SAVED_GAME,
            MENU_ITEM_ABOUT,
            MENU_ITEM_DEV_TEAM,
            MENU_ITEM_EXIT,
            MENU_ITEM_TEST,
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
            case MENU_ITEM_TEST: {
                TestView view;
                jump(view);
                break;
            }
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
                show_notice("�浵����ʧ�ܣ���Ÿ�����û������ɡ�");
            }
        }

        void about() {
            AboutView view;
            jump(view);
        }

        void dev_team() {
            show_notice(
                "Ǯ����Ŷӷ��ˡ�������Ա��������Ϸ�ܹ���ƺͿ���\n\n"
                "��  �ۣ������д˵�����߻�����Ƶ��ĵ�\n\n"
                "��  �𣺸�����Ϸ������ƺ� Logo ���\n\n"
                "�����ԣ�������Ϸ�İ���ƺ� PPT ����");
        }
    };
} // namespace kun::views
