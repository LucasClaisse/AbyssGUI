#pragma once

#include "Widget.hpp"

#include <memory>
#include <vector>

namespace Abyss {
    namespace GUI {
        class Layout;
    }
}

class Abyss::GUI::Layout : public Widget {
public:
    auto addChild(ChildType &&widget) -> Child & override;
    auto deleteChild(const Child &child) -> void override;

    template <class T, typename... Ts>
    auto addChild(Ts &&... ts) -> T &;

    template <class T>
    auto addChild(ChildType child) -> T &;
};

inline auto Abyss::GUI::Layout::addChild(ChildType &&widget) -> Child &
{
    return Widget::addChild(std::move(widget));
}

inline auto Abyss::GUI::Layout::deleteChild(const Child &child) -> void
{
    Widget::deleteChild(child);
}

template <class T, typename... Ts>
inline auto Abyss::GUI::Layout::addChild(Ts &&... ts) -> T &
{
    return static_cast<T &>(addChild(std::make_unique<T>(std::forward<Ts>(ts)...)));
}

template <class T>
inline auto Abyss::GUI::Layout::addChild(ChildType child) -> T &
{
    return static_cast<T &>(addChild(std::move(child)));
}
