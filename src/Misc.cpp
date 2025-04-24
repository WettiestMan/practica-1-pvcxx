#include "include/Misc.hpp"
#include <iostream>

void reiniciar_juego(ContextoJuego& contexto) noexcept {
    contexto.bola.reiniciar();
    contexto.jugador1.reiniciar_y();
    contexto.jugador2.reiniciar_y();
    contexto.golpeador = nullptr;
}