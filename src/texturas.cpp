#include <stdexcept>
#include <SDL2/SDL.h>
#include <string>

#include "include/texturas.hpp"

SDL_Texture* Texturas::raqueta = nullptr;
SDL_Texture* Texturas::bola = nullptr;
SDL_Texture* Texturas::segmento_linea_divisora = nullptr;

bool Texturas::iniciado = false;

bool TexturaRect::valido() const noexcept {
    return textura != nullptr;
}

Texturas::ErrorInicializacion Texturas::iniciar(SDL_Renderer* rend) {
    if (rend == nullptr) return ERROR_RENDERER_ES_NULL;

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
            SDL_RenderFillRect(rend, nullptr) == 0 &&
            SDL_SetRenderTarget(rend, bola) == 0 &&
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255) == 0 &&
            SDL_RenderFillRect(rend, nullptr) == 0 &&
            SDL_SetRenderTarget(rend, segmento_linea_divisora) == 0 &&
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255) == 0 &&
            SDL_RenderFillRect(rend, nullptr) == 0) {

            iniciado = true;
        }

        if (SDL_SetRenderTarget(rend, prev_rend_target)) {
            cerrar();
            return ERROR_RESTAURAR_TARGET;
        }
    }

    if (!iniciado) {
        cerrar();
    }
    
    return iniciado ? OK : ERROR_CREACION_TEX;
}

TexturaRect Texturas::obtener_raqueta() noexcept {
    return {raqueta, rect_raqueta};
}

TexturaRect Texturas::obtener_bola() noexcept {
    return {bola, rect_bola};
}

TexturaRect Texturas::obtener_segmento_linea_divisora() noexcept {
    return {segmento_linea_divisora, rect_segmento_linea_divisora};
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