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
            return "欢迎来到鲲宠商店！你现在有 " + std::to_string(pet_.properties.coin) + " 金币，准备好买买买了吗？";
        }

        int hp_price() { return pet_.properties.level * 300; }
        int attack_price() { return pet_.properties.level * 500; }
        int defence_price() { return pet_.properties.level * 400; }

        std::vector<std::string> menus() override {
            return {
                std::to_string(hp_price()) + " 金币购买 100 点血量",
                std::to_string(attack_price()) + " 金币购买 10 点攻击",
                std::to_string(defence_price()) + " 金币购买 10 点防御",
                "离开商店",
            };
        }

        enum MenuItem {
            MENU_ITEM_BUY_HP = 0,
            MENU_ITEM_BUY_ATTACK,
            MENU_ITEM_BUY_DEFENCE,
            MENU_ITEM_EXIT_SHOP,
        };

        void on_select(Menu &menu, const int index) override {
            const auto notice_insufficient_coin = [&] { show_notice("醒醒吧，你没钱了。"); };

            switch (index) {
            case MENU_ITEM_BUY_HP:
                if (pet_.properties.coin >= hp_price()) {
                    pet_.properties.hp += 100;
                    pet_.properties.coin -= hp_price();
                    show_notice("血量增加了 100 点。");
                } else {
                    notice_insufficient_coin();
                }
                break;
            case MENU_ITEM_BUY_ATTACK:
                if (pet_.properties.coin >= attack_price()) {
                    pet_.properties.attack += 10;
                    pet_.properties.coin -= attack_price();
                    show_notice("攻击增加了 100 点。");
                } else {
                    notice_insufficient_coin();
                }
                break;
            case MENU_ITEM_BUY_DEFENCE:
                if (pet_.properties.coin >= defence_price()) {
                    pet_.properties.defence += 10;
                    pet_.properties.coin -= defence_price();
                    show_notice("防御增加了 10 点。");
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
