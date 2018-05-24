#pragma once

#include <functional>

#include "./screen.h"

namespace kun::engine {
    // 对 Screen 类做了一层封装，提供更便捷的接口，包括输出时的对齐和边距设置
    class Canvas {
    public:
        Canvas(Screen &screen) : screen_(screen) {}

        Screen &get_screen() const { return screen_; }
        Rect get_rect() const { return screen_.get_boundary(); }
        Size get_size() const { return screen_.get_size(); }

        void fill_background_color(const Color color, const Rect &rect = Rect(-1, -1, -1, -1)) {
            screen_.fill_bg_color(color, rect);
        }

        void fill_foreground_color(const Color color, const Rect &rect = Rect(-1, -1, -1, -1)) {
            screen_.fill_fg_color(color, rect);
        }

        void fill_color(const Color color, const Rect &rect = Rect(-1, -1, -1, -1)) { screen_.fill_color(color, rect); }

        void set_background_color(const Color color) { screen_.set_bg_color(color); }
        void set_foreground_color(const Color color) { screen_.set_fg_color(color); }
        void set_color(const Color color) { screen_.set_color(color); }

        Color get_background_color() const { return (get_color() & 0xF0) >> 4; }
        Color get_foreground_color() const { return get_color() & 0x0F; }
        Color get_color() const { return screen_.get_color(); }

        void fill_and_set_background_color(const Color color, const Rect &rect = Rect(-1, -1, -1, -1)) {
            fill_background_color(color, rect);
            set_background_color(color);
        }

        void fill_and_set_foreground_color(const Color color, const Rect &rect = Rect(-1, -1, -1, -1)) {
            fill_foreground_color(color, rect);
            set_foreground_color(color);
        }

        void clear(const Rect &rect = {-1, -1, -1, -1}) { screen_.clear(rect); }

        using Aligning = uint8_t;
        struct Alignings {
            // 垂直方向对齐方式
            static const Aligning TOP = 0x01; // 0000 0001
            static const Aligning BOTTOM = 0x02; // 0000 0010
            static const Aligning VERTICAL_CENTER = TOP | BOTTOM; // 0000 0011

            // 水平方向对齐方式
            static const Aligning LEFT = 0x04; // 0000 0100
            static const Aligning RIGHT = 0x08; // 0000 1000
            static const Aligning HORIZONTAL_CENTER = LEFT | RIGHT; // 0000 1100
        };

        struct Margin {
            Int top = 0;
            Int right = 0;
            Int bottom = 0;
            Int left = 0;
        };

        struct Attribute {
            Aligning aligning = 0;
            Margin margin;

            Attribute set_aligning(const Aligning aligning) {
                this->aligning = aligning;
                return *this;
            }

            Attribute add_aligning(const Aligning aligning) {
                this->aligning |= aligning;
                return *this;
            }

            Attribute set_margin(const Margin &margin) {
                this->margin = margin;
                return *this;
            }

            Attribute set_margin_top(const Int margin_top) {
                this->margin.top = margin_top;
                return *this;
            }

            Attribute set_margin_right(const Int margin_right) {
                this->margin.right = margin_right;
                return *this;
            }

            Attribute set_margin_bottom(const Int margin_bottom) {
                this->margin.bottom = margin_bottom;
                return *this;
            }

            Attribute set_margin_left(const Int margin_left) {
                this->margin.left = margin_left;
                return *this;
            }
        };

        Rect get_calculated_rect(const Size &size, const Attribute &attr) const {
            const auto margined_rect = get_margined_rect(attr.margin);

            Point pos;

            if (attr.aligning & Alignings::TOP && attr.aligning & Alignings::BOTTOM) {
                // 垂直居中
                pos.y = margined_rect.top() + (margined_rect.height() - size.height) / 2;
            } else if (attr.aligning & Alignings::BOTTOM) {
                // 底部对齐
                pos.y = margined_rect.bottom() - size.height + 1;
            } else {
                // 顶部对齐
                pos.y = margined_rect.top();
            }

            if (attr.aligning & Alignings::LEFT && attr.aligning & Alignings::RIGHT) {
                // 水平居中
                pos.x = margined_rect.left() + (margined_rect.width() - size.width) / 2;
            } else if (attr.aligning & Alignings::RIGHT) {
                // 右对齐
                pos.x = margined_rect.right() - size.width + 1;
            } else {
                // 左对齐
                pos.x = margined_rect.left();
            }

            return Rect(pos, size);
        }

        void draw_text(const std::string &text, const Attribute &attr = Attribute()) {
            const Size size((text.size() % 2 == 0 ? text.size() : text.size() + 1) / 2, 1);
            screen_.write(get_calculated_rect(size, attr).top_left(), text);
        }

        void draw_border(const Margin &margin, const Int width = 1, const char vertical_ch = '|',
                         const char horizontal_ch = '-', const char corner_ch = '+') {
            const auto margined_rect = get_margined_rect(margin);
            const Rect inner_rect(margined_rect.left() + width,
                                  margined_rect.top() + width,
                                  margined_rect.right() - width,
                                  margined_rect.bottom() - width);

            const auto dwidth = width * 2;

            // 打印上边界
            const auto top_bottom_border = std::string(width, corner_ch)
                                           + std::string(margined_rect.width() * 2 - width * 2, horizontal_ch)
                                           + std::string(width, corner_ch);
            for (auto i = 0; i < width; i++) {
                draw_text(top_bottom_border,
                          Attribute()
                              .set_margin(margin)
                              .set_margin_top(margin.top + i)
                              .set_aligning(Alignings::TOP | Alignings::LEFT));
            }

            // 打印左右边界
            const auto left_border = std::string(width, vertical_ch);
            const auto right_border = left_border.size() % 2 == 0 ? left_border : " " + left_border;
            for (auto y = inner_rect.top(); y < inner_rect.bottom_out(); y++) {
                draw_text(
                    left_border,
                    Attribute().set_margin(margin).set_margin_top(y).set_aligning(Alignings::TOP | Alignings::LEFT));
                draw_text(
                    right_border,
                    Attribute().set_margin(margin).set_margin_top(y).set_aligning(Alignings::TOP | Alignings::RIGHT));
            }

            // 打印下边界
            for (auto i = width - 1; i >= 0; i--) {
                draw_text(top_bottom_border,
                          Attribute()
                              .set_margin(margin)
                              .set_margin_bottom(margin.bottom + i)
                              .set_aligning(Alignings::BOTTOM | Alignings::LEFT));
            }
        }

    private:
        Screen &screen_;

        Rect get_margined_rect(const Margin &margin) const {
            const auto rect = get_rect();
            const Rect margined_rect(rect.left() + margin.left,
                                     rect.top() + margin.top,
                                     rect.right() - margin.right,
                                     rect.bottom() - margin.bottom);
            return margined_rect;
        }
    };
} // namespace kun::engine
