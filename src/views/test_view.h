#pragma once

#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class TestView final : public View {
        void loop() override { wait_for_keypress('\r'); }
    };
} // namespace kun::views
