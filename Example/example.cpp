#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_syswm.h>
#include <SDL_ttf.h>

#pragma clang diagnostic pop

#include "Abyss/GUI/Interfaces/InputDevice.hpp"
#include "Abyss/GUI/Interfaces/Renderer.hpp"
#include "Abyss/GUI/Widgets/Window.hpp"
#include "WindowsConsole.hpp"
#include "Abyss/GUI/Widgets/Textbox.hpp"

#include <GL/glu.h>
#include <cstdint>
#include <ctime>
#include <map>
#include <sstream>
#include <stdexcept>

class SDL2InputDevice final : public Abyss::GUI::InputDevice {
private:
    inline static std::map<std::int64_t, Abyss::GUI::InputDefinitions::MOUSE_BUTTON> m_mouseMatches{
    {SDL_BUTTON_LEFT, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_LEFT},
    {SDL_BUTTON_MIDDLE, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE},
    {SDL_BUTTON_RIGHT, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_RIGHT},
    {SDL_BUTTON_X1, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_4},
    {SDL_BUTTON_X2, Abyss::GUI::InputDefinitions::MOUSE_BUTTON::MOUSE_BUTTON_5}};

    inline static std::map<std::int64_t, Abyss::GUI::InputDefinitions::KEY> m_keyMatches{
    {SDLK_UNKNOWN, Abyss::GUI::InputDefinitions::KEY::KEY_UNKNOWN},
    {SDLK_SPACE, Abyss::GUI::InputDefinitions::KEY::KEY_SPACE},
    // {SDLK_APOS, Abyss::GUI::InputDefinitions::KEY::KEY_APOSTROPHE},
    {SDLK_COMMA, Abyss::GUI::InputDefinitions::KEY::KEY_COMMA},
    {SDLK_MINUS, Abyss::GUI::InputDefinitions::KEY::KEY_MINUS},
    {SDLK_PERIOD, Abyss::GUI::InputDefinitions::KEY::KEY_PERIOD},
    {SDLK_SLASH, Abyss::GUI::InputDefinitions::KEY::KEY_SLASH},
    {SDLK_0, Abyss::GUI::InputDefinitions::KEY::KEY_0},
    {SDLK_1, Abyss::GUI::InputDefinitions::KEY::KEY_1},
    {SDLK_2, Abyss::GUI::InputDefinitions::KEY::KEY_2},
    {SDLK_3, Abyss::GUI::InputDefinitions::KEY::KEY_3},
    {SDLK_4, Abyss::GUI::InputDefinitions::KEY::KEY_4},
    {SDLK_5, Abyss::GUI::InputDefinitions::KEY::KEY_5},
    {SDLK_6, Abyss::GUI::InputDefinitions::KEY::KEY_6},
    {SDLK_7, Abyss::GUI::InputDefinitions::KEY::KEY_7},
    {SDLK_8, Abyss::GUI::InputDefinitions::KEY::KEY_8},
    {SDLK_9, Abyss::GUI::InputDefinitions::KEY::KEY_9},
    {SDLK_SEMICOLON, Abyss::GUI::InputDefinitions::KEY::KEY_SEMICOLON},
    {SDLK_EQUALS, Abyss::GUI::InputDefinitions::KEY::KEY_EQUAL},
    {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_A},
    {SDLK_b, Abyss::GUI::InputDefinitions::KEY::KEY_B},
    {SDLK_c, Abyss::GUI::InputDefinitions::KEY::KEY_C},
    {SDLK_d, Abyss::GUI::InputDefinitions::KEY::KEY_D},
    {SDLK_e, Abyss::GUI::InputDefinitions::KEY::KEY_E},
    {SDLK_f, Abyss::GUI::InputDefinitions::KEY::KEY_F},
    {SDLK_g, Abyss::GUI::InputDefinitions::KEY::KEY_G},
    {SDLK_h, Abyss::GUI::InputDefinitions::KEY::KEY_H},
    {SDLK_i, Abyss::GUI::InputDefinitions::KEY::KEY_I},
    {SDLK_j, Abyss::GUI::InputDefinitions::KEY::KEY_J},
    {SDLK_k, Abyss::GUI::InputDefinitions::KEY::KEY_K},
    {SDLK_l, Abyss::GUI::InputDefinitions::KEY::KEY_L},
    {SDLK_m, Abyss::GUI::InputDefinitions::KEY::KEY_M},
    {SDLK_n, Abyss::GUI::InputDefinitions::KEY::KEY_N},
    {SDLK_o, Abyss::GUI::InputDefinitions::KEY::KEY_O},
    {SDLK_p, Abyss::GUI::InputDefinitions::KEY::KEY_P},
    {SDLK_q, Abyss::GUI::InputDefinitions::KEY::KEY_Q},
    {SDLK_r, Abyss::GUI::InputDefinitions::KEY::KEY_R},
    {SDLK_s, Abyss::GUI::InputDefinitions::KEY::KEY_S},
    {SDLK_t, Abyss::GUI::InputDefinitions::KEY::KEY_T},
    {SDLK_u, Abyss::GUI::InputDefinitions::KEY::KEY_U},
    {SDLK_v, Abyss::GUI::InputDefinitions::KEY::KEY_V},
    {SDLK_w, Abyss::GUI::InputDefinitions::KEY::KEY_W},
    {SDLK_x, Abyss::GUI::InputDefinitions::KEY::KEY_X},
    {SDLK_y, Abyss::GUI::InputDefinitions::KEY::KEY_Y},
    {SDLK_z, Abyss::GUI::InputDefinitions::KEY::KEY_Z},
    {SDLK_LEFTBRACKET, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_BRACKET},
    {SDLK_BACKSLASH, Abyss::GUI::InputDefinitions::KEY::KEY_BACKSLASH},
    {SDLK_RIGHTBRACKET, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_BRACKET},
    // {SDLK_ACCENT, Abyss::GUI::InputDefinitions::KEY::KEY_GRAVE_ACCENT},
    // {SDLK_WORLD_1, Abyss::GUI::InputDefinitions::KEY::KEY_WORLD_1},
    // {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_WORLD_2},
    {SDLK_ESCAPE, Abyss::GUI::InputDefinitions::KEY::KEY_ESCAPE},
    {SDLK_KP_ENTER, Abyss::GUI::InputDefinitions::KEY::KEY_ENTER},
    {SDLK_TAB, Abyss::GUI::InputDefinitions::KEY::KEY_TAB},
    {SDLK_BACKSPACE, Abyss::GUI::InputDefinitions::KEY::KEY_BACKSPACE},
    {SDLK_INSERT, Abyss::GUI::InputDefinitions::KEY::KEY_INSERT},
    {SDLK_DELETE, Abyss::GUI::InputDefinitions::KEY::KEY_DELETE},
    {SDLK_RIGHT, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT},
    {SDLK_LEFT, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT},
    {SDLK_DOWN, Abyss::GUI::InputDefinitions::KEY::KEY_DOWN},
    {SDLK_UP, Abyss::GUI::InputDefinitions::KEY::KEY_UP},
    {SDLK_PAGEUP, Abyss::GUI::InputDefinitions::KEY::KEY_PAGE_UP},
    {SDLK_PAGEDOWN, Abyss::GUI::InputDefinitions::KEY::KEY_PAGE_DOWN},
    {SDLK_HOME, Abyss::GUI::InputDefinitions::KEY::KEY_HOME},
    {SDLK_END, Abyss::GUI::InputDefinitions::KEY::KEY_END},
    {SDLK_CAPSLOCK, Abyss::GUI::InputDefinitions::KEY::KEY_CAPS_LOCK},
    {SDLK_SCROLLLOCK, Abyss::GUI::InputDefinitions::KEY::KEY_SCROLL_LOCK},
    {SDLK_NUMLOCKCLEAR, Abyss::GUI::InputDefinitions::KEY::KEY_NUM_LOCK},
    {SDLK_PRINTSCREEN, Abyss::GUI::InputDefinitions::KEY::KEY_PRINT_SCREEN},
    {SDLK_PAUSE, Abyss::GUI::InputDefinitions::KEY::KEY_PAUSE},
    {SDLK_F1, Abyss::GUI::InputDefinitions::KEY::KEY_F1},
    {SDLK_F2, Abyss::GUI::InputDefinitions::KEY::KEY_F2},
    {SDLK_F3, Abyss::GUI::InputDefinitions::KEY::KEY_F3},
    {SDLK_F4, Abyss::GUI::InputDefinitions::KEY::KEY_F4},
    {SDLK_F5, Abyss::GUI::InputDefinitions::KEY::KEY_F5},
    {SDLK_F6, Abyss::GUI::InputDefinitions::KEY::KEY_F6},
    {SDLK_F7, Abyss::GUI::InputDefinitions::KEY::KEY_F7},
    {SDLK_F8, Abyss::GUI::InputDefinitions::KEY::KEY_F8},
    {SDLK_F9, Abyss::GUI::InputDefinitions::KEY::KEY_F9},
    {SDLK_F10, Abyss::GUI::InputDefinitions::KEY::KEY_F10},
    {SDLK_F11, Abyss::GUI::InputDefinitions::KEY::KEY_F11},
    {SDLK_F12, Abyss::GUI::InputDefinitions::KEY::KEY_F12},
    {SDLK_F13, Abyss::GUI::InputDefinitions::KEY::KEY_F13},
    {SDLK_F14, Abyss::GUI::InputDefinitions::KEY::KEY_F14},
    {SDLK_F15, Abyss::GUI::InputDefinitions::KEY::KEY_F15},
    {SDLK_F16, Abyss::GUI::InputDefinitions::KEY::KEY_F16},
    {SDLK_F17, Abyss::GUI::InputDefinitions::KEY::KEY_F17},
    {SDLK_F18, Abyss::GUI::InputDefinitions::KEY::KEY_F18},
    {SDLK_F19, Abyss::GUI::InputDefinitions::KEY::KEY_F19},
    {SDLK_F20, Abyss::GUI::InputDefinitions::KEY::KEY_F20},
    {SDLK_F21, Abyss::GUI::InputDefinitions::KEY::KEY_F21},
    {SDLK_F22, Abyss::GUI::InputDefinitions::KEY::KEY_F22},
    {SDLK_F23, Abyss::GUI::InputDefinitions::KEY::KEY_F23},
    {SDLK_F24, Abyss::GUI::InputDefinitions::KEY::KEY_F24},
    {SDLK_KP_0, Abyss::GUI::InputDefinitions::KEY::KEY_KP_0},
    {SDLK_KP_1, Abyss::GUI::InputDefinitions::KEY::KEY_KP_1},
    {SDLK_KP_2, Abyss::GUI::InputDefinitions::KEY::KEY_KP_2},
    {SDLK_KP_3, Abyss::GUI::InputDefinitions::KEY::KEY_KP_3},
    {SDLK_KP_4, Abyss::GUI::InputDefinitions::KEY::KEY_KP_4},
    {SDLK_KP_5, Abyss::GUI::InputDefinitions::KEY::KEY_KP_5},
    {SDLK_KP_6, Abyss::GUI::InputDefinitions::KEY::KEY_KP_6},
    {SDLK_KP_7, Abyss::GUI::InputDefinitions::KEY::KEY_KP_7},
    {SDLK_KP_8, Abyss::GUI::InputDefinitions::KEY::KEY_KP_8},
    {SDLK_KP_9, Abyss::GUI::InputDefinitions::KEY::KEY_KP_9},
    {SDLK_KP_DECIMAL, Abyss::GUI::InputDefinitions::KEY::KEY_KP_DECIMAL},
    {SDLK_KP_DIVIDE, Abyss::GUI::InputDefinitions::KEY::KEY_KP_DIVIDE},
    {SDLK_KP_MULTIPLY, Abyss::GUI::InputDefinitions::KEY::KEY_KP_MULTIPLY},
    {SDLK_KP_MEMSUBTRACT, Abyss::GUI::InputDefinitions::KEY::KEY_KP_SUBTRACT},
    {SDLK_KP_MEMADD, Abyss::GUI::InputDefinitions::KEY::KEY_KP_ADD},
    {SDLK_KP_ENTER, Abyss::GUI::InputDefinitions::KEY::KEY_KP_ENTER},
    {SDLK_KP_EQUALS, Abyss::GUI::InputDefinitions::KEY::KEY_KP_EQUAL},
    // {SDLK_ALT, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_SHIFT},
    // {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_CONTROL},
    // {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_ALT},
    // {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_LEFT_SUPER},
    // {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_SHIFT},
    // {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_CONTROL},
    // {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_ALT},
    // {SDLK_a, Abyss::GUI::InputDefinitions::KEY::KEY_RIGHT_SUPER},
    {SDLK_MENU, Abyss::GUI::InputDefinitions::KEY::KEY_MENU}};

public:
    auto processEvent(SDL_Event &event) noexcept -> void;
};

inline auto SDL2InputDevice::processEvent(SDL_Event &event) noexcept -> void
{
    switch (event.type) {
    case SDL_MOUSEMOTION: {
        m_mousePosition = {static_cast<double>(event.motion.x), static_cast<double>(event.motion.y)};
        break;
    }
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP: {
        auto match{m_mouseMatches.find(event.button.button)};
        if (match != m_mouseMatches.cend() && m_mouseButtonEvent)
            m_mouseButtonEvent(*this, (*match).second, (event.type == SDL_MOUSEBUTTONDOWN) ? Abyss::GUI::InputDefinitions::ACTION::ACTION_PRESS : Abyss::GUI::InputDefinitions::ACTION::ACTION_RELEASE);
        break;
    }
    case SDL_KEYDOWN:
    case SDL_KEYUP: {
        auto match{m_keyMatches.find(event.key.keysym.sym)};
		// std::cout << "Key is '" << Abyss::GUI::InputDefinitions::keyToString[(*match).second] << "' " << event.key.keysym.scancode << '\n';
        if (match != m_keyMatches.cend() && m_keyEvent)
            m_keyEvent(*this, (*match).second, (event.type == SDL_KEYDOWN) ? Abyss::GUI::InputDefinitions::ACTION::ACTION_PRESS : Abyss::GUI::InputDefinitions::ACTION::ACTION_RELEASE);
		break;
    }
	case SDL_TEXTINPUT: {
		if (m_characterEvent)
            m_characterEvent(*this, static_cast<wchar_t>(event.text.text[0]));
		break;
	}
    default:
        break;
    }
}

class OpenGL21Renderer final : public Abyss::GUI::Renderer {
public:
    auto drawVertices(const Vertices &vertices, const Color &col) -> void final;
    auto drawColoredVertices(const ColoredVertices &vertices) -> void final;
};

inline auto OpenGL21Renderer::drawVertices(const Vertices &vertices, const Color &col) -> void
{
    glBegin(GL_POLYGON);
    glColor4d(static_cast<double>(col.r) / 255, static_cast<double>(col.g) / 255, static_cast<double>(col.b) / 255, static_cast<double>(col.a) / 255);
    for (auto vertex : vertices) {
        vertex /= {1600, 900, 0};
        vertex *= 2;
        vertex -= 1;
        vertex.y *= -1;
        glVertex2d(vertex.x, vertex.y);
    }
    glEnd();
}

inline auto OpenGL21Renderer::drawColoredVertices(const ColoredVertices &vertices) -> void
{
    glBegin(GL_POLYGON);
    for (auto [vertex, color] : vertices) {
        if (color.has_value())
            glColor4d(color->r / 255, color->g / 255, color->b / 255, color->a / 255);

        vertex /= {1600, 900, 0};
        vertex *= 2;
        vertex -= 1;
        vertex.y *= -1;
        glVertex2d(vertex.x, vertex.y);
    }
    glEnd();
}

static auto start() -> void
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    auto window{SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_OPENGL /*| SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP*/)};
    if (window == nullptr)
        throw std::runtime_error{"Couldn't create window"};

    auto openglContext{SDL_GL_CreateContext(window)};
    if (openglContext == nullptr)
        throw std::runtime_error{"Couldn't create OpenGL context"};

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    OpenGL21Renderer            renderer{};
    SDL2InputDevice             device{};
    Abyss::GUI::Widgets::Window win{};
	win.getBody().addChild<Abyss::GUI::Widgets::Textbox>();
    win.registerOnInputDevice(device);

    bool      run{true};
    SDL_Event event{};
    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                run = false;
            device.processEvent(event);
        }

        if (!run)
            break;

        glClear(GL_COLOR_BUFFER_BIT);

        renderer.setColor({255, 150, 0});
        renderer.drawRectangle({50, 50}, {1600 - 100, 900 - 100});

        renderer.drawColoredVertices({
        {{100, 50}, std::make_optional<Color>(255, 0, 0)},
        {{50, 150}, std::make_optional<Color>(0, 0, 0)},
        {{150, 150}, std::make_optional<Color>(255, 255, 255)},
        });

        double dt{0};
        win.thinkDispatch(device, dt);
        win.paintDispatch(device, dt, renderer);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int, char *[])
{
	WindowsConsole con{};
    srand(static_cast<unsigned int>(time(nullptr)));

    try {
        start();
    } catch (const std::exception &e) {
        // MessageBoxA(nullptr, e.what(), "Exception caught", 0);
    }
    return 0;
}
