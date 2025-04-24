#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <SDL2/SDL.h>
#include <string>
#include <string_view>

#include "include/WindowRenderer.hpp"

#include "texturas.hpp"

class Jugador
{
public:
    enum class Direccion { ARRIBA = -1, ABAJO = 1};
    enum class NumeroJugador { JUGADOR_1 = 50 / 2, JUGADOR_2 = WindowRenderer::ANCHO_DEFAULT - 50 / 2};

    Jugador(std::string_view nombre);
    void mover(Direccion dir) noexcept;
    void dibujar(SDL_Renderer* rend) const;
    SDL_Rect obtener_rectangulo() const noexcept;

private:
    static constexpr float VELOCIDAD_DEFAULT = 5.0f;
    float velocidad;
    std::string nombre;
    TexturaRect textura_rectangulo;
    int posicion_y = 0;
};

#endif // JUGADOR_HPP