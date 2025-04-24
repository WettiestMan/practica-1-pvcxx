#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <SDL2/SDL.h>
#include <string>
#include <string_view>
#include <utility>

#include "WindowRenderer.hpp"

#include "Texturas.hpp"

class Jugador
{
public:
    enum class Direccion : int {
        QUIETO = 0,
        ARRIBA = -1,
        ABAJO = 1
    };

    enum class NumeroJugador : int{
        JUGADOR_1 = 0,
        JUGADOR_2 = WindowRenderer::ANCHO_DEFAULT - 50
    };

    Jugador(NumeroJugador jugador);
    void mover(Direccion dir) noexcept;
    void dibujar(SDL_Renderer* rend) const noexcept;
    SDL_Rect obtener_rectangulo() const noexcept;
    Jugador::NumeroJugador obtener_numero_jugador() const noexcept;
    static const char* convertir_jugador_a_string(NumeroJugador nj) noexcept;

private:
    static constexpr float VELOCIDAD_DEFAULT = 5.0f;
    float velocidad;
    TexturaRect textura_rectangulo;
    NumeroJugador numero_jugador;
    static const std::pair<int, char*> jugador_str[2];
};

#endif // JUGADOR_HPP