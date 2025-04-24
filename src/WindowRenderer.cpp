#include "include/WindowRenderer.hpp"

std::optional<WindowRenderer> WindowRenderer::iniciar(const char* titulo, int ancho, int alto) noexcept {
    WindowRenderer wr = {0};
    wr.window = SDL_CreateWindow(titulo, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho, alto, SDL_WINDOW_SHOWN);
    if (wr.window == nullptr) {
        return std::nullopt;
    }

    wr.renderer = SDL_CreateRenderer(wr.window, -1, SDL_RENDERER_ACCELERATED);
    if (!wr.renderer) {
        SDL_DestroyWindow(wr.window);
        wr.window = nullptr;
        return std::nullopt;
    }

    return wr;
}

void WindowRenderer::cerrar(WindowRenderer& wr) noexcept {
    if (wr.renderer) {
        SDL_DestroyRenderer(wr.renderer);
        wr.renderer = nullptr;
    }
    if (wr.window) {
        SDL_DestroyWindow(wr.window);
        wr.window = nullptr;
    }
}