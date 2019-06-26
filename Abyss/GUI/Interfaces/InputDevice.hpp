#pragma once

#include "Abyss/Vector.hpp"
#include "InputDefinitions.hpp"

#include <array>

namespace Abyss {
    namespace GUI {
        class InputDevice;
    }
}

class Abyss::GUI::InputDevice {
protected:
    Vector3<double>                                                                                                   m_mousePosition{};
    std::array<InputDefinitions::ACTION, static_cast<std::size_t>(InputDefinitions::KEY::KEY_LAST)>                   m_mouseButtonsState{};
    std::array<InputDefinitions::ACTION, static_cast<std::size_t>(InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_LAST)> m_keysState{};
    InputDefinitions::MOD                                                                                             m_modsState{};

public:
    [[nodiscard]] auto isKeyDown(InputDefinitions::KEY key) const noexcept -> decltype(m_keysState)::value_type;
    [[nodiscard]] auto isMouseButtonDown(InputDefinitions::MOUSE_BUTTON key) const noexcept -> decltype(m_mouseButtonsState)::value_type;
    [[nodiscard]] auto getMousePosition() const noexcept -> const decltype(m_mousePosition) &;
    [[nodiscard]] auto getMods() const noexcept -> decltype(m_modsState);
};

inline auto Abyss::GUI::InputDevice::isKeyDown(InputDefinitions::KEY key) const noexcept -> decltype(m_keysState)::value_type
{
    auto index{static_cast<std::size_t>(key)};

    if (index > m_keysState.size())
        return InputDefinitions::ACTION::ACTION_RELEASE;
    return m_keysState[index];
}

inline auto Abyss::GUI::InputDevice::isMouseButtonDown(InputDefinitions::MOUSE_BUTTON key) const noexcept -> decltype(m_mouseButtonsState)::value_type
{
    auto index{static_cast<std::size_t>(key)};

    if (index > m_mouseButtonsState.size())
        return InputDefinitions::ACTION::ACTION_RELEASE;
    return m_mouseButtonsState[index];
}

inline auto Abyss::GUI::InputDevice::getMousePosition() const noexcept -> const decltype(m_mousePosition) &
{
	return m_mousePosition;
}

inline auto Abyss::GUI::InputDevice::getMods() const noexcept -> decltype(m_modsState)
{
	return m_modsState;
}
