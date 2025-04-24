#include <SDL2/SDL.h>
#include <emscripten.h>

#include "src/functions/Consts.hpp"
#include "src/class/Paddle.hpp"
#include "src/class/Ball.hpp"
#include "src/class/Blocks.hpp"

SDL_Window*   window   = nullptr;
SDL_Renderer* renderer = nullptr;

Paddle* paddle = nullptr;
Ball*   ball   = nullptr;
Blocks* blocks = nullptr;

void loop() {
    SDL_Event e;
    while (SDL_PollEvent(&e))
    if (e.type == SDL_QUIT) { 
        SDL_Quit(); 
        return; 
    }

    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    ball->update();
    paddle->handleInput(keys);
    paddle->checkCollisions(ball);
    blocks->checkCollisions(ball);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    
    ball->show();
    blocks->show();
    paddle->show();

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Minimal Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Consts::WINDOW_WIDTH, Consts::WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    ball   = new Ball(renderer);
    ball->center();
    ball->startMovement();

    paddle = new Paddle(renderer);
    paddle->center();

    blocks = new Blocks(renderer, 5, 10);

    emscripten_set_main_loop(loop, 0, 1);
    return 0;
}
