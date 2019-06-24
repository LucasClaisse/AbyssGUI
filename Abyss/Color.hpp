#pragma once

class Color final {
public:
    unsigned char r{255};
    unsigned char g{255};
    unsigned char b{255};
    unsigned char a{255};

    Color(decltype(r) _r, decltype(g) _g, decltype(b) _b, decltype(a) _a = 255);
};

inline Color::Color(decltype(r) _r, decltype(g) _g, decltype(b) _b, decltype(a) _a)
    : r{_r}, g{_g}, b{_b}, a{_a}
{
}
