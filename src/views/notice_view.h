#pragma once

#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class NoticeView final : public TextView {
    public:
        NoticeView(const std::string &text) : text_(text) {}
        std::string text() override { return text_; }

    private:
        std::string text_;
    };
} // namespace kun::views
