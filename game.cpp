#include <SDL2/SDL.h>
#include <emscripten.h>
#include <iostream>
#include <cstdio>

#include "src/functions/Consts.hpp"
#include "src/class/Paddle.hpp"
#include "src/class/Ball.hpp"
#include "src/class/Blocks.hpp"
#include "src/class/Context.hpp"

void loop(void* arg) {
    auto ctx = static_cast<Context*>(arg);
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT) { SDL_Quit(); return; }

    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    ctx->paddle.handleInput(keys);
    ctx->ball.update(ctx->gameOver);

    if(!ctx->gameOver) {
        ctx->blocks.checkCollisions(ctx->ball);
        ctx->blocks.checkDoneAndSpeedUp(ctx->ball);
    }
    else {
        char msg[100];
        std::snprintf(msg, sizeof(msg), "¡Perdiste! Obtuviste %d puntos.", ctx->points);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ou", msg, ctx->window);
        ctx->blocks.reset();
        ctx->points = 0;
        ctx->gameOver = false;
    }

    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);

    ctx->blocks.show();
    ctx->paddle.show();
    ctx->ball.show();

    SDL_RenderPresent(ctx->renderer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Really Minimal Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Consts::WINDOW_WIDTH, Consts::WINDOW_HEIGHT, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);

    if (!window || !renderer) {
        std::cerr << "Error creando ventana o renderer: " << SDL_GetError() << std::endl;
        if (window) SDL_DestroyWindow(window);
        if (renderer) SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 1;
    }

    // instanciación
    Context ctx = { window,
        renderer,
        Paddle(renderer),
        Ball(renderer, ctx.paddle),
        Blocks(renderer, 5, 10, ctx.points), // 5 filas, 10 columnas
        0
    };
    ctx.paddle.center();

    ctx.ball.center();
    ctx.ball.startMovement();

    emscripten_set_main_loop_arg(loop, &ctx, 0, 1);
    return 0;
}
