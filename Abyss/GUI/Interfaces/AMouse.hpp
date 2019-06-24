#pragma once

#include "Input.hpp"
#include "Abyss/Vector.hpp"

#include <array>
#include <functional>

namespace Abyss {
    class AMouse;
}

class Abyss::AMouse {
protected:
    using Position = Vector3<double>;

    Position                                                                    m_position{};
    std::array<bool, static_cast<std::size_t>(Abyss::MOUSE::MOUSE_BUTTON_LAST)> m_status{};

public:
    virtual ~AMouse() = default;

    virtual auto       update() -> void = 0;
    [[nodiscard]] auto getPosition() const noexcept -> const decltype(m_position) &;
    auto               isHovering(const Position &pos, const Position &size, bool relative = true) const noexcept -> bool;
    auto               onButtonActionDispatch(MOUSE button, ACTION action) const -> void;

    std::function<void(const AMouse &, MOUSE button, ACTION action)> onButtonAction{};
};

[[nodiscard]] inline auto Abyss::AMouse::getPosition() const noexcept -> const decltype(m_position) &
{
    return m_position;
}

inline auto Abyss::AMouse::isHovering(const Position &pos, const Position &size, bool relative) const noexcept -> bool
{
    auto sizeRelative{relative ? (pos + size) : size};
    return m_position.x >= pos.x && m_position.y >= pos.y && m_position.x <= sizeRelative.x && m_position.y <= sizeRelative.y;
}

inline auto Abyss::AMouse::onButtonActionDispatch(MOUSE button, ACTION action) const -> void
{
    if (onButtonAction)
        onButtonAction(*this, button, action);
}
