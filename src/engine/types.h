#pragma once

#include <Windows.h>
#include <cstdint>

namespace kun::engine {
    using Int = int16_t;

    struct Point {
        Point() = default;
        Point(const Int x, const Int y) : x(x), y(y) {}

        Int x = 0;
        Int y = 0;

        bool operator==(const Point &other) const { return x == other.x && y == other.y; }
    };

    struct Size {
        Size() = default;
        Size(const Int width, const Int height) : width(width), height(height) {}

        Int width = 0;
        Int height = 0;

        bool operator==(const Size &other) const { return width == other.width && height == other.height; }
        bool operator<(const Size &other) const { return width * height < other.width * other.height; }
        bool operator<=(const Size &other) const { return *this < other || *this == other; }
    };

    struct Rect {
        Rect() = default;
        Rect(const Point &p1, const Point &p2) : Rect(p1.x, p1.y, p2.x, p2.y) {}
        Rect(const Point &origin, const Size &size)
            : Rect(origin.x, origin.y, origin.x + size.width, origin.y + size.height) {}

        Rect(const Int x1, const Int y1, const Int x2, const Int y2) {
            top_left_.x = min(x1, x2);
            top_left_.y = min(y1, y2);
            bottom_right_.x = max(x1, x2);
            bottom_right_.y = max(y1, y2);
        }

        Int left() const { return top_left_.x; }
        Int right() const { return bottom_right_.x; }
        Int top() const { return top_left_.y; }
        Int bottom() const { return bottom_right_.y; }

        Int width() const { return right() - left() + 1; }
        Int height() const { return bottom() - top() + 1; }
        Size size() const { return Size(width(), height()); }
        Int area() const { return width() * height(); }

        Point top_left() const { return top_left_; }
        Point top_right() const { return Point(right(), top()); }
        Point bottom_left() const { return Point(left(), bottom()); }
        Point bottom_right() const { return bottom_right_; }

        Rect center_rect() const {
            return Rect(Point((left() + right()) / 2, (top() + bottom()) / 2),
                        Point((left() + right() + 1) / 2, (top() + bottom() + 1) / 2));
        }
        Point center() const { return center_rect().bottom_right(); }

        bool operator==(const Rect &other) const {
            return top_left_ == other.top_left_ && bottom_right_ == other.bottom_right_;
        }

    private:
        Point top_left_{0, 0};
        Point bottom_right_{0, 0};
    };

    using Color = uint8_t;

    struct Colors {
        static const Color BLACK = 0x0;
        static const Color BLUE = 0x1;
        static const Color GREEN = 0x2;
        static const Color RED = 0x4;
        static const Color INTENSITY = 0x8;

        static const Color CYAN = GREEN | BLUE;
        static const Color PURPLE = RED | BLUE;
        static const Color YELLOW = RED | GREEN;
        static const Color WHITE = RED | GREEN | BLUE | INTENSITY;

        static Color combine(const Color bg_color, const Color fg_color) {
            return (bg_color & 0xF) << 4 | fg_color & 0xF;
        }
    };
} // namespace kun::engine
