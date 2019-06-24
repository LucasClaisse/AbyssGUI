#pragma once

#include "Abyss/GUI/Widget.hpp"

namespace Abyss {
    namespace Widgets {
        class Checkbox;
    }
}

class Abyss::Widgets::Checkbox final : public Widget {
private:
    bool &m_variable;
    bool  m_holding{false};
	std::wstring m_text{L"Sample Text"};

public:
    Checkbox(decltype(m_variable) variable, const decltype(m_text) &text = L"Sample Text");

    auto paint(const AMouse &mouse, double dt, IRenderer &renderer) -> void final;
    auto mouseButtonEvent(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void final;
};

inline Abyss::Widgets::Checkbox::Checkbox(decltype(m_variable) variable, const decltype(m_text) &text)
    : m_variable{variable}, m_text{text}
{
    setSize({20, 20});
}

auto Abyss::Widgets::Checkbox::paint(const AMouse &mouse, double dt, IRenderer &renderer) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};
    auto hovered{mouse.isHovering(pos, size)};

    static Color shadowColor{0, 0, 0, 255 / 10};
    static Color backgroundColor{255, 255, 255, 255};
    static Color accentColor{255, 255, 255, 255};

    renderer.color(shadowColor);
    renderer.roundedRectangle({pos.x - 1, pos.y - 1}, {size.x + 2, size.y + 4});

    renderer.color(backgroundColor);
    renderer.roundedRectangle(pos, size);

    Color overlayColor{0, 0, 0, static_cast<unsigned char>(hovered ? shadowColor.a : 0)};
    if (m_holding)
        overlayColor.a = static_cast<unsigned char>(overlayColor.a * 1.5);

    renderer.color(overlayColor);
    renderer.roundedRectangle(pos, size);

    if (m_variable) {
        renderer.color(shadowColor);
        renderer.roundedRectangle({pos.x + 2, pos.y + 2}, {size.x - 4, size.y - 4});

        renderer.color({250, 250, 250, 255});
        renderer.roundedRectangle({pos.x + 3, pos.y + 3}, {size.x - 6, size.y - 6});
    }

	renderer.textColor({0, 0, 0, 255});
	renderer.text(pos + Vector3<double>{size.x + size.y * 0.25, (size.y / 2) - (size.y / 2) - 1}, "OpenSans-Regular.ttf", 15, m_text);
}

auto Abyss::Widgets::Checkbox::mouseButtonEvent(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};
    auto hovered{mouse.isHovering(pos, size)};

    if (button == MOUSE::MOUSE_BUTTON_LEFT && action == ACTION::ACTION_PRESS) {
        m_holding = hovered;
    } else if (button == MOUSE::MOUSE_BUTTON_LEFT && action == ACTION::ACTION_RELEASE) {
        if (m_holding && hovered)
            m_variable = !m_variable;
        m_holding = false;
    }
}
