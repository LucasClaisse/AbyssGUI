#pragma once

#include "Color.hpp"
#include "Vector.hpp"

#include <string>

namespace Abyss {
    class IRenderer;
}

class Abyss::IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual auto color(const Color &color) -> void                                                                            = 0;
    virtual auto rectangle(const Vector3<double> &pos, const Vector3<double> &size) -> void                                   = 0;
    virtual auto line(const Vector3<double> &p1, const Vector3<double> &p2) -> void                                           = 0;
    virtual auto textColor(const Color &color) -> void                                                                        = 0;
    virtual auto text(const Vector3<double> &pos, const std::string &font, std::size_t size, const std::wstring &str) -> void = 0;
    virtual auto roundedRectangle(const Vector3<double> &pos, const Vector3<double> &size) -> void                            = 0;
};
