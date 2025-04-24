#include <emscripten.h>
#include <SDL2/SDL.h>

#include "include/Juego.hpp"
#include "include/Misc.hpp"

static void renderizar(ContextoJuego& contexto) noexcept;
//static void dibujar_linea_divisora(SDL_Renderer* rend) noexcept;
static void manejar_colisiones(ContextoJuego& contexto) noexcept;
static void verificar_bola_fuera(ContextoJuego& contexto) noexcept;

void game_loop(void* arg) noexcept {
    auto contexto = *static_cast<ContextoJuego*>(arg);
    auto renderer = contexto.display.renderer;

    SDL_Event evento;
    while (SDL_PollEvent(&evento)) {
        if (evento.type == SDL_QUIT) {
            emscripten_cancel_main_loop();
            return;
        }
    }

    const Uint8* teclas = SDL_GetKeyboardState(nullptr);
    if (teclas[SDL_SCANCODE_W]) {
        contexto.jugador1.mover(Jugador::Direccion::ARRIBA);
    }
    if (teclas[SDL_SCANCODE_S]) {
        contexto.jugador1.mover(Jugador::Direccion::ABAJO);
    }
    if (teclas[SDL_SCANCODE_UP]) {
        contexto.jugador2.mover(Jugador::Direccion::ARRIBA);
    }
    if (teclas[SDL_SCANCODE_DOWN]) {
        contexto.jugador2.mover(Jugador::Direccion::ABAJO);
    }

    contexto.bola.actualizar();
    manejar_colisiones(contexto);
    verificar_bola_fuera(contexto);
    renderizar(contexto);
}

static void renderizar(ContextoJuego& contexto) noexcept {
    auto renderer = contexto.display.renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //dibujar_linea_divisora(renderer);
    contexto.bola.dibujar(renderer);
    contexto.jugador1.dibujar(renderer);
    contexto.jugador2.dibujar(renderer);

    SDL_RenderPresent(renderer);
}

static void manejar_colisiones(ContextoJuego& contexto) noexcept {
    SDL_Rect rect_bola = contexto.bola.obtener_rectangulo();
    SDL_Rect rect_jugador1 = contexto.jugador1.obtener_rectangulo();
    SDL_Rect rect_jugador2 = contexto.jugador2.obtener_rectangulo();

    if (SDL_HasIntersection(&rect_bola, &rect_jugador1)) {
        contexto.bola.rebotar_horizontal();
        contexto.golpeador = &contexto.jugador1;
    } else if (SDL_HasIntersection(&rect_bola, &rect_jugador2)) {
        contexto.bola.rebotar_horizontal();
        contexto.golpeador = &contexto.jugador2;
    }
}

static void verificar_bola_fuera(ContextoJuego& contexto) noexcept {
    constexpr int margen = 20;
    SDL_Rect rect_bola = contexto.bola.obtener_rectangulo();

    if (rect_bola.x < (0 - rect_bola.w - margen) || rect_bola.x > WindowRenderer::ANCHO_DEFAULT + margen) {
        if (contexto.golpeador != nullptr) {
            char mensaje[100] = {0};
            std::snprintf(mensaje, 100, "Ganador: %s", Jugador::convertir_jugador_a_string(contexto.golpeador->obtener_numero_jugador()));
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Fin del juego", mensaje, contexto.display.window);
        }
        else {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Fin del juego", "Ay, que aburridos :|", contexto.display.window);
        }

        reiniciar_juego(contexto);
    }
}