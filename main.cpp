#include <emscripten.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <optional>

#include "include/WindowRenderer.hpp"
#include "include/texturas.hpp"

int main(void) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL2 no pudo inicializarse: " << SDL_GetError() << std::endl;
		return 1;
	}

	std::optional<WindowRenderer> tal_vez_display = WindowRenderer::iniciar("SDL2 Emscripten", 800, 600);
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

	return 0;
}
