#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

#pragma clang diagnostic pop

#include "Abyss/GUI/Interfaces/Renderer.hpp"

#include <cstdint>
#include <ctime>
#include <gl\GLU.h>
#include <sstream>
#include <stdexcept>

class OpenGL21Renderer final : public Abyss::GUI::Renderer {
public:
    auto drawVertices(const Vertices &vertices, const Color &col) -> void final;
    auto drawColoredVertices(const ColoredVertices &vertices) -> void final;
};

auto OpenGL21Renderer::drawVertices(const Vertices &vertices, const Color &col) -> void
{
    glBegin(GL_QUADS);
    glColor4d(col.r / 255, col.g / 255, col.b / 255, col.a / 255);
    for (auto vertex : vertices) {
        vertex /= {1600, 900, 0};
        vertex *= 2;
        vertex -= 1;
        vertex.y *= -1;
        glVertex2d(vertex.x, vertex.y);
    }
    glEnd();
}

auto OpenGL21Renderer::drawColoredVertices(const ColoredVertices &vertices) -> void
{
    glBegin(GL_QUADS);
    for (auto [vertex, color] : vertices) {
        glColor4d(color.r / 255, color.g / 255, color.b / 255, color.a / 255);
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

    OpenGL21Renderer renderer{};

    bool      run{true};
    SDL_Event event{};
    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                run = false;
        }

        if (!run)
            break;

        glClear(GL_COLOR_BUFFER_BIT);

        renderer.setColor({255, 150, 0});
        renderer.drawRectangle({50, 50}, {1600 - 100, 900 - 100});

        renderer.drawColoredVertices({
        {{50, 50}, {255, 0, 0}},
        {{50, 150}, {0, 255, 0}},
        {{150, 150}, {0, 0, 255}},
        {{150, 50}, {255, 255, 0}},
        });

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int, char *[])
{
    srand(static_cast<unsigned int>(time(nullptr)));

    try {
        start();
    } catch (const std::exception &e) {
        MessageBoxA(nullptr, e.what(), "Exception caught", 0);
    }
    return 0;
}
