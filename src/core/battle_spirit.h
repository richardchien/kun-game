#pragma once

#include "./pet.h"
#include "utils/random.h"

namespace kun::core {
    using utils::random_int;

    struct BattleSpirit {
        int hp = 100;
        int attack = 10;
        int defence = 10;

        static BattleSpirit random_enermy(const BattleSpirit &self) {
            BattleSpirit enermy;
            enermy.hp = random_int(self.hp - 100, self.hp + 100);
            enermy.attack = random_int(max(self.attack * 0.5, 1), self.attack * 1.3);
            enermy.defence = random_int(max(self.defence * 0.6, 1), self.defence * 1.5);
            return enermy;
        }

        static BattleSpirit from_pet(const Pet &pet) {
            return BattleSpirit{
                pet.properties.hp, pet.properties.attack, static_cast<int>(pet.properties.defence * 0.7)};
        }
    };
} // namespace kun::core
