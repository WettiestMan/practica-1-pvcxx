#include "include/Bola.hpp"
#include "include/WindowRenderer.hpp"
#include <algorithm>
#include <cstdlib>
#include <cmath>

Bola::Bola() {
    TexturaRect textura = Texturas::obtener_bola();
    if (textura.valido()) {
        textura_rectangulo = textura;
        reiniciar();
    } else {
        throw std::runtime_error("No se pudo obtener la textura de la bola.");
    }
}

void Bola::actualizar() noexcept {
    auto& rect = textura_rectangulo.rectangulo;
    // Actualizar posición
    rect.x += vel_x;
    rect.y += vel_y;
    
    // Colisiones con los bordes
    if (rect.y <= 0 || rect.y >= WindowRenderer::ALTO_DEFAULT - textura_rectangulo.rectangulo.h) {
        invertir_y();
    }
}

void Bola::dibujar(SDL_Renderer* rend) const noexcept {
    SDL_RenderCopy(rend, textura_rectangulo.textura, nullptr, &textura_rectangulo.rectangulo);
}

void Bola::reiniciar() noexcept {
    rebotes = 0;
    auto& rect = textura_rectangulo.rectangulo;
    rect.x = WindowRenderer::ANCHO_DEFAULT / 2.0f - rect.w / 2.0f;
    rect.y = WindowRenderer::ALTO_DEFAULT / 2.0f;
    vel_x = std::rand() % 2 == 0 ? VELOCIDAD_INICIAL : -VELOCIDAD_INICIAL;
    vel_y = VELOCIDAD_INICIAL;
}

SDL_Rect Bola::obtener_rectangulo() const noexcept {
    return textura_rectangulo.rectangulo;
}

void Bola::aumentar_rebotes() noexcept {
    rebotes++;

    if (rebotes % VELOCIDAD_PASO == 0) {
        const int aumento = rebotes / VELOCIDAD_PASO;
        vel_x += (std::signbit(vel_x) ? -1 : 1) * aumento;
        vel_y += (std::signbit(vel_y) ? -1 : 1) * aumento;
    }
}

void Bola::invertir_x() noexcept {
    vel_x = -vel_x;
}

void Bola::invertir_y() noexcept {
    vel_y = -vel_y;
}

void Bola::reposicionar_x(Jugador& j) noexcept {
    auto& rect = textura_rectangulo.rectangulo;

    constexpr int margen = 5;

    rect.x = j.obtener_rectangulo().x + (vel_x / std::abs(vel_x)) * (j.obtener_rectangulo().w);
}