#pragma once

#include "./enermy_view.h"
#include "./notice_view.h"
#include "./pet_mixin.h"
#include "engine/engine.h"
#include "utils/random.h"

namespace kun::views {
    using namespace engine;
    using namespace core;
    using std::endl;
    using utils::random_int;

    class GameDashboardView final : public TextView, PetMixin {
        std::string text() override {
            std::ostringstream oss;
            oss << "���֣�" << pet_.name << endl;
            oss << "���䣺" << pet_.age() << endl;
            oss << "���ͣ�" << pet_.type_string() << endl;
            oss << "���飺" << pet_.properties.experience << endl;
            oss << "�ȼ���" << pet_.properties.level << endl;
            oss << "Ѫ����" << pet_.properties.hp << endl;
            oss << "������" << pet_.properties.attack << endl;
            oss << "������" << pet_.properties.defence << endl;
            oss << "������" << pet_.properties.energy << endl;
            return oss.str();
        }

        std::vector<std::string> menus() override { return {"ˢ��״̬", "ιʳ", "̽��", "���淵��"}; }

        enum MenuItem {
            MENU_ITEM_REFRESH_STATUS = 0,
            MENU_ITEM_FEED,
            MENU_ITEM_EXPLORE,
            MENU_ITEM_SAVE_AND_RETURN,
        };

        void on_select(Menu &menu, const int index) override {
            switch (index) {
            case MENU_ITEM_REFRESH_STATUS:
                refresh_status();
                break;
            case MENU_ITEM_FEED:
                feed();
                break;
            case MENU_ITEM_EXPLORE:
                explore();
                break;
            case MENU_ITEM_SAVE_AND_RETURN:
                save_game(menu);
                break;
            default:
                break;
            }
        }

        void refresh_status() { draw_text(); }

        void feed() {
            const auto energy_inc = random_int(5, 25);

            std::ostringstream notice_oss;
            if (pet_.properties.energy < Pet::Properties::ENERGY_MAX) {
                const auto old_energy = pet_.properties.energy;
                pet_.properties.energy = min(pet_.properties.energy + energy_inc, Pet::Properties::ENERGY_MAX);
                notice_oss << "�ɹ�ιʳ������������ " << pet_.properties.energy - old_energy
                           << "���������ʾ�ܿ��ġ���";
            } else {
                notice_oss << "�������Ѿ����ˣ���ι��Ҫ�����ˣ�";
            }

            NoticeView view(notice_oss.str());
            jump(view);
        }

        void explore() {
            if (pet_.properties.energy < 10) {
                NoticeView view("���������������ˣ���ι������̽�հɡ�");
                jump(view);
                return;
            }

            const auto energy_dec = random_int(5, 10);
            pet_.properties.energy -= energy_dec;

            if (random_int(1, 10) > 2) {
                // 80% ������������
                EnermyView view;
                jump(view);
            } else {
                NoticeView view("̽�չ�����ɶҲû������");
                jump(view);
            }
        }

        void save_game(Menu &menu) {
            const auto succeeded = Game::save();
            if (succeeded) {
                NoticeView view("�浵����ɹ���");
                jump(view);
                menu.break_loop();
            } else {
                NoticeView view("�浵����ʧ�ܣ������Ϊ�����Ҫը�˰ɡ�");
                jump(view);
            }
        }
    };
} // namespace kun::views
