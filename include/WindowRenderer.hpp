#ifndef WINDOWRENDERER_HPP
#define WINDOWRENDERER_HPP

#include <SDL2/SDL.h>
#include <optional>
#include <expected>
#include <string>

struct WindowRenderer
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    static constexpr int ANCHO_DEFAULT = 800;
    static constexpr int ALTO_DEFAULT = 600;

    /**
     * @brief Genera una ventana y un renderer de SDL.
     * @param titulo Titulo de la ventana.
     * @param ancho Ancho de la ventana.
     * @param alto Alto de la ventana.
     * @return Un objeto WindowRenderer con la ventana y el renderer creados, o std::nullopt si hubo un error.
     */
    static std::optional<WindowRenderer> iniciar(const char* titulo, int ancho, int alto) noexcept;

    /**
     * @brief Cierra la ventana y el renderer de SDL.
     * @param wr Referencia al objeto WindowRenderer a cerrar.
     */
    static void cerrar(WindowRenderer& wr) noexcept;
};

#endif // WINDOWRENDERER_HPP