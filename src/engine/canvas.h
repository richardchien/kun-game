#pragma once

#include "./screen.h"

namespace kun::engine {
    class Canvas {
    public:
        Canvas(Screen &screen) : screen_(screen) {}

        Screen &get_screen() const { return screen_; }

        Canvas &fill_background_with_color(const Color color) {
            screen_.fill_bg_color(color);
            return *this;
        }

        Canvas &fill_foreground_with_color(const Color color) {
            screen_.fill_fg_color(color);
            return *this;
        }

        Canvas &set_background_color(const Color color) {
            screen_.set_bg_color(color);
            return *this;
        }

        Canvas &set_foreground_color(const Color color) {
            screen_.set_fg_color(color);
            return *this;
        }

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

            Attribute &set_aligning(const Aligning aligning) {
                this->aligning = aligning;
                return *this;
            }

            Attribute &add_aligning(const Aligning aligning) {
                this->aligning |= aligning;
                return *this;
            }

            Attribute &set_margin(const Margin &margin) {
                this->margin = margin;
                return *this;
            }

            Attribute &set_margin_top(const Int margin_top) {
                this->margin.top = margin_top;
                return *this;
            }

            Attribute &set_margin_right(const Int margin_right) {
                this->margin.right = margin_right;
                return *this;
            }

            Attribute &set_margin_bottom(const Int margin_bottom) {
                this->margin.bottom = margin_bottom;
                return *this;
            }

            Attribute &set_margin_left(const Int margin_left) {
                this->margin.left = margin_left;
                return *this;
            }
        };

        Canvas &print_text(const std::string &text, const Attribute &attr = Attribute()) {
            const auto screen_rect = screen_.get_boundary();
            const Rect boundary(screen_rect.left() + attr.margin.left,
                                screen_rect.top() + attr.margin.top,
                                screen_rect.right() - attr.margin.right,
                                screen_rect.bottom() - attr.margin.bottom);

            const Size size((text.size() % 2 == 0 ? text.size() : text.size() + 1) / 2, 1);
            Point pos;

            if (attr.aligning & Alignings::TOP && attr.aligning & Alignings::BOTTOM) {
                // 垂直居中
                pos.y = boundary.top() + (boundary.height() - size.height) / 2;
            } else if (attr.aligning & Alignings::BOTTOM) {
                // 底部对齐
                pos.y = boundary.bottom() - size.height + 1;
            } else {
                // 顶部对齐
                pos.y = boundary.top();
            }

            if (attr.aligning & Alignings::LEFT && attr.aligning & Alignings::RIGHT) {
                // 水平居中
                pos.x = boundary.left() + (boundary.width() - size.width) / 2;
            } else if (attr.aligning & Alignings::RIGHT) {
                // 右对齐
                pos.x = boundary.right() - size.width + 1;
            } else {
                // 左对齐
                pos.x = boundary.left();
            }

            screen_.write(pos, text);
            return *this;
        }

    private:
        Screen &screen_;
    };
} // namespace kun::engine
