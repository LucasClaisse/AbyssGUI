#pragma once

#include "Abyss/Color.hpp"
#include "Abyss/Vector.hpp"

#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace Abyss {
    namespace GUI {
        class Renderer;
    }
}

class Abyss::GUI::Renderer {
protected:
    using Vertex          = Vector3<double>;
    using Vertices        = std::vector<Vertex>;
    using ColoredVertex   = std::pair<Vertex, std::optional<Color>>;
    using ColoredVertices = std::vector<ColoredVertex>;

    Color m_currentImmediateColor{255, 255, 255, 255};

public:
    virtual ~Renderer() = default;

    virtual auto drawVertices(const Vertices &vertices, const Color &col) -> void                                                                              = 0;
    virtual auto drawColoredVertices(const ColoredVertices &vertices) -> void                                                                                  = 0;
    virtual auto drawText(const std::wstring &wstr, const Vector3<double> &position, const std::string &fontName, const double size, const Color &col) -> void = 0;

    virtual auto setColor(const Color &col) -> void;
    virtual auto drawRectangle(const Vector3<double> &pos, const Vector3<double> &size) -> void;
};

auto Abyss::GUI::Renderer::setColor(const Color &col) -> void
{
    m_currentImmediateColor = col;
}

auto Abyss::GUI::Renderer::drawRectangle(const Vector3<double> &pos, const Vector3<double> &size) -> void
{
    drawVertices({pos + Vector3<double>{0, 0, 0}, pos + Vector3<double>{0, size.y, 0}, pos + Vector3<double>{size.x, size.y, 0}, pos + Vector3<double>{size.x, 0, 0}}, m_currentImmediateColor);
}
