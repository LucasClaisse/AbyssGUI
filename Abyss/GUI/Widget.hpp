#pragma once

#include "Interfaces/InputDevice.hpp"
#include "Interfaces/Renderer.hpp"

#include <functional>

namespace Abyss {
    namespace GUI {
        class Widget;
    }
}

class Abyss::GUI::Widget {
protected:
    Widget *        m_parent{nullptr};
    bool            m_visible{true};
    bool            m_active{true};
    Vector3<double> m_position{};
    Vector3<double> m_size{};
    Vector3<double> m_rotation{};
    Vector3<double> m_scale{1, 1, 1};

    virtual auto think(const InputDevice &device, double dt) -> void;
    virtual auto paint(const InputDevice &device, double dt, IRenderer &renderer) -> void;
    virtual auto keyEvent(const InputDevice &device, KEY key, ACTION action, MODS mods) -> void;
    virtual auto characterEvent(const InputDevice &device, wchar_t codepoint) -> void;
    virtual auto mouseButtonEvent(const InputDevice &device, MOUSE button, ACTION action, MODS mods) -> void;
    virtual auto scrollEvent(const InputDevice &device, const Vector3<double> &offset) -> void;

public:
    [[nodiscard]] virtual auto getParent() const -> decltype(m_parent);
    virtual auto               setParent(decltype(m_parent) parent) -> void;
    [[nodiscard]] virtual auto isVisible() const -> decltype(m_visible);
    virtual auto               setVisible(decltype(m_visible) visible) -> void;
    [[nodiscard]] virtual auto isActive() const -> decltype(m_active);
    virtual auto               setActive(decltype(m_active) active) -> void;
    [[nodiscard]] virtual auto getPosition(bool relative = true) const -> decltype(m_position);
    virtual auto               setPosition(decltype(m_position) position) -> void;
    [[nodiscard]] virtual auto getSize() const -> decltype(m_size);
    virtual auto               setSize(decltype(m_size) size) -> void;
    [[nodiscard]] virtual auto getRotation(bool relative = true) const -> decltype(m_rotation);
    virtual auto               setRotation(decltype(m_rotation) rotation) -> void;
    [[nodiscard]] virtual auto getScale(bool relative = true) const -> decltype(m_scale);
    virtual auto               setScale(decltype(m_scale) scale) -> void;
};

inline auto Abyss::GUI::Widget::getParent() const -> decltype(m_parent)
{
    return m_parent;
}

inline auto Abyss::GUI::Widget::setParent(decltype(m_parent) parent) -> void
{
    m_parent = parent;
}

inline auto Abyss::GUI::Widget::isVisible() const -> decltype(m_visible)
{
    if (m_parent != nullptr && !m_parent->isVisible())
        return false;
    return m_visible;
}

inline auto Abyss::GUI::Widget::setVisible(decltype(m_visible) visible) -> void
{
    m_visible = visible;
}

inline auto Abyss::GUI::Widget::isActive() const -> decltype(m_active)
{
    if (m_parent != nullptr && !m_parent->isActive())
        return false;
    return m_active;
}

inline auto Abyss::GUI::Widget::setActive(decltype(m_active) active) -> void
{
    m_active = active;
}

inline auto Abyss::GUI::Widget::getPosition(bool relative) const -> decltype(m_position)
{
    if (m_parent != nullptr && relative)
        return m_parent->getPosition() + m_position;
    return m_position;
}

inline auto Abyss::GUI::Widget::setPosition(decltype(m_position) position) -> void
{
    m_position = position;
}

inline auto Abyss::GUI::Widget::getSize() const -> decltype(m_size)
{
    return m_size;
}

inline auto Abyss::GUI::Widget::setSize(decltype(m_size) size) -> void
{
    m_size = size;
}

inline auto Abyss::GUI::Widget::getRotation(bool relative) const -> decltype(m_rotation)
{
    if (m_parent != nullptr && relative)
        return m_parent->getRotation() + m_rotation;
    return m_rotation;
}

inline auto Abyss::GUI::Widget::setRotation(decltype(m_rotation) rotation) -> void
{
    m_rotation = rotation;
}

inline auto Abyss::GUI::Widget::getScale(bool relative) const -> decltype(m_scale)
{
    if (m_parent != nullptr && relative)
        return m_parent->getScale() * m_scale;
    return m_scale;
}

inline auto Abyss::GUI::Widget::setScale(decltype(m_scale) scale) -> void
{
    m_scale = scale;
}

namespace Abyss {
    class Widget;
}

class Abyss::Widget {
protected:
    Widget *        m_parent{nullptr};
    Vector3<double> m_position{};
    Vector3<double> m_size{};
    bool            m_visible{true};
    bool            m_active{true};

public:
    Widget(decltype(m_parent) parent = nullptr);
    virtual ~Widget() = default;

    [[nodiscard]] virtual auto getParent() const noexcept -> decltype(m_parent);
    virtual auto               setParent(decltype(m_parent) parent) noexcept -> void;
    [[nodiscard]] virtual auto getPosition(const bool relative = true) const noexcept -> decltype(m_position);
    virtual auto               setPosition(const decltype(m_position) &position) noexcept -> void;
    [[nodiscard]] virtual auto getSize() const noexcept -> decltype(m_size);
    virtual auto               setSize(const decltype(m_size) &size) -> void;
    [[nodiscard]] virtual auto isVisible() const noexcept -> decltype(m_visible);
    virtual auto               setVisible(const decltype(m_visible) visible) -> void;
    [[nodiscard]] virtual auto isActive() const noexcept -> decltype(m_active);
    virtual auto               setActive(const decltype(m_active) active) -> void;

    virtual auto think(const InputDevice &mouse, double dt) -> void;
    virtual auto paint(const AMouse &mouse, double dt, IRenderer &renderer) -> void;
    virtual auto keyEvent(const AMouse &mouse, KEY key, ACTION action, MODS mods) -> void;
    virtual auto characterEvent(const AMouse &mouse, wchar_t codepoint) -> void;
    virtual auto mouseButtonEvent(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void;
    virtual auto scrollEvent(const AMouse &mouse, const Vector3<double> &offset) -> void;

    virtual auto thinkDispatch(const AMouse &mouse, double dt) -> void;
    virtual auto paintDispatch(const AMouse &mouse, double dt, IRenderer &renderer) -> void;
    virtual auto keyEventDispatch(const AMouse &mouse, KEY key, ACTION action, MODS mods) -> void;
    virtual auto characterEventDispatch(const AMouse &mouse, wchar_t codepoint) -> void;
    virtual auto mouseButtonEventDispatch(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void;
    virtual auto scrollEventDispatch(const AMouse &mouse, const Vector3<double> &offset) -> void;
};

inline Abyss::Widget::Widget(decltype(m_parent) parent)
    : m_parent{parent}
{
}

[[nodiscard]] inline auto Abyss::Widget::getParent() const noexcept -> decltype(m_parent)
{
    return m_parent;
}

inline auto Abyss::Widget::setParent(decltype(m_parent) parent) noexcept -> void
{
    m_parent = parent;
}

[[nodiscard]] inline auto Abyss::Widget::getPosition(const bool relative) const noexcept -> decltype(m_position)
{
    if (m_parent != nullptr && relative)
        return m_parent->getPosition() + m_position;
    return m_position;
}

inline auto Abyss::Widget::setPosition(const decltype(m_position) &position) noexcept -> void
{
    m_position = position;
}

[[nodiscard]] inline auto Abyss::Widget::getSize() const noexcept -> decltype(m_size)
{
    return m_size;
}

inline auto Abyss::Widget::setSize(const decltype(m_size) &size) -> void
{
    m_size = size;
}

[[nodiscard]] inline auto Abyss::Widget::isVisible() const noexcept -> decltype(m_visible)
{
    if (m_parent != nullptr && !m_parent->isVisible())
        return false;
    return m_visible;
}

inline auto Abyss::Widget::setVisible(const decltype(m_visible) visible) -> void
{
    m_visible = visible;
}

[[nodiscard]] inline auto Abyss::Widget::isActive() const noexcept -> decltype(m_active)
{
    if (m_parent != nullptr && !m_parent->isActive())
        return false;
    return m_active;
}

inline auto Abyss::Widget::setActive(const decltype(m_active) active) -> void
{
    m_active = active;
}

inline auto Abyss::Widget::think(const AMouse &mouse, double dt) -> void
{
}

inline auto Abyss::Widget::paint(const AMouse &mouse, double dt, IRenderer &renderer) -> void
{
}

inline auto Abyss::Widget::keyEvent(const AMouse &mouse, KEY key, ACTION action, MODS mods) -> void
{
}

inline auto Abyss::Widget::characterEvent(const AMouse &mouse, wchar_t codepoint) -> void
{
}

inline auto Abyss::Widget::mouseButtonEvent(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void
{
}

inline auto Abyss::Widget::scrollEvent(const AMouse &mouse, const Vector3<double> &offset) -> void
{
}

inline auto Abyss::Widget::thinkDispatch(const AMouse &mouse, double dt) -> void
{
    if (m_active)
        think(mouse, dt);
}

inline auto Abyss::Widget::paintDispatch(const AMouse &mouse, double dt, IRenderer &renderer) -> void
{
    if (m_visible)
        paint(mouse, dt, renderer);
}

inline auto Abyss::Widget::keyEventDispatch(const AMouse &mouse, KEY key, ACTION action, MODS mods) -> void
{
    if (m_active)
        keyEvent(mouse, key, action, mods);
}

inline auto Abyss::Widget::characterEventDispatch(const AMouse &mouse, wchar_t codepoint) -> void
{
    if (m_active)
        characterEvent(mouse, codepoint);
}

inline auto Abyss::Widget::mouseButtonEventDispatch(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void
{
    if (m_active)
        mouseButtonEvent(mouse, button, action, mods);
}

inline auto Abyss::Widget::scrollEventDispatch(const AMouse &mouse, const Vector3<double> &offset) -> void
{
    if (m_active)
        scrollEvent(mouse, offset);
}
