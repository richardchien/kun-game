#pragma once

#include "./notice_view.h"
#include "./pet_mixin.h"
#include "core/enermy.h"
#include "engine/engine.h"
#include "utils/random.h"

namespace kun::views {
    using namespace engine;
    using namespace core;
    using utils::random_int;

    class EnermyView final : public TextView, PetMixin {
    public:
        EnermyView() : enermy_(Enermy::random(pet_)) {}

    private:
        Enermy enermy_;

        std::string text() override { return "�������ˣ�������ͦ�����ģ�Ҫ��Ҫ��"; }

        std::vector<std::string> menus() override { return {"��Ҫ�ˣ������գ�", "���"}; }

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
            if (enermy_.attack <= pet_.properties.defence && pet_.properties.attack <= enermy_.defence) {
                // ˭Ҳ�򲻶�˭
                NoticeView view("�����е����Σ����˼��غϣ�˭��û��Ѫ�����Ǹ��ظ��Ұɡ���");
                jump(view);
                return;
            }

            auto won = false;
            auto exp_inc = 0;
            if (enermy_.attack <= pet_.properties.defence) {
                // ���˴򲻶��ҷ���Ӯ��
                won = true;
                exp_inc = random_int(5, 10);
            } else if (pet_.properties.attack <= enermy_.defence) {
                // �򲻶����ˣ�����
                won = false;
                exp_inc = random_int(10, 15);
            } else {
                const auto round_count_enermy = enermy_.hp / (pet_.properties.attack - enermy_.defence);
                const auto round_count_pet = pet_.properties.hp / (enermy_.attack - pet_.properties.defence);
                won = round_count_pet >= round_count_enermy;
                exp_inc =
                    random_int(min(0.08 * pet_.properties.experience, 15), min(0.25 * pet_.properties.experience, 20));
            }

            const auto level_up = pet_.add_exp(exp_inc);

            NoticeView view(std::string(won ? "Ӯ" : "��") + "�ˣ������ " + std::to_string(exp_inc) + " �㾭�顣");
            jump(view);

            switch (random_int(1, 4)) {
            case 1:
                // ʲô������
                break;
            case 2: {
                // ��Ѫƿ
                const auto hp_inc = random_int(10, 100) / 10 * 10;
                pet_.properties.hp += hp_inc;
                view = NoticeView("��Ѫƿ��Ѫ�������� " + std::to_string(hp_inc) + " �㡣");
                jump(view);
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
                view = NoticeView("��" + weapon.first + "������������ " + std::to_string(weapon.second) + " �㡣");
                jump(view);
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
                view = NoticeView("��" + weapon.first + "������������ " + std::to_string(weapon.second) + " �㡣");
                jump(view);
                break;
            }
            default:
                break;
            }

            if (level_up) {
                // ������
                view = NoticeView("��ϲ�������� " + std::to_string(pet_.properties.level) + " ���ˣ�");
                jump(view);
            }
        }

        void escape() {
            pet_.add_exp(1);
            NoticeView view("��Ȼ�����ˣ���������һ�㾭��ɣ��ԣ����� 1 �㡣");
            jump(view);
        }
    };
} // namespace kun::views
