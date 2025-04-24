#ifndef BOLA_HPP
#define BOLA_HPP

#include <SDL2/SDL.h>
#include "texturas.hpp"
#include "Jugador.hpp"

class Bola {
public:
    Bola();
    
    void actualizar() noexcept;
    void dibujar(SDL_Renderer* rend) const noexcept;
    void reiniciar() noexcept;
    SDL_Rect obtener_rectangulo() const noexcept;
    
    void aumentar_rebotes() noexcept;
    void invertir_x() noexcept;
    void invertir_y() noexcept;
    void reposicionar_x(Jugador& J) noexcept;

private:
    static constexpr float VELOCIDAD_INICIAL = 5.0f;
    static constexpr int VELOCIDAD_PASO = 6; 

    TexturaRect textura_rectangulo;
    float vel_x;
    float vel_y;
    int rebotes;
};

#endif // BOLA_HPP