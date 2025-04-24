#include "include/Jugador.hpp"
#include "include/Texturas.hpp"
#include "include/WindowRenderer.hpp"

Jugador::Jugador(std::string_view nombre) : nombre(nombre), velocidad(VELOCIDAD_DEFAULT) {
    TexturaRect textura = Texturas::obtener_raqueta();
    if (textura.valido()) {
        textura_rectangulo.rectangulo = textura.rectangulo;
        textura_rectangulo.textura = textura.textura;

        posicion_y = WindowRenderer::ALTO_DEFAULT / 2;
        textura_rectangulo.rectangulo.x = static_cast<int>(NumeroJugador::JUGADOR_1);
    } else {
        throw std::runtime_error("No se pudo obtener la textura de la raqueta.");
    }
}

