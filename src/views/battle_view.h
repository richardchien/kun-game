#pragma once

#include "./pet_mixin.h"
#include "core/battle_spirit.h"
#include "engine/engine.h"
#include "utils/random.h"

namespace kun::views {
    using namespace engine;
    using namespace core;
    using utils::random_int;

    class BattleView final : public TextView, PetMixin {
    public:
        BattleView() : self_(BattleSpirit::from_pet(pet_)), enermy_(BattleSpirit::random_enermy(self_)) {}

    private:
        BattleSpirit self_;
        BattleSpirit enermy_;

        std::string text() override { return "遇到敌人，看起来挺厉害的，要不要打？"; }

        std::vector<std::string> menus() override {
            return {
                "不要怂，跟他刚！",
                "溜吧",
            };
        }

        enum MenuItem {
            MENU_ITEM_FIGHT = 0,
            MENU_ITEM_ESCAPE,
        };

        void on_select(Menu &menu, const int index) override {
            switch (index) {
            case MENU_ITEM_FIGHT:
                fight();
                menu.break_loop();
                break;
            case MENU_ITEM_ESCAPE:
                escape();
                menu.break_loop();
                break;
            default:
                break;
            }
        }

        void fight() {
            if (enermy_.attack <= self_.defence && self_.attack <= enermy_.defence) {
                // 谁也打不动谁
                show_notice("场面有点尴尬，打了几回合，谁都没掉血，还是各回各家吧……");
                return;
            }

            auto won = false;
            auto exp_inc = 0;
            if (enermy_.attack <= self_.defence) {
                // 敌人打不动我方，赢了
                won = true;
                exp_inc = random_int(5, 30);
            } else if (self_.attack <= enermy_.defence) {
                // 打不动敌人，输了
                won = false;
                exp_inc = random_int(10, 30);
            } else {
                const auto round_count_enermy = enermy_.hp / (self_.attack - enermy_.defence);
                const auto round_count_pet = self_.hp / (enermy_.attack - self_.defence);
                won = round_count_pet >= round_count_enermy;
                exp_inc =
                    random_int(max(0.08 * pet_.properties.experience, 15), max(0.25 * pet_.properties.experience, 40));
            }

            const auto level_up = pet_.add_exp(exp_inc);

            const auto coin_inc = random_int(exp_inc * 5, exp_inc * 15);
            pet_.properties.coin += coin_inc;

            show_notice(std::string(won ? "赢" : "输") + "了，获得了 " + std::to_string(exp_inc) + " 点经验和 "
                        + std::to_string(coin_inc) + " 个金币。");

            if (won) {
                // 赢了的情况下，捡掉落装备
                switch (random_int(1, 4)) {
                case 1:
                    // 什么都不干
                    break;
                case 2: {
                    // 捡到血瓶
                    const auto hp_inc = random_int(10, 100) / 10 * 10;
                    pet_.properties.hp += hp_inc;
                    show_notice("捡到血瓶，血量增加了 " + std::to_string(hp_inc) + " 点。");
                    break;
                }
                case 3: {
                    // 捡到攻击武器
                    static const std::vector<std::pair<std::string, int>> weapons{
                        {"盘古斧", 2},
                        {"轩辕剑", 3},
                        {"东皇钟", 5},
                        {"昊天塔", 8},
                        {"崆峒印", 10},
                    };

                    const auto weapon = weapons[random_int(0, 4)];
                    pet_.properties.attack += weapon.second;
                    show_notice("捡到" + weapon.first + "，攻击增加了 " + std::to_string(weapon.second) + " 点。");
                    break;
                }
                case 4: {
                    // 捡到防御武器
                    static const std::vector<std::pair<std::string, int>> weapons{
                        {"孤星战月铠", 2},
                        {"梼杌战甲", 3},
                        {"穷奇袍甲", 5},
                        {"神农鼎", 8},
                        {"昆仑镜", 10},
                    };

                    const auto weapon = weapons[random_int(0, 4)];
                    pet_.properties.defence += weapon.second;
                    show_notice("捡到" + weapon.first + "，防御增加了 " + std::to_string(weapon.second) + " 点。");
                    break;
                }
                default:
                    break;
                }
            }

            if (level_up) {
                // 升级了
                show_notice("恭喜你升级到 " + std::to_string(pet_.properties.level) + " 级了！");
            }
        }

        void escape() {
            pet_.add_exp(1);
            show_notice("虽然你溜了，还是送你一点经验吧，对，就是 1 点。");
        }
    };
} // namespace kun::views
