#pragma once

#include <Windows.h>
#include <ctime>
#include <nlohmann/json.hpp>
#include <string>

#include "utils/encoding.h"
#include "utils/random.h"

namespace kun::core {
    using nlohmann::json;
    using utils::random_int;

    // ������
    struct Pet {
        Pet() = default;
        Pet(const std::string &name) : name(name), birthtime(time(nullptr)) {}

        // �����࣬��Ż�����Ϸ�仯������
        struct Properties {
            int experience = 0;
            int next_level_experience = 100;
            int level = 1;
            int hp = 100;
            int attack = 10;
            int defence = 10;
            int coin = 0;
            static const int ENERGY_MAX = 100;
            int energy = ENERGY_MAX;
        };

        enum class Type {
            XIAO_KUN, // С��
            DA_KUN, // ����
            SHI_KUN, // ʬ��
            KAI_KUN, // ����
            LAN_KUN, // ����
            GU_KUN, // ����
            CHI_KUN, // ����
            JU_KUN, // ����
            TU_KUN, // ����
            XUAN_KUN, // ����
            SHANG_GU_JU_KUN, // �Ϲž���
            DAO_JING_KUN, // ������
            KUN_WANG, // ����
        };

        std::string name = "";
        time_t birthtime = 0;
        Type type = Type::XIAO_KUN;
        Properties properties;

        int age() const { return (time(nullptr) - birthtime) / (60 * 5 /* 5 ����һ�� */) + 1; }

        static std::string type_string(const Type type) {
            switch (type) {
            case Type::XIAO_KUN:
                return "С��";
            case Type::DA_KUN:
                return "����";
            case Type::SHI_KUN:
                return "ʬ��";
            case Type::KAI_KUN:
                return "����";
            case Type::LAN_KUN:
                return "����";
            case Type::GU_KUN:
                return "����";
            case Type::CHI_KUN:
                return "����";
            case Type::JU_KUN:
                return "����";
            case Type::TU_KUN:
                return "����";
            case Type::XUAN_KUN:
                return "����";
            case Type::SHANG_GU_JU_KUN:
                return "�Ϲž���";
            case Type::DAO_JING_KUN:
                return "������";
            case Type::KUN_WANG:
                return "����";
            default:
                return "";
            }
        }

        std::string type_string() const { return type_string(type); }

        bool add_exp(const int inc) {
            properties.experience += inc;
            if (properties.experience >= properties.next_level_experience) {
                level_up();
                return true;
            }
            return false;
        }

    private:
        void level_up() {
            properties.level += 1;
            properties.next_level_experience *= 2;

            switch (type) {
            case Type::XIAO_KUN:
                type = Type::DA_KUN;
                break;
            case Type::DA_KUN: {
                const auto point = max(properties.hp / 10, max(properties.attack, properties.defence));
                if (point == properties.attack) {
                    type = Type::SHI_KUN;
                } else if (point == properties.defence) {
                    type = Type::KAI_KUN;
                } else {
                    type = Type::LAN_KUN;
                }
                break;
            }
            case Type::SHI_KUN:
                type = std::vector<Type>{Type::GU_KUN, Type::CHI_KUN}[random_int(0, 1)];
                break;
            case Type::KAI_KUN:
            case Type::LAN_KUN:
                type = Type::JU_KUN;
                break;
            case Type::GU_KUN:
            case Type::CHI_KUN:
            case Type::JU_KUN:
                type = Type::TU_KUN;
                break;
            case Type::TU_KUN:
                type = std::vector<Type>{Type::XUAN_KUN, Type::SHANG_GU_JU_KUN}[random_int(0, 1)];
                break;
            case Type::XUAN_KUN:
            case Type::SHANG_GU_JU_KUN:
                type = Type::DAO_JING_KUN;
                break;
            case Type::DAO_JING_KUN:
                type = Type::KUN_WANG;
                break;
            case Type::KUN_WANG:
                type = Type::KUN_WANG;
                break;
            default:
                break;
            }
        }
    };

    inline void from_json(const json &j, Pet::Properties &props) {
        props.experience = j.at("experience").get<int>();
        props.next_level_experience = j.at("next_level_experience").get<int>();
        props.level = j.at("level").get<int>();
        props.hp = j.at("hp").get<int>();
        props.attack = j.at("attack").get<int>();
        props.defence = j.at("defence").get<int>();
        props.coin = j.at("coin").get<int>();
        props.energy = j.at("energy").get<int>();
    }

    inline void to_json(json &j, const Pet::Properties &props) {
        j = {
            {"experience", props.experience},
            {"next_level_experience", props.next_level_experience},
            {"level", props.level},
            {"hp", props.hp},
            {"attack", props.attack},
            {"defence", props.defence},
            {"coin", props.coin},
            {"energy", props.energy},
        };
    }

    inline void from_json(const json &j, Pet &pet) {
        pet.name = utils::utf8_to_gbk(j.at("name").get<std::string>().c_str());
        pet.birthtime = j.at("birthtime").get<time_t>();
        pet.type = j.at("type").get<Pet::Type>();
        pet.properties = j.at("properties").get<Pet::Properties>();
    }

    inline void to_json(json &j, const Pet &pet) {
        j = {
            {"name", utils::gbk_to_utf8(pet.name.c_str())},
            {"birthtime", pet.birthtime},
            {"type", pet.type},
            {"properties", pet.properties},
        };
    }
} // namespace kun::core
