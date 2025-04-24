#include "include/Jugador.hpp"
#include "include/texturas.hpp"
#include "include/WindowRenderer.hpp"

#include <iostream>

const std::pair<int, const char*> Jugador::jugador_str[2] = {
    {static_cast<int>(NumeroJugador::JUGADOR_1), "Jugador 1"},
    {static_cast<int>(NumeroJugador::JUGADOR_2), "Jugador 2"}
};

Jugador::Jugador(NumeroJugador jugador) : numero_jugador(jugador), velocidad(VELOCIDAD_DEFAULT) {
    TexturaRect textura = Texturas::obtener_raqueta();
    if (textura.valido()) {
        rectangulo = textura.rectangulo;
        this->textura = textura.textura;

        rectangulo.y = WindowRenderer::ALTO_DEFAULT / 2 - textura.rectangulo.h / 2;
        rectangulo.x = static_cast<int>(numero_jugador);
    } else {
        throw std::runtime_error("No se pudo obtener la textura de la raqueta.");
    }
}

void Jugador::mover(Direccion dir) noexcept {
    if (dir == Direccion::ARRIBA) {
        rectangulo.y -= velocidad;
    }
    else if (dir == Direccion::ABAJO) {
        rectangulo.y += velocidad;
    }

    if (rectangulo.y < 0) {
        rectangulo.y = 0;
    } else if (rectangulo.y + rectangulo.h > WindowRenderer::ALTO_DEFAULT) {
        rectangulo.y = WindowRenderer::ALTO_DEFAULT - rectangulo.h;
    }
}

void Jugador::dibujar(SDL_Renderer* rend) const noexcept {
    SDL_RenderCopy(rend, textura, nullptr, &rectangulo);
}

SDL_Rect Jugador::obtener_rectangulo() const noexcept {
    return rectangulo;
}

Jugador::NumeroJugador Jugador::obtener_numero_jugador() const noexcept {
    return numero_jugador;
}

const char* Jugador::convertir_jugador_a_string(NumeroJugador nj) noexcept {
    const char* str = nullptr;
    for (const auto& par : jugador_str) {
        if (par.first == static_cast<int>(nj)) {
            str = par.second;
            break;
        }
    }

    return str;
}

void Jugador::reiniciar_y() noexcept {
    rectangulo.y = WindowRenderer::ALTO_DEFAULT / 2 - rectangulo.h / 2;
}