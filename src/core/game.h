#pragma once

#include "fstream"

#include "./pet.h"

namespace kun::core {
    class Game {
    public:
        static Game &instance() { return game_; }

        static bool start_new(const std::string &pet_name) {
            game_ = Game();
            game_.pet_ = Pet(pet_name);
            return true;
        }

        static bool save() {
            if (std::ofstream f("data.json"); f.is_open()) {
                try {
                    const json j = game_.pet();
                    j >> f;
                    return true;
                } catch (...) {
                }
            }
            return false;
        }

        static bool load_saved() {
            if (std::ifstream f("data.json"); f.is_open()) {
                json j;
                try {
                    f >> j;
                    game_ = Game();
                    game_.pet_ = j.get<Pet>();
                    return true;
                } catch (...) {
                }
            }
            return false;
        }

        Pet &pet() { return pet_; }

    private:
        Game() = default;

        static Game game_;

        Pet pet_;
    };
} // namespace kun::core
