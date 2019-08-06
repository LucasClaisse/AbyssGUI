#include "SFML.hpp"
#include "Abyss/GUI/Widgets/Textbox.hpp"
#include "Abyss/GUI/Widgets/Window.hpp"
#include "WindowsConsole.hpp"

#include <cstdint>
#include <ctime>
#include <map>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

class TabBar : public Abyss::GUI::Widgets::RelativeLayout {
public:
    auto paint(const Abyss::GUI::InputDevice &device, double dt, Abyss::GUI::Renderer &renderer) -> void final;
};

inline auto TabBar::paint(const Abyss::GUI::InputDevice &device, double, Abyss::GUI::Renderer &renderer) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};

    renderer.setColor({0, 172, 193});
    renderer.drawRectangle(pos, size);
    renderer.drawText(L"Tab 1\tTab 2\tTab 3", pos + Vector3<double>{10, 3}, "OpenSans-Regular.ttf", size.y - 3 * 3, {205, 205, 205});
}

static auto start() -> void
{
    sf::RenderWindow window{sf::VideoMode{1600, 900}, "AbyssGUI example"};

    SFMLInputDevice input{};
    SFMLRenderer    renderer{window};

    Abyss::GUI::Widgets::Window win{};
    win.registerOnInputDevice(input);
    auto &textbox{win.getBody().addChild<Abyss::GUI::Widgets::Textbox>()};
    auto &tabbar{win.getBody().addChild<TabBar>()};
    tabbar.setSize({win.getSize().x, 20});

    sf::Event event{};
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            input.processEvent(event);
        }

        window.clear();
        renderer.drawRectangle({50, 50}, {100, 100});
        win.thinkDispatch(input, 0);
        win.paintDispatch(input, 0, renderer);
        window.display();
    }
}

int main()
{
    try {
        WindowsConsole test{};
        start();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
