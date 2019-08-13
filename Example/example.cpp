#include "Abyss/GUI/Widgets/Textbox.hpp"
#include "Abyss/GUI/Widgets/Window.hpp"
#include "SFML.hpp"
#include "WindowsConsole.hpp"

#include <cstdint>
#include <ctime>
#include <map>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <unordered_map>

class WindowBody final : public Abyss::GUI::Widgets::RelativeLayout {
public:
    auto paint(const Abyss::GUI::InputDevice &device, double dt, Abyss::GUI::Renderer &renderer) -> void final;
};

inline auto WindowBody::paint(const Abyss::GUI::InputDevice &device, double, Abyss::GUI::Renderer &renderer) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};

    renderer.setColor({255, 255, 255});
    renderer.drawRectangle(pos, size);
}

class SFMLWindow final : public Abyss::GUI::Widget {
private:
    bool                              m_held{false};
    Vector3<double>                   m_heldPosition{};
    std::unique_ptr<sf::RenderWindow> m_window{};
    WindowBody *                      m_body{nullptr};

public:
    explicit SFMLWindow();

    [[nodiscard]] auto getPosition(bool relative = true) const -> decltype(m_position) final;
    auto               setPosition(const decltype(m_position) &position) -> void final;
    [[nodiscard]] auto getSize() const -> decltype(m_size) final;
    auto               setSize(const decltype(m_size) &size) -> void final;
    [[nodiscard]] auto getBody() -> WindowBody &;

    auto mouseButtonEvent(const Abyss::GUI::InputDevice &device, Abyss::GUI::InputDefinitions::MOUSE_BUTTON button, Abyss::GUI::InputDefinitions::ACTION action) -> void final;
    auto think(const Abyss::GUI::InputDevice &device, double dt) -> void final;
    auto paint(const Abyss::GUI::InputDevice &device, double dt, Abyss::GUI::Renderer &renderer) -> void final;
};

inline auto SFMLWindow::getPosition(bool relative) const -> decltype(m_position)
{
    if (relative == true)
        return {};

    auto pos{m_window->getPosition()};
    return {static_cast<double>(pos.x), static_cast<double>(pos.y)};
}

inline auto SFMLWindow::setPosition(const decltype(m_position) &position) -> void
{
    Widget::setPosition(position);
    m_window->setPosition({static_cast<int>(position.x), static_cast<int>(position.y)});
}

inline auto SFMLWindow::getSize() const -> decltype(m_size)
{
    auto size{m_window->getSize()};
    return {static_cast<double>(size.x), static_cast<double>(size.y)};
}

inline auto SFMLWindow::setSize(const decltype(m_size) &size) -> void
{
    Widget::setSize(size);
    m_window->setSize({static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y)});
    m_body->setSize(size - Vector3<double>{0, 30});
}

inline auto SFMLWindow::getBody() -> WindowBody &
{
    return *m_body;
}

inline auto SFMLWindow::mouseButtonEvent(const Abyss::GUI::InputDevice &device, Abyss::GUI::InputDefinitions::MOUSE_BUTTON button, Abyss::GUI::InputDefinitions::ACTION action) -> void
{
    auto  pos{getPosition()};
    auto  size{getSize()};
    auto  hovered{device.isHovering(pos, {size.x, 30})};
    POINT point{};
    GetCursorPos(&point);
    Vector3<double> mouse{static_cast<double>(point.x), static_cast<double>(point.y)};

    if (button == Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_LEFT && action == Abyss::GUI::InputDefinitions::ACTION::ACTION_PRESS && !m_held) {
        m_held = hovered;
        if (m_held)
            m_heldPosition = mouse - getPosition(false);
    } else if (button == Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_LEFT && action == Abyss::GUI::InputDefinitions::ACTION::ACTION_RELEASE && m_held)
        m_held = false;
}

SFMLWindow::SFMLWindow()
{
    m_children.push_back(std::make_unique<WindowBody>());
    m_body = static_cast<decltype(m_body)>(m_children.back().get());
    if (m_body == nullptr)
        throw std::runtime_error{"Couldn't create WindowBody"};

    m_body->setPosition({0, 30});
    getBody().addChild<Abyss::GUI::Widgets::Textbox>();

    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode{400, 400}, "AbyssGUI example", sf::Style::None);
    if (!m_window)
        throw std::runtime_error{"Couldn't create RenderWindow."};

    setPosition({0, 0});
    setSize({300, 300});

    SFMLInputDevice input{};
    SFMLRenderer    renderer{*m_window};

    registerOnInputDevice(input);

    /*
    Abyss::GUI::Widgets::Window win{};
    auto &textbox{win.getBody().addChild<Abyss::GUI::Widgets::Textbox>()};
    auto &tabbar{win.getBody().addChild<TabBar>()};
    tabbar.setSize({win.getSize().x, 20});
*/

    sf::Event event{};
    while (m_window->isOpen()) {
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window->close();

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                m_window->setView(sf::View(visibleArea));
            }

            input.processEvent(event);
        }

        m_window->clear();
        // renderer.drawRectangle({50, 50}, {100, 100});
        thinkDispatch(input, 0);
        paintDispatch(input, 0, renderer);
        m_window->display();
    }
}

inline auto SFMLWindow::think(const Abyss::GUI::InputDevice &device, double) -> void
{
    POINT point{};
    GetCursorPos(&point);
    Vector3<double> mouse{static_cast<double>(point.x), static_cast<double>(point.y)};

    if (m_held)
        setPosition(mouse - m_heldPosition);
}

inline auto SFMLWindow::paint(const Abyss::GUI::InputDevice &device, double, Abyss::GUI::Renderer &renderer) -> void
{
    auto pos{getPosition()};
    auto size{getSize()};

    renderer.setColor({0, 255, 0});
    renderer.drawRectangle(pos, size);
    renderer.drawText(L"Window Test", pos + Vector3<double>{6, 3}, "OpenSans-Regular.ttf", 18, {50, 50, 50});
}

auto main() -> int
{
    WindowsConsole test{};
    try {
        // start();
        SFMLWindow win{};
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        int tmp{};
        std::cin >> tmp;
    }
    return 0;
}

// static auto start() -> void
// {
//     sf::RenderWindow window{sf::VideoMode{1600, 900}, "AbyssGUI example", sf::Style::None};

//     SFMLInputDevice input{};
//     SFMLRenderer    renderer{window};

//     Abyss::GUI::Widgets::Window win{};
//     win.registerOnInputDevice(input);
//     auto &textbox{win.getBody().addChild<Abyss::GUI::Widgets::Textbox>()};
//     auto &tabbar{win.getBody().addChild<TabBar>()};
//     tabbar.setSize({win.getSize().x, 20});

//     sf::Event event{};
//     while (window.isOpen()) {
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();

//             input.processEvent(event);
//         }

//         window.clear();
//         renderer.drawRectangle({50, 50}, {100, 100});
//         win.thinkDispatch(input, 0);
//         win.paintDispatch(input, 0, renderer);
//         window.display();
//     }
// }

// class TabBar : public Abyss::GUI::Widgets::RelativeLayout {
// public:
//     auto paint(const Abyss::GUI::InputDevice &device, double dt, Abyss::GUI::Renderer &renderer) -> void final;
// };

// inline auto TabBar::paint(const Abyss::GUI::InputDevice &device, double, Abyss::GUI::Renderer &renderer) -> void
// {
//     auto pos{getPosition()};
//     auto size{getSize()};

//     renderer.setColor({255, 255, 0});
//     renderer.drawRectangle(pos, size);
//     renderer.drawText(L"Tab 1\tTab 2\tTab 3", pos + Vector3<double>{10, 3}, "OpenSans-Regular.ttf", size.y - 3 * 3, {205, 205, 205});
// }
