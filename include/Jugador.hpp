#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <SDL2/SDL.h>
#include <string>
#include <string_view>

#include "include/WindowRenderer.hpp"

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

    Jugador(std::string_view nombre);
    void mover(Direccion dir) noexcept;
    void dibujar(SDL_Renderer* rend) const noexcept;
    SDL_Rect obtener_rectangulo() const noexcept;

private:
    static constexpr float VELOCIDAD_DEFAULT = 5.0f;
    float velocidad;
    std::string nombre;
    TexturaRect textura_rectangulo;
};

#endif // JUGADOR_HPP