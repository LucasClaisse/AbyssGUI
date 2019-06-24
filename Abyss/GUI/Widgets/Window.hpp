#pragma once

#include "RelativeLayout.hpp"

namespace Abyss {
    namespace Widgets {
        class WindowTitlebar;
        class WindowBody;
        class Window;
    }
}

class Abyss::Widgets::WindowTitlebar final : public Widget {
private:
    bool            m_held{false};
    Vector3<double> m_heldPosition{};

public:
    WindowTitlebar();

    // auto paint(const AMouse &mouse, double dt, IRenderer &renderer) -> void final;
    auto mouseButtonEvent(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void final;

    auto isHeld() -> decltype(m_held);
    auto getHeldPosition() -> decltype(m_heldPosition);
};

inline Abyss::Widgets::WindowTitlebar::WindowTitlebar()
{
    setSize({0, 20});
}

inline auto Abyss::Widgets::WindowTitlebar::mouseButtonEvent(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};
    auto hovered{mouse.isHovering(pos, size)};

    if (button == MOUSE::MOUSE_BUTTON_LEFT && action == ACTION::ACTION_PRESS && !m_held) {
        m_held = hovered;
        if (m_held)
            m_heldPosition = mouse.getPosition() - pos;
    } else if (button == MOUSE::MOUSE_BUTTON_LEFT && action == ACTION::ACTION_RELEASE && m_held)
        m_held = false;
}

inline auto Abyss::Widgets::WindowTitlebar::isHeld() -> decltype(m_held)
{
    return m_held;
}

inline auto Abyss::Widgets::WindowTitlebar::getHeldPosition() -> decltype(m_heldPosition)
{
    return m_heldPosition;
}

// inline auto Abyss::Widgets::WindowTitlebar::paint(const AMouse &, double, IRenderer &renderer) -> void
// {
//     auto pos{getPosition()};
//     auto size{getSize()};

//     renderer.color({0, 255, 0});
//     renderer.rectangle(pos, size);
// }

class Abyss::Widgets::WindowBody : public RelativeLayout {
public:
    auto paint(const AMouse &mouse, double dt, IRenderer &renderer) -> void final;
};

inline auto Abyss::Widgets::WindowBody::paint(const AMouse &, double, IRenderer &renderer) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};

    renderer.color({255, 255, 255});
    renderer.roundedRectangle(pos, size);
}

class Abyss::Widgets::Window final : public RelativeLayout {
private:
    WindowTitlebar *m_titlebar{nullptr};
    WindowBody *    m_body{nullptr};

    auto addChild(ChildType child) -> Child & final;
    auto delChild(Child *child) -> void final;

public:
    Window();

    auto setSize(const decltype(m_size) &size) -> void final;

    auto think(const AMouse &mouse, double dt) -> void final;
    auto paint(const AMouse &mouse, double dt, IRenderer &renderer) -> void final;

	auto getBody() const noexcept -> WindowBody &;
};

auto Abyss::Widgets::Window::addChild(ChildType child) -> Child &
{
	return Layout::addChild(std::move(child));
}

auto Abyss::Widgets::Window::delChild(Child *child) -> void
{
	Layout::delChild(child);
}

inline Abyss::Widgets::Window::Window()
{
    m_titlebar = &Abyss::Layout::addChild<WindowTitlebar>();
    m_body     = &Abyss::Layout::addChild<WindowBody>();
    m_body->setPosition(m_titlebar->getSize());
    setSize({300, 300});
}

inline auto Abyss::Widgets::Window::setSize(const decltype(m_size) &size) -> void
{
    auto height{m_titlebar->getSize().y};    // use child resize event

    m_size = size;
    if (m_size.y < height)
        m_size.y = height;

    m_titlebar->setSize({m_size.x, height});
    m_body->setSize({m_size.x, m_size.y - height});
}

inline auto Abyss::Widgets::Window::think(const AMouse &mouse, double dt) -> void
{
    if (m_titlebar->isHeld())
        setPosition(mouse.getPosition() - m_titlebar->getHeldPosition());
}

inline auto Abyss::Widgets::Window::paint(const AMouse &mouse, double dt, IRenderer &renderer) -> void
{
	auto pos{getPosition()};
	auto size{getSize()};

	renderer.color({255, 255, 255, 75});
	renderer.roundedRectangle(pos, size);
}

inline auto Abyss::Widgets::Window::getBody() const noexcept -> WindowBody &
{
	return *m_body;
}
