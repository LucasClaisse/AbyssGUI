#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <SDL.h>
#include <SDL_ttf.h>

#pragma clang diagnostic pop

#include "Abyss/GUI/Interfaces/IRenderer.hpp"

#include <codecvt>
#include <locale>
#include <stdexcept>
#include <unordered_map>

class SDL2Renderer final : public Abyss::IRenderer {
private:
    SDL_Color                                                                    m_textColor{255, 255, 255, 255};
    SDL_Renderer *                                                               m_renderer{nullptr};
    std::unordered_map<std::string, std::unordered_map<std::size_t, TTF_Font *>> m_fonts{};
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>                       m_converter{};

public:
    SDL2Renderer(decltype(m_renderer) renderer);
    ~SDL2Renderer() final;

    auto color(const Color &color) -> void final;
    auto rectangle(const Vector3<double> &pos, const Vector3<double> &size) -> void final;
    auto textColor(const Color &color) -> void final;
    auto text(const Vector3<double> &pos, const std::string &font, std::size_t size, const std::wstring &str) -> void final;
    auto line(const Vector3<double> &p1, const Vector3<double> &p2) -> void final;
    auto roundedRectangle(const Vector3<double> &pos, const Vector3<double> &size) -> void final;
};

inline SDL2Renderer::SDL2Renderer(decltype(m_renderer) renderer)
    : m_renderer{renderer}
{
}

inline SDL2Renderer::~SDL2Renderer()
{
    /*for (const auto &[size, font] : m_fonts)
        TTF_CloseFont(font);*/
}

inline auto SDL2Renderer::color(const Color &color) -> void
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
}

inline auto SDL2Renderer::rectangle(const Vector3<double> &pos, const Vector3<double> &size) -> void
{
    SDL_Rect rect{static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.y)};
    SDL_RenderFillRect(m_renderer, &rect);
}

inline auto SDL2Renderer::textColor(const Color &color) -> void
{
	m_textColor.r = color.r;
	m_textColor.g = color.g;
	m_textColor.b = color.b;
	m_textColor.a = color.a;
}

inline auto SDL2Renderer::text(const Vector3<double> &pos, const std::string &font, std::size_t size, const std::wstring &str) -> void
{
    if (auto it{m_fonts.find(font)}; it == m_fonts.cend() || ((*it).second.find(size) == (*it).second.cend())) {
        auto &cachedFont{m_fonts[font][size]};

        cachedFont = TTF_OpenFont(font.c_str(), static_cast<int>(size));
        if (cachedFont == nullptr)
            throw std::runtime_error{"Couldn't create font"};
    }

    auto &       cachedFont{m_fonts[font][size]};
    SDL_Surface *surface{TTF_RenderUTF8_Blended(cachedFont, m_converter.to_bytes(str).c_str(), m_textColor)};
    if (surface == nullptr)
        return;

    SDL_Texture *texture{SDL_CreateTextureFromSurface(m_renderer, surface)};
    if (texture != nullptr) {
        int texW{0};
        int texH{0};
        SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
        SDL_Rect rect{static_cast<int>(pos.x), static_cast<int>(pos.y), texW, texH};
        SDL_RenderCopy(m_renderer, texture, nullptr, &rect);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

inline auto SDL2Renderer::line(const Vector3<double> &, const Vector3<double> &) -> void
{
}

inline auto SDL2Renderer::roundedRectangle(const Vector3<double> &pos, const Vector3<double> &size) -> void
{
    Vector3<double> lineSize{size.x - 2, 1};

    rectangle({pos.x + 1, pos.y}, lineSize);
    rectangle({pos.x, pos.y + 1}, {size.x, size.y - 2});
    rectangle({pos.x + 1, pos.y + size.y - 1}, lineSize);
}
