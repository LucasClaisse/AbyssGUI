#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <SDL.h>

#pragma clang diagnostic pop

#include "Abyss/GUI/Interfaces/AMouse.hpp"

#include <unordered_map>

class SDL2Mouse final : public Abyss::AMouse {
private:
    static inline const std::unordered_map<int, Abyss::MOUSE> m_matches{
    {SDL_BUTTON_LEFT, Abyss::MOUSE::MOUSE_BUTTON_LEFT},
    {SDL_BUTTON_RIGHT, Abyss::MOUSE::MOUSE_BUTTON_RIGHT},
    {SDL_BUTTON_MIDDLE, Abyss::MOUSE::MOUSE_BUTTON_MIDDLE}};

public:
	auto receiveEvent(const SDL_Event &event) -> void;
    auto update() -> void final;
};

inline auto SDL2Mouse::receiveEvent(const SDL_Event &event) -> void
{
	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		auto it{m_matches.find(event.button.button)};
		if (it == m_matches.cend())
			return;

		auto &button{(*it).second};
		auto eventResult{event.type == SDL_MOUSEBUTTONDOWN ? Abyss::ACTION::ACTION_PRESS : Abyss::ACTION::ACTION_RELEASE};
		m_status[static_cast<std::size_t>(button)] = eventResult == Abyss::ACTION::ACTION_PRESS;
		onButtonActionDispatch(button, eventResult);
	} else if (event.type == SDL_MOUSEMOTION)
		m_position = {static_cast<double>(event.motion.x), static_cast<double>(event.motion.y)};
}

inline auto SDL2Mouse::update() -> void
{
    /*GetCursorPos(&m_point);
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
    }*/
}
