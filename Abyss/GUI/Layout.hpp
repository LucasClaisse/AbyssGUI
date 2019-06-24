#pragma once

#include "Widget.hpp"

#include <vector>

namespace Abyss {
    class Layout;
}

class Abyss::Layout : public Widget {
protected:
    using Child     = Widget;
    using ChildType = std::unique_ptr<Child>;

    std::vector<ChildType> m_children{};

    virtual auto childrenUpdate() -> void = 0;

public:
    template <class T, typename... Ts>
    auto addChild(Ts &&... ts) -> T &;

    template <class T>
    auto addChild(ChildType child) -> T &;

    virtual auto addChild(ChildType child) -> Child &;
    virtual auto delChild(Child *child) -> void;

    virtual auto onChildResize() -> void;

    auto thinkDispatch(const AMouse &mouse, double dt) -> void override;
    auto paintDispatch(const AMouse &mouse, double dt, IRenderer &renderer) -> void override;
    auto keyEventDispatch(const AMouse &mouse, KEY key, ACTION action, MODS mods) -> void override;
    auto characterEventDispatch(const AMouse &mouse, wchar_t codepoint) -> void override;
    auto mouseButtonEventDispatch(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void override;
    auto scrollEventDispatch(const AMouse &mouse, const Vector3<double> &offset) -> void override;
};

template <class T, typename... Ts>
inline auto Abyss::Layout::addChild(Ts &&... ts) -> T &
{
	return static_cast<T&>(addChild(std::make_unique<T>(std::forward<Ts>(ts)...)));
}

template <class T>
inline auto Abyss::Layout::addChild(ChildType child) -> T &
{
	return static_cast<T&>(addChild(std::move(child)));
}

inline auto Abyss::Layout::addChild(ChildType child) -> Child &
{
    if (child == nullptr)
        throw std::runtime_error{""};

    m_children.emplace_back(std::move(child));
    auto &ret{*m_children.back()};
    ret.setParent(this);
    childrenUpdate();
    return ret;
}

inline auto Abyss::Layout::delChild(Child *child) -> void
{
    for (auto it{m_children.cbegin()}; it != m_children.cend();) {
        auto &ptr{*it};
        if (ptr.get() == child) {
            m_children.erase(it);
            return;
        } else
            ++it;
    }
}

inline auto Abyss::Layout::onChildResize() -> void
{

}

inline auto Abyss::Layout::thinkDispatch(const AMouse &mouse, double dt) -> void
{
    for (const auto &widget : m_children)
        widget->thinkDispatch(mouse, dt);

    Widget::thinkDispatch(mouse, dt);
}

inline auto Abyss::Layout::paintDispatch(const AMouse &mouse, double dt, IRenderer &renderer) -> void
{
    Widget::paintDispatch(mouse, dt, renderer);

    for (const auto &widget : m_children)
        widget->paintDispatch(mouse, dt, renderer);
}

inline auto Abyss::Layout::keyEventDispatch(const AMouse &mouse, KEY key, ACTION action, MODS mods) -> void
{
    Widget::keyEventDispatch(mouse, key, action, mods);

    for (const auto &widget : m_children)
        widget->keyEventDispatch(mouse, key, action, mods);
}

inline auto Abyss::Layout::characterEventDispatch(const AMouse &mouse, wchar_t codepoint) -> void
{
    Widget::characterEventDispatch(mouse, codepoint);

    for (const auto &widget : m_children)
        widget->characterEventDispatch(mouse, codepoint);
}

inline auto Abyss::Layout::mouseButtonEventDispatch(const AMouse &mouse, MOUSE button, ACTION action, MODS mods) -> void
{
    Widget::mouseButtonEventDispatch(mouse, button, action, mods);

    for (const auto &widget : m_children)
        widget->mouseButtonEventDispatch(mouse, button, action, mods);
}

inline auto Abyss::Layout::scrollEventDispatch(const AMouse &mouse, const Vector3<double> &offset) -> void
{
    Widget::scrollEventDispatch(mouse, offset);

    for (const auto &widget : m_children)
        widget->scrollEventDispatch(mouse, offset);
}
