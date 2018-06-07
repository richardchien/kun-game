class Screen {
    // ...

    Screen &show_cursor() {
        CONSOLE_CURSOR_INFO cursor_info;
        GetConsoleCursorInfo(handle_, &cursor_info);
        cursor_info.bVisible = TRUE;
        SetConsoleCursorInfo(handle_, &cursor_info);
        return *this;
    }

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

    // ...

    Screen &write(const std::string &str) {
        DWORD num;
        WriteConsoleA(handle_, str.c_str(), str.size(), &num, nullptr);
        return *this;
    }

    // ...
};
