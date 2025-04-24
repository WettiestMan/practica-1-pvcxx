#ifndef TEXTURAS_HPP
#define TEXTURAS_HPP

#include <SDL2/SDL.h>
#include <optional>

/**
 * @brief Estructura que representa una textura y su rectángulo asociado.
 * @note Los recursos que son proveidos por esta estructura no deben ser liberados por separado.
 * Se requiere que Texturas::cerrar() sea llamado para liberar los recursos de las texturas.
 * (tener en cuenta que llamar a Texturas::cerrar() liberará todos los recursos de las texturas
 * por lo que ningún objeto TexturaRect podrá ser usado después de eso).
 */
struct TexturaRect
{
    SDL_Texture* textura;
    SDL_Rect rectangulo;

    bool valido() const noexcept;
};

class Texturas
{
public:
    static constexpr int ANCHO_TEX_RAQUETA = 30;
    static constexpr int ALTO_TEX_RAQUETA = 200;
    static constexpr int ANCHO_TEX_BOLA = 15;
    static constexpr int ALTO_TEX_BOLA = 15;
    static constexpr int ANCHO_TEX_SEGMENTO_LINEA_DIVISORA = 10;
    static constexpr int ALTO_TEX_SEGMENTO_LINEA_DIVISORA = 20;

    enum ErrorInicializacion
    {
        OK = 0,
        ERROR_CREACION_TEX = 1,
        ERROR_RENDERER_ES_NULL = 2,
        ERROR_RESTAURAR_TARGET = 3
    };

    /**
     * @brief Inicializa las texturas de la aplicación.
     * @param rend El renderer de SDL donde se crearán las texturas.
     * @return Texturas::OK si la inicialización fue exitosa, u otro valor si hubo un error.
     * @note Si la inicialización falla, se liberarán todos los recursos de las texturas.
     */
    static ErrorInicializacion iniciar(SDL_Renderer* rend);
    static void cerrar() noexcept;
    static TexturaRect obtener_raqueta() noexcept;
    static TexturaRect obtener_bola() noexcept;
    static TexturaRect obtener_segmento_linea_divisora() noexcept;
    static bool esta_iniciado() noexcept;

private:
    static SDL_Texture* raqueta;
    static SDL_Texture* bola;
    static SDL_Texture* segmento_linea_divisora;
    static bool iniciado;

    static constexpr SDL_Rect rect_raqueta = {0, 0, ANCHO_TEX_RAQUETA, ALTO_TEX_RAQUETA};
    static constexpr SDL_Rect rect_bola = {0, 0, ANCHO_TEX_BOLA, ANCHO_TEX_BOLA};
    static constexpr SDL_Rect rect_segmento_linea_divisora = {0, 0, ANCHO_TEX_SEGMENTO_LINEA_DIVISORA,
        ALTO_TEX_SEGMENTO_LINEA_DIVISORA};
};

#endif // TEXTURAS_HPP