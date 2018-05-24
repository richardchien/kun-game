#pragma once

#include "engine/engine.h"

namespace kun::engine {
    class NoticeView final : public TextView {
    public:
        NoticeView(const std::string &text) : text_(text) {}

    private:
        std::string text_;

        std::string text() override { return text_; }
        std::vector<std::string> menus() override { return {"我知道了"}; }
        void on_select(Menu &menu, const int index) override { menu.break_loop(); }
    };
} // namespace kun::engine
