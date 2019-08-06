#pragma once

#include "Abyss/GUI/Widget.hpp"

namespace Abyss {
    namespace GUI {
        namespace Widgets {
            class TabManager;
            class TabButton;
            class TabView;
        }
    }
}

class Abyss::GUI::Widgets::TabManager : public Widget {
public:
    auto paint(const Abyss::GUI::InputDevice &device, double dt, Abyss::GUI::Renderer &renderer) -> void final;
};

inline auto Abyss::GUI::Widgets::TabManager::paint(const Abyss::GUI::InputDevice &device, double, Abyss::GUI::Renderer &renderer) -> void
{
    auto            pos{getPosition()};
    auto            size{getSize()};
    Vector3<double> barSize{size.x, 20};

    renderer.setColor({0, 172, 193});
    renderer.drawRectangle(pos, barSize);
    renderer.drawText(L"Tab 1\tTab 2\tTab 3", pos + Vector3<double>{10, 3}, "OpenSans-Regular.ttf", size.y - 3 * 3, {205, 205, 205});
}

class Abyss::GUI::Widgets::TabButton : public Widget {
protected:
	TabManager &m_manager;
	std::wstring m_text{};

public:
	explicit TabButton(decltype(m_manager) manager, const decltype(m_text) &text);

	auto paint(const Abyss::GUI::InputDevice &device, double dt, Abyss::GUI::Renderer &renderer) -> void final;
};

inline Abyss::GUI::Widgets::TabButton::TabButton(decltype(m_manager) manager, const decltype(m_text) &text)
	: m_manager{manager}, m_text{text}
{

}

inline auto Abyss::GUI::Widgets::TabButton::paint(const Abyss::GUI::InputDevice &device, double, Abyss::GUI::Renderer &renderer) -> void
{
    auto            pos{getPosition()};
    auto            size{getSize()};
    Vector3<double> barSize{size.x, 20};

    renderer.drawText(L"Tab 1\tTab 2\tTab 3", pos + Vector3<double>{10, 3}, "OpenSans-Regular.ttf", size.y - 3 * 3, {205, 205, 205});
}
