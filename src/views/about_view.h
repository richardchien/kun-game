#pragma once

#include "./notice_view.h"
#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class AboutView final : public TextView {
        std::string text() override { return "����һֻ�����ȫ���̡�\n\n���Կ���������һ��ǳ����ϵ���Ϸ�ˡ���"; }

        std::vector<std::string> menus() override { return {"ʲô���Ҳ��������ϰ�", "Ŷ"}; }

        enum MenuItem {
            MENU_ITEM_I_AM_STUPID,
            MENU_ITEM_OH,
        };

        void on_select(Menu &menu, const int index) override {
            switch (index) {
            case MENU_ITEM_I_AM_STUPID: {
                NoticeView view("�Ǿ����������ˣ�");
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
