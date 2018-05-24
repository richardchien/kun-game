#pragma once

#include "core/game.h"
#include "core/pet.h"

namespace kun::views {
    class PetMixin {
    public:
        PetMixin() : pet_(core::Game::instance().pet()) {}

    protected:
        core::Pet &pet_;
    };
} // namespace kun::views
