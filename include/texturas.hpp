#include <SDL2/SDL.h>

class Texturas
{
private:
    static SDL_Texture* raqueta;
    static SDL_Texture* bola;
    static SDL_Texture* segmento_linea_divisora;
    static bool iniciado;

    static constexpr SDL_Rect rect_raqueta = {0, 0, 50, 300};
    static constexpr SDL_Rect rect_bola = {0, 0, 25, 25};
    static constexpr SDL_Rect rect_segmento_linea_divisora = {0, 0, 10, 20};

public:
    static bool iniciar(SDL_Renderer* rend);
    static void cerrar() noexcept;
    static SDL_Texture* obtener_raqueta() noexcept;
    static SDL_Texture* obtener_bola() noexcept;
    static SDL_Texture* obtener_segmento_linea_divisora() noexcept;
    static bool esta_iniciado() noexcept;
};