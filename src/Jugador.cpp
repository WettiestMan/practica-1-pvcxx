#include "include/Jugador.hpp"
#include "include/texturas.hpp"

Jugador::Jugador(std::string_view nombre) : nombre(nombre), velocidad(VELOCIDAD_DEFAULT) {
    TexturaRect textura = Texturas::obtener_raqueta();
    if (TexturaRect::valido(textura)) {
        textura_rectangulo = textura;
    } else {
        throw std::runtime_error("No se pudo obtener la textura de la raqueta.");
    }
}