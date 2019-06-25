#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_ttf.h>

#pragma clang diagnostic pop

#include <cstdint>
#include <stdexcept>
#include <sstream>
#include <ctime>

#include "Abyss/GUI.hpp"
#include "SDL2Renderer.hpp"
#include "SDL2Mouse.hpp"
#include "WinAPIMouse.hpp"

static auto start() -> void
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    auto window{SDL_CreateWindow("IsekaiEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_VULKAN /*| SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP*/)};
    if (window == nullptr)
        throw std::runtime_error{"Couldn't create window"};

    auto renderer{SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)};
    if (renderer == nullptr)
        throw std::runtime_error{"Couldn't get renderer"};

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	// SDL_SetWindowOpacity(window, 0.5);

	SDL2Renderer sdl2renderer{renderer};
	SDL2Mouse sdl2mouse{};
	Abyss::Widgets::Window win{};

	win.getBody().addChild<Abyss::Widgets::Button>([]() {});

	sdl2mouse.onButtonAction = [&win](const Abyss::AMouse &mouse, Abyss::MOUSE button, Abyss::ACTION action) {
        win.mouseButtonEventDispatch(mouse, button, action, static_cast<Abyss::MODS>(0));
    };

    bool        run{true};
    SDL_Event   event{};
    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                run = false;

			sdl2mouse.receiveEvent(event);
		}

        if (!run)
            break;

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
        SDL_RenderClear(renderer);

		sdl2renderer.color({255, 150, 0});
		sdl2renderer.rectangle({50, 50}, {100, 300});

		sdl2mouse.update();
		win.think(sdl2mouse, 0);
		win.paint(sdl2mouse, 0, sdl2renderer);

        SDL_RenderPresent(renderer);
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
