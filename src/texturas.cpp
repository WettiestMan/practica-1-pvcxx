#include "include/texturas.hpp"
#include <stdexcept>
#include <SDL2/SDL.h>

SDL_Texture* Texturas::raqueta = nullptr;
SDL_Texture* Texturas::bola = nullptr;
SDL_Texture* Texturas::segmento_linea_divisora = nullptr;

bool Texturas::iniciado = false;

bool Texturas::iniciar(SDL_Renderer* rend) {
    if (rend == nullptr) return false;

    auto prev_rend_target = SDL_GetRenderTarget(rend);
    raqueta = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET,
                                rect_raqueta.w, rect_raqueta.h);
    bola = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET,
                                rect_bola.w, rect_bola.h);
    segmento_linea_divisora = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET,
                                rect_segmento_linea_divisora.w, rect_segmento_linea_divisora.h);

    if (raqueta != nullptr && bola != nullptr && segmento_linea_divisora != nullptr) {
        if (SDL_SetRenderTarget(rend, raqueta) == 0 &&
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255) == 0 &&
            SDL_RenderFillRect(rend, nullptr) == 0) {

            if (SDL_SetRenderTarget(rend, bola) == 0 &&
                SDL_SetRenderDrawColor(rend, 255, 255, 255, 255) == 0 &&
                SDL_RenderFillRect(rend, nullptr) == 0) {

                if (SDL_SetRenderTarget(rend, segmento_linea_divisora) == 0 &&
                    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255) == 0 &&
                    SDL_RenderFillRect(rend, nullptr) == 0) {

                    iniciado = true;
                }
            }
        }

        // En general, tu no quieres tirar excepciones al momento de escribir videojuegos (a menos que uses Java o C#, supongo)
        // porque en general es muy costoso en rendimiento. En este caso, sin embargo, decidí hacerlo
        // porque no poder restaurar el render target es un error de ejecución grave.
        // es probable que haya mejores maneras de manejarlo, pero esto es lo que se me ocurrió.
        // (también tuve que descartar "noexcept" aquí :( )
        //
        // No te preocupes por los recursos, esta función llama Texturas::cerrar() para liberarlos
        if (SDL_SetRenderTarget(rend, prev_rend_target)) {
            cerrar();
            using namespace std::string_literals;
            throw std::runtime_error("Error al restaurar el render target: "s + SDL_GetError());
        }
    }
    else {
        if (raqueta != nullptr) {
            SDL_DestroyTexture(raqueta);
            raqueta = nullptr;
        }
        if (bola != nullptr) {
            SDL_DestroyTexture(bola);
            bola = nullptr;
        }
        if (segmento_linea_divisora != nullptr) {
            SDL_DestroyTexture(segmento_linea_divisora);
            segmento_linea_divisora = nullptr;
        }
    }
    
    return iniciado;
}

SDL_Texture* Texturas::obtener_raqueta() noexcept {
    return iniciado ? raqueta : nullptr;
}

SDL_Texture* Texturas::obtener_bola() noexcept {
    return iniciado ? bola : nullptr;
}

SDL_Texture* Texturas::obtener_segmento_linea_divisora() noexcept {
    return iniciado ? segmento_linea_divisora : nullptr;
}

bool Texturas::esta_iniciado() noexcept {
    return iniciado;
}

void Texturas::cerrar() noexcept {
    if (raqueta != nullptr) SDL_DestroyTexture(raqueta);
    if (bola != nullptr) SDL_DestroyTexture(bola);
    if (segmento_linea_divisora != nullptr) SDL_DestroyTexture(segmento_linea_divisora);
    segmento_linea_divisora = nullptr;
    raqueta = nullptr;
    bola = nullptr;
    iniciado = false;
}