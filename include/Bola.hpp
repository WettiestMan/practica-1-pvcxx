#ifndef BOLA_HPP
#define BOLA_HPP

#include <SDL2/SDL.h>
#include "texturas.hpp"

class Bola {
public:
    Bola();
    
    void actualizar() noexcept;
    void dibujar(SDL_Renderer* rend) const;
    void reiniciar() noexcept;
    SDL_Rect obtener_rectangulo() const noexcept;
    
    void aplicar_velocidad(float vx, float vy) noexcept;
    void aplicar_gravedad() noexcept;
    void rebotar_horizontal() noexcept;
    void rebotar_vertical() noexcept;

private:
    static constexpr float GRAVEDAD = 0.5f;
    static constexpr float VELOCIDAD_INICIAL = -10.0f;
    static constexpr float VELOCIDAD_MAXIMA = 15.0f;
    static constexpr float FACTOR_REBOTE = 0.8f;

    TexturaRect textura_rectangulo;
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
};

#endif // BOLA_HPP