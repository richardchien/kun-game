#pragma once

#include <Windows.h>
#include <string>
#include <vector>

#include "types.h"

namespace kun::engine {
    class Screen {
    public:
        Screen(const HANDLE handle = nullptr) {
            handle_ = handle ? handle : GetStdHandle(STD_OUTPUT_HANDLE);
            init();
        }

        void reattach(const HANDLE handle) {
            handle_ = handle;
            init();
        }

        HANDLE get_handle() const { return handle_; }

        Screen &fill_color(const Color color, Rect rect = Rect(-1, -1, -1, -1)) {
            const auto buffer_info = get_buffer_info();

            if (rect == Rect(-1, -1, -1, -1)) {
                rect = Rect({0, 0}, get_size());
            }

            DWORD num;
            const auto attr = attribute_with_new_color(buffer_info.wAttributes, color);
            for (auto y = rect.top(); y <= rect.bottom(); y++) {
                FillConsoleOutputAttribute(handle_,
                                           attr,
                                           rect.width() * 2 /* 控制台里的实际宽度是字符数的两倍 */,
                                           COORD{rect.left() * 2, y},
                                           &num);
            }
            return *this;
        }

        Screen &fill_bg_color(const Color bg_color, const Rect &rect = Rect(-1, -1, -1, -1)) {
            return fill_color(Colors::combine(bg_color, get_buffer_info().wAttributes & 0x0F /* 获取当前前景色 */),
                              rect);
        }

        Screen &fill_fg_color(const Color fg_color, const Rect &rect = Rect(-1, -1, -1, -1)) {
            return fill_color(
                Colors::combine((get_buffer_info().wAttributes & 0xF0) >> 4 /* 获取当前背景色 */, fg_color), rect);
        }

        Screen &set_color(const Color color) {
            SetConsoleTextAttribute(handle_, attribute_with_new_color(get_buffer_info().wAttributes, color));
            return *this;
        }

        Screen &set_bg_color(const Color bg_color) {
            return set_color(Colors::combine(bg_color, get_buffer_info().wAttributes & 0x0F /* 获取当前前景色 */));
        }

        Screen &set_fg_color(const Color fg_color) {
            return set_color(
                Colors::combine((get_buffer_info().wAttributes & 0xF0) >> 4 /* 获取当前背景色 */, fg_color));
        }

        Color get_color() const {
            return get_buffer_info().wAttributes & 0xFF; // 取低八位的背景和前景色
        }

        Screen &set_size(const Size &size) {
            // 设置缓冲区大小，为了让缓冲区是正方形，宽要乘 2
            SetConsoleScreenBufferSize(handle_, COORD{size.width * 2, size.height});

            // 设置控制台窗口大小，宽同理
            SMALL_RECT window_rect;
            window_rect.Top = 0;
            window_rect.Bottom = size.height - 1; // 坐标从 0 开始，所以需要用高度减 1
            window_rect.Left = 0;
            window_rect.Right = size.width * 2 - 1; // 同上
            SetConsoleWindowInfo(handle_, TRUE, &window_rect);

            return *this;
        }

        Size get_size() const {
            const auto w = get_buffer_info().srWindow;
            return {w.Right / 2 /* 用户所看到的宽度是控制台实际宽度的一半 */, w.Bottom};
        }

        Rect get_boundary() const { return Rect(Point(0, 0), get_size()); }

        Screen &clear() {
            const auto size = get_buffer_info().dwSize;
            DWORD num;
            FillConsoleOutputCharacterA(handle_, ' ', size.X * size.Y, COORD{0, 0}, &num);
            return *this;
        }

        Screen &set_cursor_position(const Point &position) {
            SetConsoleCursorPosition(handle_, COORD{position.x * 2, position.y});
            return *this;
        }

        Screen &write(const std::string &str) {
            DWORD num;
            WriteConsoleA(handle_, str.c_str(), str.size(), &num, nullptr);
            return *this;
        }

        Screen &write(const Point &position, const std::string &str) {
            set_cursor_position(position);
            return write(str);
        }

        std::string read(const Point &position, const Int length) const {
            std::string s(length, ' ');
            DWORD num;
            ReadConsoleOutputCharacterA(handle_, s.data(), length, COORD{position.x * 2, position.y}, &num);
            return s;
        }

        std::vector<std::string> read(const Rect &rect) const {
            std::vector<std::string> lines;
            for (auto y = rect.top(); y <= rect.bottom(); y++) {
                lines.push_back(read({rect.left(), y}, rect.width()));
            }
            return lines;
        }

    private:
        HANDLE handle_ = nullptr;

        void init() {
            // 设置初始状态为白底黑字
            const auto color = Colors::combine(Colors::WHITE, Colors::BLACK);
            fill_color(color);
            set_color(color);

            // 隐藏光标
            CONSOLE_CURSOR_INFO cursor_info;
            GetConsoleCursorInfo(handle_, &cursor_info);
            cursor_info.bVisible = FALSE;
            SetConsoleCursorInfo(handle_, &cursor_info);
        }

        CONSOLE_SCREEN_BUFFER_INFO get_buffer_info() const {
            CONSOLE_SCREEN_BUFFER_INFO buffer_info;
            GetConsoleScreenBufferInfo(handle_, &buffer_info);
            return buffer_info;
        }

        static DWORD attribute_with_new_color(DWORD attribute, const Color color) {
            attribute &= ~0xFF; // 清除背景和前景色的八位
            attribute |= color & 0xFF; // 设置新的背景和前景色
            return attribute;
        }

        static DWORD attribute_with_new_bg_color(DWORD attribute, const Color bg_color) {
            attribute &= ~0xF0; // 清除背景色的四位
            attribute |= (bg_color & 0xF) << 4; // 设置新的背景色
            return attribute;
        }

        static DWORD attribute_with_new_fg_color(DWORD attribute, const Color fg_color) {
            attribute &= ~0x0F; // 清除前景色的四位
            attribute |= fg_color & 0xF; // 设置新的前景色
            return attribute;
        }
    };
} // namespace kun::engine
