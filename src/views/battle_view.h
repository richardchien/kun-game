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

        std::string text() override { return "�������ˣ�������ͦ�����ģ�Ҫ��Ҫ��"; }

        std::vector<std::string> menus() override {
            return {
                "��Ҫ�ˣ������գ�",
                "���",
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
                // ˭Ҳ�򲻶�˭
                show_notice("�����е����Σ����˼��غϣ�˭��û��Ѫ�����Ǹ��ظ��Ұɡ���");
                return;
            }

            auto won = false;
            auto exp_inc = 0;
            if (enermy_.attack <= self_.defence) {
                // ���˴򲻶��ҷ���Ӯ��
                won = true;
                exp_inc = random_int(5, 30);
            } else if (self_.attack <= enermy_.defence) {
                // �򲻶����ˣ�����
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

            show_notice(std::string(won ? "Ӯ" : "��") + "�ˣ������ " + std::to_string(exp_inc) + " �㾭��� "
                        + std::to_string(coin_inc) + " ����ҡ�");

            if (won) {
                // Ӯ�˵�����£������װ��
                switch (random_int(1, 4)) {
                case 1:
                    // ʲô������
                    break;
                case 2: {
                    // ��Ѫƿ
                    const auto hp_inc = random_int(10, 100) / 10 * 10;
                    pet_.properties.hp += hp_inc;
                    show_notice("��Ѫƿ��Ѫ�������� " + std::to_string(hp_inc) + " �㡣");
                    break;
                }
                case 3: {
                    // �񵽹�������
                    static const std::vector<std::pair<std::string, int>> weapons{
                        {"�̹Ÿ�", 2},
                        {"��ԯ��", 3},
                        {"������", 5},
                        {"�����", 8},
                        {"���ӡ", 10},
                    };

                    const auto weapon = weapons[random_int(0, 4)];
                    pet_.properties.attack += weapon.second;
                    show_notice("��" + weapon.first + "������������ " + std::to_string(weapon.second) + " �㡣");
                    break;
                }
                case 4: {
                    // �񵽷�������
                    static const std::vector<std::pair<std::string, int>> weapons{
                        {"����ս����", 2},
                        {"���ս��", 3},
                        {"�����ۼ�", 5},
                        {"��ũ��", 8},
                        {"���ؾ�", 10},
                    };

                    const auto weapon = weapons[random_int(0, 4)];
                    pet_.properties.defence += weapon.second;
                    show_notice("��" + weapon.first + "������������ " + std::to_string(weapon.second) + " �㡣");
                    break;
                }
                default:
                    break;
                }
            }

            if (level_up) {
                // ������
                show_notice("��ϲ�������� " + std::to_string(pet_.properties.level) + " ���ˣ�");
            }
        }

        void escape() {
            pet_.add_exp(1);
            show_notice("��Ȼ�����ˣ���������һ�㾭��ɣ��ԣ����� 1 �㡣");
        }
    };
} // namespace kun::views
