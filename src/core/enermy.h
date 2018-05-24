#pragma once

#include "./pet.h"
#include "utils/random.h"

namespace kun::core {
    using utils::random_int;

    struct Enermy {
        int hp = 100;
        int attack = 10;
        int defence = 10;

        static Enermy random(const Pet &pet) {
            Enermy enermy;
            enermy.hp = random_int(pet.properties.hp - 100, pet.properties.hp + 100);
            // const auto min_point = min(pet.properties.attack, pet.properties.defence);
            // const auto max_point = max(pet.properties.attack, pet.properties.defence);
            enermy.attack = random_int(max(pet.properties.defence - 20, 1), pet.properties.defence + 10);
            enermy.defence = random_int(max(pet.properties.attack - 10, 1), pet.properties.attack + 20);
            return enermy;
        }
    };
} // namespace kun::core
