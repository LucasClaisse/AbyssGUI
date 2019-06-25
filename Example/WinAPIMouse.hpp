#pragma once

#ifdef _WIN32

#    include "Abyss/GUI/Interfaces/AMouse.hpp"
#    include "Abyss/GUI/Interfaces/Input.hpp"

#    include <Windows.h>
#    include <unordered_map>

namespace Abyss {
    namespace Essentials {
        class WinAPIMouse;
    }
}

class Abyss::Essentials::WinAPIMouse final : public Abyss::AMouse {
private:
    POINT                                                     m_point{};
    static inline const std::unordered_map<int, Abyss::MOUSE> m_matches{
    {VK_LBUTTON, MOUSE::MOUSE_BUTTON_LEFT},
    {VK_RBUTTON, MOUSE::MOUSE_BUTTON_RIGHT},
    {VK_MBUTTON, MOUSE::MOUSE_BUTTON_MIDDLE}};

public:
    inline auto update() -> void final;
};

inline auto Abyss::Essentials::WinAPIMouse::update() -> void
{
    GetCursorPos(&m_point);
    ScreenToClient(GetActiveWindow(), &m_point);
    m_position.x = m_point.x;
    m_position.y = m_point.y;

    for (const auto &[winkey, key] : m_matches) {
        bool  isDown{static_cast<bool>(GetAsyncKeyState(winkey))};
        bool &val{m_status[static_cast<std::size_t>(key)]};

        if (isDown && !val) {
            onButtonActionDispatch(key, ACTION::ACTION_PRESS);
            val = true;
        } else if (!isDown && val) {
            onButtonActionDispatch(key, ACTION::ACTION_RELEASE);
            val = false;
        }
    }
}

#endif
