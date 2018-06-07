using Int = int16_t;

struct Size {
    Size() = default;
    Size(const Int width, const Int height) : width(width), height(height) {}

    Int width = 0;
    Int height = 0;

    bool operator==(const Size &other) const { return width == other.width && height == other.height; }
    bool operator<(const Size &other) const { return width * height < other.width * other.height; }
    bool operator<=(const Size &other) const { return *this < other || *this == other; }
};
