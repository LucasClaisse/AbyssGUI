#pragma once

#include "RelativeLayout.hpp"

#include <iostream>

namespace Abyss {
    namespace GUI {
        namespace Widgets {
            class WindowTitlebar;
            class WindowBody;
            class Window;
        }
    }
}

class Abyss::GUI::Widgets::WindowTitlebar final : public Widget {
private:
    bool            m_held{false};
    Vector3<double> m_heldPosition{};

public:
    WindowTitlebar();

    auto mouseButtonEvent(const InputDevice &device, InputDefinitions::MOUSE_BUTTON button, InputDefinitions::ACTION action) -> void final;

    auto isHeld() -> decltype(m_held);
    auto getHeldPosition() -> decltype(m_heldPosition);
};

inline Abyss::GUI::Widgets::WindowTitlebar::WindowTitlebar()
{
    setSize({0, 20});
}

inline auto Abyss::GUI::Widgets::WindowTitlebar::mouseButtonEvent(const InputDevice &device, InputDefinitions::MOUSE_BUTTON button, InputDefinitions::ACTION action) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};
    auto hovered{device.isHovering(pos, size)};

        std::cout << "wow" << std::endl;
    if (button == InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_LEFT && action == InputDefinitions::ACTION::ACTION_PRESS && !m_held) {
        m_held = hovered;
        if (m_held)
            m_heldPosition = device.getMousePosition() - pos;
    } else if (button == InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_LEFT && action == InputDefinitions::ACTION::ACTION_RELEASE && m_held)
        m_held = false;
}

inline auto Abyss::GUI::Widgets::WindowTitlebar::isHeld() -> decltype(m_held)
{
    return m_held;
}

inline auto Abyss::GUI::Widgets::WindowTitlebar::getHeldPosition() -> decltype(m_heldPosition)
{
    return m_heldPosition;
}

class Abyss::GUI::Widgets::WindowBody : public RelativeLayout {
public:
    auto paint(const InputDevice &device, double dt, Renderer &renderer) -> void final;
};

inline auto Abyss::GUI::Widgets::WindowBody::paint(const InputDevice &device, double, Renderer &renderer) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};

    renderer.setColor({255, 255, 255});
    renderer.drawRectangle(pos, size);

}

class Abyss::GUI::Widgets::Window final : public RelativeLayout {
private:
    WindowTitlebar *m_titlebar{nullptr};
    WindowBody *    m_body{nullptr};

public:
    Window();

    auto setSize(const decltype(m_size) &size) -> void final;

    auto think(const InputDevice &device, double dt) -> void final;
    auto paint(const InputDevice &device, double dt, Renderer &renderer) -> void final;

    auto getBody() const noexcept -> WindowBody &;
};

inline Abyss::GUI::Widgets::Window::Window()
{
    m_titlebar = &Layout::addChild<WindowTitlebar>();
    m_body     = &Layout::addChild<WindowBody>();
    m_body->setPosition(m_titlebar->getSize());
    setSize({300, 300});
}

inline auto Abyss::GUI::Widgets::Window::setSize(const decltype(m_size) &size) -> void
{
    auto height{m_titlebar->getSize().y};    // use child resize event

    m_size = size;
    if (m_size.y < height)
        m_size.y = height;

    m_titlebar->setSize({m_size.x, height});
    m_body->setSize({m_size.x, m_size.y - height});
}

inline auto Abyss::GUI::Widgets::Window::think(const InputDevice &device, double dt) -> void
{
    if (m_titlebar->isHeld())
        setPosition(device.getMousePosition() - m_titlebar->getHeldPosition());
}

inline auto Abyss::GUI::Widgets::Window::paint(const InputDevice &device, double dt, Renderer &renderer) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};

    renderer.setColor({0, 255, 255, 75});
    renderer.drawRectangle(pos, size);

    // m_body->paintDispatch(device, dt, renderer);
}

inline auto Abyss::GUI::Widgets::Window::getBody() const noexcept -> WindowBody &
{
    return *m_body;
}
