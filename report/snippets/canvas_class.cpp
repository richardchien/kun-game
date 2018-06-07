class Canvas {
    // ...

    void draw_text(const std::string &text, const Rect &boundary) {
        std::vector<std::string> text_lines;
        std::istringstream iss(text);
        std::string line;
        while (std::getline(iss, line)) {
            text_lines.push_back(line);
        }

        const auto text_size_per_line = boundary.width() * 2;

        auto pos = boundary.top_left();
        for (size_t i = 0; i < text_lines.size() && pos.y <= boundary.bottom(); i++) {
            if (text_lines[i].empty()) {
                // 当前文本行是空行，直接输出一排空白
                screen_.write(pos, std::string(text_size_per_line, ' '));
                pos.y++;
            } else {
                // 输出当前文本行
                for (Int j = 0; pos.y <= boundary.bottom() && text_size_per_line * j < text_lines[i].size();
                        j++, pos.y++) {
                    auto line_in_rect = text_lines[i].substr(text_size_per_line * j, text_size_per_line);
                    line_in_rect.resize(text_size_per_line, ' '); // 填充当前矩形行剩下的空间
                    screen_.write(pos, line_in_rect);
                }
            }
        }
    }

    // ...
}
