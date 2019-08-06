#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#pragma clang diagnostic pop

#include "Abyss/GUI/Interfaces/InputDevice.hpp"
#include "Abyss/GUI/Interfaces/Renderer.hpp"

class SFMLInputDevice final : public Abyss::GUI::InputDevice {
private:
    inline static std::map<sf::Mouse::Button, Abyss::GUI::InputDefinitions::MOUSE_BUTTON> m_mouseMatches{
    {sf::Mouse::Button::Left, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_LEFT},
    {sf::Mouse::Button::Middle, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE},
    {sf::Mouse::Button::Right, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_RIGHT},
    {sf::Mouse::Button::XButton1, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_4},
    {sf::Mouse::Button::XButton2, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_5}};

    inline static std::map<sf::Keyboard::Key, Abyss::GUI::InputDefinitions::KEY> m_keyMatches{
    {sf::Keyboard::Key::Unknown, Abyss::GUI::InputDefinitions::KEY::KEY_UNKNOWN},
    {sf::Keyboard::Key::Space, Abyss::GUI::InputDefinitions::KEY::KEY_SPACE},
    // {sf::Keyboard::Key::Apo, Abyss::GUI::InputDefinitions::KEY::KEY_APOSTROPHE},
    {sf::Keyboard::Key::Comma, Abyss::GUI::InputDefinitions::KEY::KEY_COMMA},
    {sf::Keyboard::Key::Subtract, Abyss::GUI::InputDefinitions::KEY::KEY_MINUS},
    {sf::Keyboard::Key::Period, Abyss::GUI::InputDefinitions::KEY::KEY_PERIOD},
    {sf::Keyboard::Key::Slash, Abyss::GUI::InputDefinitions::KEY::KEY_SLASH},
    {sf::Keyboard::Key::Num0, Abyss::GUI::InputDefinitions::KEY::KEY_0},
    {sf::Keyboard::Key::Num1, Abyss::GUI::InputDefinitions::KEY::KEY_1},
    {sf::Keyboard::Key::Num2, Abyss::GUI::InputDefinitions::KEY::KEY_2},
    {sf::Keyboard::Key::Num3, Abyss::GUI::InputDefinitions::KEY::KEY_3},
    {sf::Keyboard::Key::Num4, Abyss::GUI::InputDefinitions::KEY::KEY_4},
    {sf::Keyboard::Key::Num5, Abyss::GUI::InputDefinitions::KEY::KEY_5},
    {sf::Keyboard::Key::Num6, Abyss::GUI::InputDefinitions::KEY::KEY_6},
    {sf::Keyboard::Key::Num7, Abyss::GUI::InputDefinitions::KEY::KEY_7},
    {sf::Keyboard::Key::Num8, Abyss::GUI::InputDefinitions::KEY::KEY_8},
    {sf::Keyboard::Key::Num9, Abyss::GUI::InputDefinitions::KEY::KEY_9},
    {sf::Keyboard::Key::SemiColon, Abyss::GUI::InputDefinitions::KEY::KEY_SEMICOLON},
    {sf::Keyboard::Key::Equal, Abyss::GUI::InputDefinitions::KEY::KEY_EQUAL},
    {sf::Keyboard::Key::A, Abyss::GUI::InputDefinitions::KEY::KEY_A},
    {sf::Keyboard::Key::B, Abyss::GUI::InputDefinitions::KEY::KEY_B},
    {sf::Keyboard::Key::C, Abyss::GUI::InputDefinitions::KEY::KEY_C},
    {sf::Keyboard::Key::D, Abyss::GUI::InputDefinitions::KEY::KEY_D},
    {sf::Keyboard::Key::E, Abyss::GUI::InputDefinitions::KEY::KEY_E},
    {sf::Keyboard::Key::F, Abyss::GUI::InputDefinitions::KEY::KEY_F},
    {sf::Keyboard::Key::G, Abyss::GUI::InputDefinitions::KEY::KEY_G},
    {sf::Keyboard::Key::H, Abyss::GUI::InputDefinitions::KEY::KEY_H},
    {sf::Keyboard::Key::I, Abyss::GUI::InputDefinitions::KEY::KEY_I},
    {sf::Keyboard::Key::J, Abyss::GUI::InputDefinitions::KEY::KEY_J},
    {sf::Keyboard::Key::K, Abyss::GUI::InputDefinitions::KEY::KEY_K},
    {sf::Keyboard::Key::L, Abyss::GUI::InputDefinitions::KEY::KEY_L},
    {sf::Keyboard::Key::M, Abyss::GUI::InputDefinitions::KEY::KEY_M},
    {sf::Keyboard::Key::N, Abyss::GUI::InputDefinitions::KEY::KEY_N},
    {sf::Keyboard::Key::O, Abyss::GUI::InputDefinitions::KEY::KEY_O},
    {sf::Keyboard::Key::P, Abyss::GUI::InputDefinitions::KEY::KEY_P},
    {sf::Keyboard::Key::Q, Abyss::GUI::InputDefinitions::KEY::KEY_Q},
    {sf::Keyboard::Key::R, Abyss::GUI::InputDefinitions::KEY::KEY_R},
    {sf::Keyboard::Key::S, Abyss::GUI::InputDefinitions::KEY::KEY_S},
    {sf::Keyboard::Key::T, Abyss::GUI::InputDefinitions::KEY::KEY_T},
    {sf::Keyboard::Key::U, Abyss::GUI::InputDefinitions::KEY::KEY_U},
    {sf::Keyboard::Key::V, Abyss::GUI::InputDefinitions::KEY::KEY_V},
    {sf::Keyboard::Key::W, Abyss::GUI::InputDefinitions::KEY::KEY_W},
    {sf::Keyboard::Key::X, Abyss::GUI::InputDefinitions::KEY::KEY_X},
    {sf::Keyboard::Key::Y, Abyss::GUI::InputDefinitions::KEY::KEY_Y},
    {sf::Keyboard::Key::Z, Abyss::GUI::InputDefinitions::KEY::KEY_Z},
    {sf::Keyboard::Key::LBracket, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_BRACKET},
    {sf::Keyboard::Key::BackSlash, Abyss::GUI::InputDefinitions::KEY::KEY_BACKSLASH},
    {sf::Keyboard::Key::RBracket, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_BRACKET},
    // {sf::Keyboard::Key:, Abyss::GUI::InputDefinitions::KEY::KEY_GRAVE_ACCENT},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_WORLD_1},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_WORLD_2},
    {sf::Keyboard::Key::Escape, Abyss::GUI::InputDefinitions::KEY::KEY_ESCAPE},
    {sf::Keyboard::Key::Enter, Abyss::GUI::InputDefinitions::KEY::KEY_ENTER},
    {sf::Keyboard::Key::Tab, Abyss::GUI::InputDefinitions::KEY::KEY_TAB},
    {sf::Keyboard::Key::BackSpace, Abyss::GUI::InputDefinitions::KEY::KEY_BACKSPACE},
    {sf::Keyboard::Key::Insert, Abyss::GUI::InputDefinitions::KEY::KEY_INSERT},
    {sf::Keyboard::Key::Delete, Abyss::GUI::InputDefinitions::KEY::KEY_DELETE},
    {sf::Keyboard::Key::Right, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT},
    {sf::Keyboard::Key::Left, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT},
    {sf::Keyboard::Key::Down, Abyss::GUI::InputDefinitions::KEY::KEY_DOWN},
    {sf::Keyboard::Key::Up, Abyss::GUI::InputDefinitions::KEY::KEY_UP},
    {sf::Keyboard::Key::PageUp, Abyss::GUI::InputDefinitions::KEY::KEY_PAGE_UP},
    {sf::Keyboard::Key::PageDown, Abyss::GUI::InputDefinitions::KEY::KEY_PAGE_DOWN},
    {sf::Keyboard::Key::Home, Abyss::GUI::InputDefinitions::KEY::KEY_HOME},
    {sf::Keyboard::Key::End, Abyss::GUI::InputDefinitions::KEY::KEY_END},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_CAPS_LOCK},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_SCROLL_LOCK},
    // {sf::Keyboard::Key::num, Abyss::GUI::InputDefinitions::KEY::KEY_NUM_LOCK},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_PRINT_SCREEN},
    {sf::Keyboard::Key::Pause, Abyss::GUI::InputDefinitions::KEY::KEY_PAUSE},
    {sf::Keyboard::Key::F1, Abyss::GUI::InputDefinitions::KEY::KEY_F1},
    {sf::Keyboard::Key::F2, Abyss::GUI::InputDefinitions::KEY::KEY_F2},
    {sf::Keyboard::Key::F3, Abyss::GUI::InputDefinitions::KEY::KEY_F3},
    {sf::Keyboard::Key::F4, Abyss::GUI::InputDefinitions::KEY::KEY_F4},
    {sf::Keyboard::Key::F5, Abyss::GUI::InputDefinitions::KEY::KEY_F5},
    {sf::Keyboard::Key::F6, Abyss::GUI::InputDefinitions::KEY::KEY_F6},
    {sf::Keyboard::Key::F7, Abyss::GUI::InputDefinitions::KEY::KEY_F7},
    {sf::Keyboard::Key::F8, Abyss::GUI::InputDefinitions::KEY::KEY_F8},
    {sf::Keyboard::Key::F9, Abyss::GUI::InputDefinitions::KEY::KEY_F9},
    {sf::Keyboard::Key::F10, Abyss::GUI::InputDefinitions::KEY::KEY_F10},
    {sf::Keyboard::Key::F11, Abyss::GUI::InputDefinitions::KEY::KEY_F11},
    {sf::Keyboard::Key::F12, Abyss::GUI::InputDefinitions::KEY::KEY_F12},
    {sf::Keyboard::Key::F13, Abyss::GUI::InputDefinitions::KEY::KEY_F13},
    {sf::Keyboard::Key::F14, Abyss::GUI::InputDefinitions::KEY::KEY_F14},
    {sf::Keyboard::Key::F15, Abyss::GUI::InputDefinitions::KEY::KEY_F15},
    {sf::Keyboard::Key::Numpad0, Abyss::GUI::InputDefinitions::KEY::KEY_KP_0},
    {sf::Keyboard::Key::Numpad1, Abyss::GUI::InputDefinitions::KEY::KEY_KP_1},
    {sf::Keyboard::Key::Numpad2, Abyss::GUI::InputDefinitions::KEY::KEY_KP_2},
    {sf::Keyboard::Key::Numpad3, Abyss::GUI::InputDefinitions::KEY::KEY_KP_3},
    {sf::Keyboard::Key::Numpad4, Abyss::GUI::InputDefinitions::KEY::KEY_KP_4},
    {sf::Keyboard::Key::Numpad5, Abyss::GUI::InputDefinitions::KEY::KEY_KP_5},
    {sf::Keyboard::Key::Numpad6, Abyss::GUI::InputDefinitions::KEY::KEY_KP_6},
    {sf::Keyboard::Key::Numpad7, Abyss::GUI::InputDefinitions::KEY::KEY_KP_7},
    {sf::Keyboard::Key::Numpad8, Abyss::GUI::InputDefinitions::KEY::KEY_KP_8},
    {sf::Keyboard::Key::Numpad9, Abyss::GUI::InputDefinitions::KEY::KEY_KP_9},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_KP_DECIMAL},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_KP_DIVIDE},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_KP_MULTIPLY},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_KP_SUBTRACT},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_KP_ADD},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_KP_ENTER},
    // {sf::Keyboard::Key::, Abyss::GUI::InputDefinitions::KEY::KEY_KP_EQUAL},
    {sf::Keyboard::Key::LShift, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_SHIFT},
    {sf::Keyboard::Key::LControl, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_CONTROL},
    {sf::Keyboard::Key::LAlt, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_ALT},
    {sf::Keyboard::Key::LSystem, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_SUPER},
    {sf::Keyboard::Key::RShift, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_SHIFT},
    {sf::Keyboard::Key::RControl, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_CONTROL},
    {sf::Keyboard::Key::RAlt, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_ALT},
    {sf::Keyboard::Key::RSystem, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_SUPER}};
    // {sf::Keyboard::Key::RMenu, Abyss::GUI::InputDefinitions::KEY::KEY_MENU}};

public:
    auto processEvent(sf::Event &event) noexcept -> void;
};

inline auto SFMLInputDevice::processEvent(sf::Event &event) noexcept -> void
{
    switch (event.type) {
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased: {
        auto match{m_keyMatches.find(event.key.code)};
        // std::cout << "Key is '" << Abyss::GUI::InputDefinitions::keyToString[(*match).second] << "' " << event.key.code << '\n';
        if (match != m_keyMatches.cend() && m_keyEvent)
            m_keyEvent(*this, (*match).second, (event.type == sf::Event::KeyPressed) ? Abyss::GUI::InputDefinitions::ACTION::ACTION_PRESS : Abyss::GUI::InputDefinitions::ACTION::ACTION_RELEASE);
        break;
    }
    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased: {
        auto match{m_mouseMatches.find(event.mouseButton.button)};
        if (match != m_mouseMatches.cend() && m_mouseButtonEvent)
            m_mouseButtonEvent(*this, (*match).second, (event.type == sf::Event::MouseButtonPressed) ? Abyss::GUI::InputDefinitions::ACTION::ACTION_PRESS : Abyss::GUI::InputDefinitions::ACTION::ACTION_RELEASE);
        break;
    }
    case sf::Event::MouseMoved: {
        m_mousePosition = {static_cast<double>(event.mouseMove.x), static_cast<double>(event.mouseMove.y)};
        break;
    }
    case sf::Event::TextEntered: {
        if (m_characterEvent)
            m_characterEvent(*this, static_cast<wchar_t>(event.text.unicode));
        break;
    }
    case sf::Event::MouseWheelScrolled: {
        if (m_scrollEvent)
            m_scrollEvent(*this, {0, static_cast<double>(event.mouseWheelScroll.delta)});
        break;
    }
    default:
        break;
    }
}

class SFMLRenderer final : public Abyss::GUI::Renderer {
private:
    sf::RenderWindow &                                         m_window;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fontsCache{};

public:
    SFMLRenderer(decltype(m_window) window);

    auto drawVertices(const Vertices &vertices, const Color &col) -> void final;
    auto drawColoredVertices(const ColoredVertices &vertices) -> void final;
    auto drawText(const std::wstring &wstr, const Vector3<double> &position, const std::string &fontName, const double size, const Color &col) -> void;
};

inline SFMLRenderer::SFMLRenderer(decltype(m_window) window)
    : m_window{window}
{
}

inline auto SFMLRenderer::drawVertices(const Vertices &vertices, const Color &col) -> void
{
    sf::ConvexShape shape{};
    shape.setPointCount(vertices.size());
    shape.setFillColor({col.r, col.g, col.b, col.a});
    for (size_t i{0}; i < vertices.size(); ++i) {
        auto &vertex{vertices[i]};
        shape.setPoint(i, {static_cast<float>(vertex.x), static_cast<float>(vertex.y)});
    }
    m_window.draw(shape);
}

inline auto SFMLRenderer::drawColoredVertices(const ColoredVertices &vertices) -> void
{
    sf::ConvexShape shape{};
    shape.setPointCount(vertices.size());
    for (size_t i{0}; i < vertices.size(); ++i) {
        auto &vertex{vertices[i]};
        shape.setPoint(i, {static_cast<float>(vertex.first.x), static_cast<float>(vertex.first.y)});
    }
    m_window.draw(shape);
}

inline auto SFMLRenderer::drawText(const std::wstring &wstr, const Vector3<double> &position, const std::string &fontName, const double size, const Color &col) -> void
{
    auto font{m_fontsCache.find(fontName)};
    if (font == m_fontsCache.cend()) {
        auto ptr{std::make_unique<sf::Font>()};
        if (!ptr->loadFromFile(fontName))
            throw std::runtime_error{"Couldn't open font"};

        m_fontsCache[fontName] = std::move(ptr);
        font                   = m_fontsCache.find(fontName);
    }

    sf::Text text{wstr, *((*font).second.get()), static_cast<unsigned int>(size)};
    text.setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
    text.setColor({col.r, col.g, col.b, col.a});
    m_window.draw(text);
}
