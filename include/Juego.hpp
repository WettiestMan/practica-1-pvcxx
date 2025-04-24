#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "Bola.hpp"
#include "WindowRenderer.hpp"
#include "Jugador.hpp"

struct ContextoJuego
{
    WindowRenderer display;
    Bola bola;
    Jugador jugador1;
    Jugador jugador2;
    Jugador* golpeador;
};

void game_loop(void* arg) noexcept;

#endif // JUEGO_HPP