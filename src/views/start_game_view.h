#pragma once

#include "./game_dashboard_view.h"
#include "core/game.h"
#include "engine/engine.h"

namespace kun::views {
    using namespace engine;
    using namespace core;

    class StartGameView final : public InputView {
        std::string prompt() override { return "��������Ļ�ɫ���������������������֣�"; }

        void on_input(const std::string &input) override {
            Game::start_new(input);
            GameDashboardView dashboardv_view;
            jump(dashboardv_view);
        }
    };
} // namespace kun::views
