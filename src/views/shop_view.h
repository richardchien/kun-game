#pragma once

#include "./pet_mixin.h"
#include "engine/engine.h"
#include "utils/random.h"

namespace kun::views {
    using namespace engine;
    using namespace core;
    using std::endl;
    using utils::random_int;

    class ShopView final : public TextView, PetMixin {
        std::string text() override {
            return "��ӭ��������̵꣡�������� " + std::to_string(pet_.properties.coin) + " ��ң�׼��������������";
        }

        int hp_price() { return pet_.properties.level * 300; }
        int attack_price() { return pet_.properties.level * 500; }
        int defence_price() { return pet_.properties.level * 400; }

        std::vector<std::string> menus() override {
            return {
                std::to_string(hp_price()) + " ��ҹ��� 100 ��Ѫ��",
                std::to_string(attack_price()) + " ��ҹ��� 10 �㹥��",
                std::to_string(defence_price()) + " ��ҹ��� 10 �����",
                "�뿪�̵�",
            };
        }

        enum MenuItem {
            MENU_ITEM_BUY_HP = 0,
            MENU_ITEM_BUY_ATTACK,
            MENU_ITEM_BUY_DEFENCE,
            MENU_ITEM_EXIT_SHOP,
        };

        void on_select(Menu &menu, const int index) override {
            const auto notice_insufficient_coin = [&] { show_notice("���Ѱɣ���ûǮ�ˡ�"); };

            switch (index) {
            case MENU_ITEM_BUY_HP:
                if (pet_.properties.coin >= hp_price()) {
                    pet_.properties.hp += 100;
                    pet_.properties.coin -= hp_price();
                    show_notice("Ѫ�������� 100 �㡣");
                } else {
                    notice_insufficient_coin();
                }
                break;
            case MENU_ITEM_BUY_ATTACK:
                if (pet_.properties.coin >= attack_price()) {
                    pet_.properties.attack += 10;
                    pet_.properties.coin -= attack_price();
                    show_notice("���������� 100 �㡣");
                } else {
                    notice_insufficient_coin();
                }
                break;
            case MENU_ITEM_BUY_DEFENCE:
                if (pet_.properties.coin >= defence_price()) {
                    pet_.properties.defence += 10;
                    pet_.properties.coin -= defence_price();
                    show_notice("���������� 10 �㡣");
                } else {
                    notice_insufficient_coin();
                }
                break;
            case MENU_ITEM_EXIT_SHOP:
                menu.break_loop();
                break;
            default:
                break;
            }
        }
    };
} // namespace kun::views
