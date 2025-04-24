#include <SDL2/SDL.h>
#include <string>
#include <string_view>

#include "texturas.hpp"

class Jugador
{
public:
    enum class Direccion { ARRIBA = -1, ABAJO = 1};

    Jugador(std::string_view nombre);
    void mover(Direccion dir);
    void dibujar(SDL_Renderer* rend) const;

private:
    static constexpr float VELOCIDAD_DEFAULT = 5.0f;
    float velocidad;
    std::string nombre;
    TexturaRect textura_rectangulo;
};