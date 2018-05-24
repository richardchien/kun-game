#pragma once

#include <string>

namespace kun::utils {
    std::string utf8_to_gbk(const char *utf8_str);
    std::string gbk_to_utf8(const char *gbk_str);
} // namespace kun::utils
