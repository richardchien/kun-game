#pragma once

#include "./battle_view.h"
#include "./pet_mixin.h"
#include "./shop_view.h"
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
            oss << "名字：" << pet_.name << endl;
            oss << "年龄：" << pet_.age() << endl;
            oss << "类型：" << pet_.type_string() << endl;
            oss << "经验：" << pet_.properties.experience << endl;
            oss << "等级：" << pet_.properties.level << endl;
            oss << "血量：" << pet_.properties.hp << endl;
            oss << "攻击：" << pet_.properties.attack << endl;
            oss << "防御：" << pet_.properties.defence << endl;
            oss << "金币：" << pet_.properties.coin << endl;
            oss << "体力：" << pet_.properties.energy << endl;
            return oss.str();
        }

        std::vector<std::string> menus() override {
            return {
                "喂食",
                "探险",
                "商店",
                "保存游戏",
                "保存并返回主菜单",
            };
        }

        enum MenuItem {
            MENU_ITEM_FEED = 0,
            MENU_ITEM_EXPLORE,
            MENU_ITEM_SHOP,
            MENU_ITEM_SAVE,
            MENU_ITEM_SAVE_AND_RETURN,
        };

        void on_select(Menu &menu, const int index) override {
            switch (index) {
            case MENU_ITEM_FEED:
                feed();
                break;
            case MENU_ITEM_EXPLORE:
                explore();
                break;
            case MENU_ITEM_SHOP: {
                ShopView view;
                jump(view);
                break;
            }
            case MENU_ITEM_SAVE:
                save_game();
                break;
            case MENU_ITEM_SAVE_AND_RETURN:
                save_game();
                menu.break_loop();
                break;
            default:
                break;
            }
        }

        void feed() {
            const auto energy_inc = random_int(5, 25);

            std::ostringstream notice_oss;
            if (pet_.properties.energy < Pet::Properties::ENERGY_MAX) {
                const auto old_energy = pet_.properties.energy;
                pet_.properties.energy = min(pet_.properties.energy + energy_inc, Pet::Properties::ENERGY_MAX);
                notice_oss << "成功喂食，体力增加了 " << pet_.properties.energy - old_energy
                           << "，你的鲲宠表示很开心……";
            } else {
                notice_oss << "你的鲲宠已经饱了，再喂就要撑死了！";
            }

            show_notice(notice_oss.str());
        }

        void explore() {
            if (pet_.properties.energy < 10) {
                show_notice("你的鲲宠体力不够了，先喂饱它再探险吧。");
                return;
            }

            const auto energy_dec = random_int(5, 10);
            pet_.properties.energy -= energy_dec;

            if (random_int(1, 10) > 2) {
                // 80% 概率碰到敌人
                BattleView view;
                jump(view);
            } else {
                show_notice("探险归来，啥也没碰到。");
            }
        }

        void save_game() {
            const auto succeeded = Game::save();
            if (succeeded) {
                show_notice("存档保存成功。");
            } else {
                show_notice("存档保存失败，大概因为你电脑要炸了吧。");
            }
        }
    };
} // namespace kun::views
