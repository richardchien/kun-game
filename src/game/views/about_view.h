#pragma once

#include "engine/engine.h"

namespace kun::views {
    using namespace engine;

    class AboutView final : public TextView {
        std::string text() override { return "����һֻ�����ȫ���̡�\n\n���Կ���������һ��ǳ����ϵ���Ϸ�ˡ���"; }
    };
} // namespace kun::views
