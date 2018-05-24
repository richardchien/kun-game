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
            oss << "名字：" << pet_.name << endl;
            oss << "年龄：" << pet_.age() << endl;
            oss << "类型：" << pet_.type_string() << endl;
            oss << "经验：" << pet_.properties.experience << endl;
            oss << "等级：" << pet_.properties.level << endl;
            oss << "血量：" << pet_.properties.hp << endl;
            oss << "攻击：" << pet_.properties.attack << endl;
            oss << "防御：" << pet_.properties.defence << endl;
            oss << "体力：" << pet_.properties.energy << endl;
            return oss.str();
        }

        std::vector<std::string> menus() override { return {"刷新状态", "喂食", "探险", "保存返回"}; }

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
                notice_oss << "成功喂食，体力增加了 " << pet_.properties.energy - old_energy
                           << "，你的鲲宠表示很开心……";
            } else {
                notice_oss << "你的鲲宠已经饱了，再喂就要撑死了！";
            }

            NoticeView view(notice_oss.str());
            jump(view);
        }

        void explore() {
            if (pet_.properties.energy < 10) {
                NoticeView view("你的鲲宠体力不够了，先喂饱它再探险吧。");
                jump(view);
                return;
            }

            const auto energy_dec = random_int(5, 10);
            pet_.properties.energy -= energy_dec;

            if (random_int(1, 10) > 2) {
                // 80% 概率碰到敌人
                EnermyView view;
                jump(view);
            } else {
                NoticeView view("探险归来，啥也没碰到。");
                jump(view);
            }
        }

        void save_game(Menu &menu) {
            const auto succeeded = Game::save();
            if (succeeded) {
                NoticeView view("存档保存成功。");
                jump(view);
                menu.break_loop();
            } else {
                NoticeView view("存档保存失败，大概因为你电脑要炸了吧。");
                jump(view);
            }
        }
    };
} // namespace kun::views
