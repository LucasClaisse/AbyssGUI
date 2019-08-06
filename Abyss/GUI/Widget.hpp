#pragma once

#include "Interfaces/InputDevice.hpp"
#include "Interfaces/Renderer.hpp"

#include <functional>
#include <memory>

namespace Abyss {
    namespace GUI {
        class Widget;
    }
}

/*
	To implement:
	- Rotation
	- Scale
	- Padding
	- Margin
	- Spacing (Layout only?)
*/

class Abyss::GUI::Widget {
public:
    enum class Type : uint8_t {
        Relative,
        Absolute,
        Percentage
    };

protected:
    using Child     = Widget;
    using ChildType = std::unique_ptr<Child>;

    Widget *               m_parent{nullptr};
    bool                   m_visible{true};
    bool                   m_active{true};
    Vector3<double>        m_position{};
    Vector3<double>        m_size{};
    Vector3<double>        m_baseSize{100, 100};
    Vector3<double>        m_rotation{};
    Vector3<double>        m_scale{1, 1, 1};
    Vector3<double>        m_padding{};
    Vector3<double>        m_margin{};
    std::vector<ChildType> m_children{};

    virtual auto think(const InputDevice &device, double dt) -> void;
    virtual auto paint(const InputDevice &device, double dt, Renderer &renderer) -> void;
    virtual auto keyEvent(const InputDevice &device, InputDefinitions::KEY key, InputDefinitions::ACTION action) -> void;
    virtual auto characterEvent(const InputDevice &device, wchar_t codepoint) -> void;
    virtual auto mouseButtonEvent(const InputDevice &device, InputDefinitions::MOUSE_BUTTON button, InputDefinitions::ACTION action) -> void;
    virtual auto scrollEvent(const InputDevice &device, const Vector3<double> &offset) -> void;
    virtual auto addChild(ChildType &&widget) -> Child &;
    virtual auto deleteChild(const Child &child) -> void;
    virtual auto onChildAdded(const Child &child) -> void;
    virtual auto onChildDeleted(const Child &child) -> void;
    virtual auto onChildChange(const Child &child) -> void;

public:
    virtual ~Widget() = default;

    [[nodiscard]] virtual auto getParent() const -> decltype(m_parent);
    virtual auto               setParent(decltype(m_parent) parent) -> void;
    [[nodiscard]] virtual auto isVisible() const -> decltype(m_visible);
    virtual auto               setVisible(decltype(m_visible) visible) -> void;
    [[nodiscard]] virtual auto isActive() const -> decltype(m_active);
    virtual auto               setActive(decltype(m_active) active) -> void;
    [[nodiscard]] virtual auto getPosition(bool relative = true) const -> decltype(m_position);
    virtual auto               setPosition(const decltype(m_position) &position) -> void;
    [[nodiscard]] virtual auto getSize() const -> decltype(m_size);
    virtual auto               setSize(const decltype(m_size) &size) -> void;
    [[nodiscard]] virtual auto getBaseSize() const -> decltype(m_baseSize);
    virtual auto               setBaseSize(const decltype(m_baseSize) &baseSize) -> void;
    [[nodiscard]] virtual auto getRotation(bool relative = true) const -> decltype(m_rotation);
    virtual auto               setRotation(const decltype(m_rotation) &rotation) -> void;
    [[nodiscard]] virtual auto getScale(bool relative = true) const -> decltype(m_scale);
    virtual auto               setScale(const decltype(m_scale) &scale) -> void;
    [[nodiscard]] virtual auto getPadding() const -> decltype(m_padding);
    virtual auto               setPadding(const decltype(m_padding) &padding) -> void;
    [[nodiscard]] virtual auto getMargin() const -> decltype(m_margin);
    virtual auto               setMargin(const decltype(m_margin) &margin) -> void;
    virtual auto               thinkDispatch(const InputDevice &device, double dt) -> void;
    virtual auto               paintDispatch(const InputDevice &device, double dt, Renderer &renderer) -> void;
    virtual auto               keyEventDispatch(const InputDevice &device, InputDefinitions::KEY key, InputDefinitions::ACTION action) -> void;
    virtual auto               characterEventDispatch(const InputDevice &device, wchar_t codepoint) -> void;
    virtual auto               mouseButtonEventDispatch(const InputDevice &device, InputDefinitions::MOUSE_BUTTON button, InputDefinitions::ACTION action) -> void;
    virtual auto               scrollEventDispatch(const InputDevice &device, const Vector3<double> &offset) -> void;
    virtual auto               registerOnInputDevice(InputDevice &device) -> void;
};

inline auto Abyss::GUI::Widget::registerOnInputDevice(InputDevice &deviceToRegister) -> void
{
    deviceToRegister.m_keyEvent = [this](const InputDevice &device, InputDefinitions::KEY key, InputDefinitions::ACTION action) {
        keyEventDispatch(device, key, action);
    };

    deviceToRegister.m_characterEvent = [this](const InputDevice &device, wchar_t codepoint) {
        characterEventDispatch(device, codepoint);
    };

    deviceToRegister.m_mouseButtonEvent = [this](const InputDevice &device, InputDefinitions::MOUSE_BUTTON button, InputDefinitions::ACTION action) {
        mouseButtonEventDispatch(device, button, action);
    };

    deviceToRegister.m_scrollEvent = [this](const InputDevice &device, const Vector3<double> &offset) {
        scrollEventDispatch(device, offset);
    };
}

inline auto Abyss::GUI::Widget::think(const InputDevice &device, double dt) -> void
{
}

inline auto Abyss::GUI::Widget::paint(const InputDevice &device, double dt, Renderer &renderer) -> void
{
}

inline auto Abyss::GUI::Widget::keyEvent(const InputDevice &device, InputDefinitions::KEY key, InputDefinitions::ACTION action) -> void
{
}

inline auto Abyss::GUI::Widget::characterEvent(const InputDevice &device, wchar_t codepoint) -> void
{
}

inline auto Abyss::GUI::Widget::mouseButtonEvent(const InputDevice &device, InputDefinitions::MOUSE_BUTTON button, InputDefinitions::ACTION action) -> void
{
}

inline auto Abyss::GUI::Widget::scrollEvent(const InputDevice &device, const Vector3<double> &offset) -> void
{
}

inline auto Abyss::GUI::Widget::addChild(ChildType &&widget) -> Child &
{
    if (widget == nullptr)
        throw std::runtime_error{"Couldn't add an invalid child to Layout"};

    m_children.emplace_back(std::move(widget));
    auto &reference{*m_children.back()};
    reference.setParent(this);
    onChildAdded(reference);
    onChildChange(reference);
    return reference;
}

inline auto Abyss::GUI::Widget::deleteChild(const Child &child) -> void
{
    for (auto it{m_children.cbegin()}; it != m_children.cend();) {
        auto &ptr{*it};
        if (ptr.get() == &child) {
            m_children.erase(it);
            return;
        } else
            ++it;
    }
}

inline auto Abyss::GUI::Widget::onChildAdded(const Child &child) -> void
{
}

inline auto Abyss::GUI::Widget::onChildDeleted(const Child &child) -> void
{
}

inline auto Abyss::GUI::Widget::onChildChange(const Child &child) -> void
{
}

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

inline auto Abyss::GUI::Widget::setPosition(const decltype(m_position) &position) -> void
{
    m_position = position;
}

inline auto Abyss::GUI::Widget::getSize() const -> decltype(m_size)
{
    return m_size;
}

inline auto Abyss::GUI::Widget::setSize(const decltype(m_size) &size) -> void
{
    m_size = size;
}

inline auto Abyss::GUI::Widget::getBaseSize() const -> decltype(m_baseSize)
{
    return m_baseSize;
}

inline auto Abyss::GUI::Widget::setBaseSize(const decltype(m_baseSize) &baseSize) -> void
{
    m_baseSize = baseSize;
}

inline auto Abyss::GUI::Widget::getRotation(bool relative) const -> decltype(m_rotation)
{
    if (m_parent != nullptr && relative)
        return m_parent->getRotation() + m_rotation;

    return m_rotation;
}

inline auto Abyss::GUI::Widget::setRotation(const decltype(m_rotation) &rotation) -> void
{
    m_rotation = rotation;
}

inline auto Abyss::GUI::Widget::getScale(bool relative) const -> decltype(m_scale)
{
    if (m_parent != nullptr && relative)
        return m_parent->getScale() * m_scale;

    return m_scale;
}

inline auto Abyss::GUI::Widget::setScale(const decltype(m_scale) &scale) -> void
{
    m_scale = scale;
}

inline auto Abyss::GUI::Widget::getPadding() const -> decltype(m_padding)
{
    return m_padding;
}

inline auto Abyss::GUI::Widget::setPadding(const decltype(m_padding) &padding) -> void
{
    m_padding = padding;
}

inline auto Abyss::GUI::Widget::getMargin() const -> decltype(m_margin)
{
    return m_margin;
}

inline auto Abyss::GUI::Widget::setMargin(const decltype(m_margin) &margin) -> void
{
    m_margin = margin;
}

inline auto Abyss::GUI::Widget::thinkDispatch(const InputDevice &device, double dt) -> void
{
    if (!m_active)
        return;

    for (const auto &widget : m_children)
        widget->thinkDispatch(device, dt);

    think(device, dt);
}

inline auto Abyss::GUI::Widget::paintDispatch(const InputDevice &device, double dt, Renderer &renderer) -> void
{
    if (!m_visible)
        return;

    paint(device, dt, renderer);

    for (const auto &widget : m_children)
        widget->paintDispatch(device, dt, renderer);
}

inline auto Abyss::GUI::Widget::keyEventDispatch(const InputDevice &device, InputDefinitions::KEY key, InputDefinitions::ACTION action) -> void
{
    if (!m_active)
        return;

    for (const auto &widget : m_children)
        widget->keyEventDispatch(device, key, action);

    keyEvent(device, key, action);
}

inline auto Abyss::GUI::Widget::characterEventDispatch(const InputDevice &device, wchar_t codepoint) -> void
{
    if (!m_active)
        return;

    for (const auto &widget : m_children)
        widget->characterEventDispatch(device, codepoint);

    characterEvent(device, codepoint);
}

inline auto Abyss::GUI::Widget::mouseButtonEventDispatch(const InputDevice &device, InputDefinitions::MOUSE_BUTTON button, InputDefinitions::ACTION action) -> void
{
    if (!m_active)
        return;

    for (const auto &widget : m_children)
        widget->mouseButtonEventDispatch(device, button, action);

    mouseButtonEvent(device, button, action);
}

inline auto Abyss::GUI::Widget::scrollEventDispatch(const InputDevice &device, const Vector3<double> &offset) -> void
{
    if (!m_active)
        return;

    for (const auto &widget : m_children)
        widget->scrollEventDispatch(device, offset);

    scrollEvent(device, offset);
}
