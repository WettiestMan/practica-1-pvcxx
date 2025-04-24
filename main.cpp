#include <emscripten.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <optional>
#include <cstdlib>
#include <ctime>

#include "include/WindowRenderer.hpp"
#include "include/texturas.hpp"
#include "include/Bola.hpp"
#include "include/Jugador.hpp"
#include "include/Juego.hpp"

int main(void) {
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL2 no pudo inicializarse: " << SDL_GetError() << std::endl;
		return 1;
	}

	std::optional<WindowRenderer> tal_vez_display = WindowRenderer::iniciar("Pong!", 
		WindowRenderer::ANCHO_DEFAULT, WindowRenderer::ALTO_DEFAULT);
	if (!tal_vez_display) {
		std::cerr << "No se pudieron crear la ventana y el renderer: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	if (Texturas::iniciar(tal_vez_display->renderer) != Texturas::OK) {
		std::cerr << "No se pudieron crear las texturas: " << SDL_GetError() << std::endl;
		WindowRenderer::cerrar(tal_vez_display.value());
		SDL_Quit();
		return 1;
	}

	ContextoJuego ctx = {
		tal_vez_display.value(),
		Bola(),
		Jugador(Jugador::NumeroJugador::JUGADOR_1),
		Jugador(Jugador::NumeroJugador::JUGADOR_2),
		nullptr
	};

	emscripten_set_main_loop_arg(game_loop, &ctx, 0, true);

	return 0;
}
