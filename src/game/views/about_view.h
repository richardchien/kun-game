#pragma once

#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class AboutView final : public TextView {
        std::string text() override { return "开局一只鲲，进化全靠吞。\n\n可以看出，这是一款非常智障的游戏了……"; }
    };
} // namespace kun::views
