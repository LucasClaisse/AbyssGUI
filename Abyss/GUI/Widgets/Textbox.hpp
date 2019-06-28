#pragma once

#include "Abyss/GUI/Widget.hpp"

#include <iostream>

namespace Abyss {
	namespace GUI {
		namespace Widgets {
			class Textbox;
		}
	}
}

class Abyss::GUI::Widgets::Textbox : public Widget {
protected:
	std::wstring m_wstr{};

public:
	virtual ~Textbox() = default;

    auto characterEvent(const InputDevice &device, wchar_t codepoint) -> void override;
	auto paint(const InputDevice &device, double dt, Renderer &renderer) -> void override;
};

inline auto Abyss::GUI::Widgets::Textbox::characterEvent(const InputDevice &device, wchar_t codepoint) -> void
{
	m_wstr += codepoint;
}

inline auto Abyss::GUI::Widgets::Textbox::paint(const InputDevice &device, double dt, Renderer &renderer) -> void
{
	std::wcout << m_wstr << '\n';
}
