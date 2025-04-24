#include "include/Jugador.hpp"
#include "include/Texturas.hpp"
#include "include/WindowRenderer.hpp"

const std::pair<int, char*> Jugador::jugador_str[2] = {
    {static_cast<int>(NumeroJugador::JUGADOR_1), "Jugador 1"},
    {static_cast<int>(NumeroJugador::JUGADOR_2), "Jugador 2"}
};

Jugador::Jugador(NumeroJugador jugador) : numero_jugador(jugador), velocidad(VELOCIDAD_DEFAULT) {
    TexturaRect textura = Texturas::obtener_raqueta();
    if (textura.valido()) {
        textura_rectangulo.rectangulo = textura.rectangulo;
        textura_rectangulo.textura = textura.textura;

        textura_rectangulo.rectangulo.y = WindowRenderer::ALTO_DEFAULT / 2 - textura.rectangulo.h / 2;
        textura_rectangulo.rectangulo.x = static_cast<int>(numero_jugador);
    } else {
        throw std::runtime_error("No se pudo obtener la textura de la raqueta.");
    }
}

void Jugador::mover(Direccion dir) noexcept {
    textura_rectangulo.rectangulo.y += static_cast<int>(dir) * velocidad;

    if (textura_rectangulo.rectangulo.y < 0) {
        textura_rectangulo.rectangulo.y = 0;
    } else if (textura_rectangulo.rectangulo.y + textura_rectangulo.rectangulo.h > WindowRenderer::ALTO_DEFAULT) {
        textura_rectangulo.rectangulo.y = WindowRenderer::ALTO_DEFAULT - textura_rectangulo.rectangulo.h;
    }
}

void Jugador::dibujar(SDL_Renderer* rend) const noexcept {
    SDL_RenderCopy(rend, textura_rectangulo.textura, nullptr, &textura_rectangulo.rectangulo);
}

SDL_Rect Jugador::obtener_rectangulo() const noexcept {
    return textura_rectangulo.rectangulo;
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