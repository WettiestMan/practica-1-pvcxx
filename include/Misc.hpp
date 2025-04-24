#ifndef MISC_HPP
#define MISC_HPP

#include "Juego.hpp"

void reiniciar_juego(ContextoJuego& contexto) noexcept;

inline bool revisar_colision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

#endif // MISC_HPP