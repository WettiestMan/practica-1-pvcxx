#include "include/Bola.hpp"
#include "include/WindowRenderer.hpp"
#include <algorithm>

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
    aplicar_gravedad();
    
    // Actualizar posición
    pos_x += vel_x;
    pos_y += vel_y;
    
    // Limitar la velocidad máxima
    vel_x = std::clamp(vel_x, -VELOCIDAD_MAXIMA, VELOCIDAD_MAXIMA);
    vel_y = std::clamp(vel_y, -VELOCIDAD_MAXIMA, VELOCIDAD_MAXIMA);
    
    // Colisiones con los bordes
    if (pos_x <= 0 || pos_x >= WindowRenderer::ANCHO_DEFAULT - textura_rectangulo.rectangulo.w) {
        rebotar_horizontal();
    }
    if (pos_y <= 0 || pos_y >= WindowRenderer::ALTO_DEFAULT - textura_rectangulo.rectangulo.h) {
        rebotar_vertical();
    }
    
    // Actualizar el rectángulo de la textura
    textura_rectangulo.rectangulo.x = static_cast<int>(pos_x);
    textura_rectangulo.rectangulo.y = static_cast<int>(pos_y);
}

void Bola::dibujar(SDL_Renderer* rend) const {
    SDL_RenderCopy(rend, textura_rectangulo.textura, nullptr, &textura_rectangulo.rectangulo);
}

void Bola::reiniciar() noexcept {
    pos_x = WindowRenderer::ANCHO_DEFAULT / 2.0f - textura_rectangulo.rectangulo.w / 2.0f;
    pos_y = WindowRenderer::ALTO_DEFAULT / 2.0f;
    vel_x = 0.0f;
    vel_y = VELOCIDAD_INICIAL;
}

SDL_Rect Bola::obtener_rectangulo() const noexcept {
    return textura_rectangulo.rectangulo;
}

void Bola::aplicar_velocidad(float vx, float vy) noexcept {
    vel_x += vx;
    vel_y += vy;
}

void Bola::aplicar_gravedad() noexcept {
    vel_y += GRAVEDAD;
}

void Bola::rebotar_horizontal() noexcept {
    vel_x = -vel_x * FACTOR_REBOTE;
    // Ajustar posición para evitar pegarse a los bordes
    pos_x = std::clamp(pos_x, 0.0f, 
        static_cast<float>(WindowRenderer::ANCHO_DEFAULT - textura_rectangulo.rectangulo.w));
}

void Bola::rebotar_vertical() noexcept {
    vel_y = -vel_y * FACTOR_REBOTE;
    // Ajustar posición para evitar pegarse a los bordes
    pos_y = std::clamp(pos_y, 0.0f, 
        static_cast<float>(WindowRenderer::ALTO_DEFAULT - textura_rectangulo.rectangulo.h));
}