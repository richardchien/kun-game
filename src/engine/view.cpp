#include "./view.h"

#include "./notice_view.h"

namespace kun::engine {
    void View::show_notice(const std::string &notice) {
        NoticeView view(notice);
        jump(view);
    }
} // namespace kun::engine
