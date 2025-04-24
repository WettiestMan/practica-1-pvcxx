#pragma once

#include <SDL2/SDL.h>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Blocks.hpp"

struct Context {
    SDL_Window* window   = nullptr;
    SDL_Renderer* renderer = nullptr;
    Paddle paddle;
    Ball ball;
    Blocks blocks;
    int points;
    bool gameOver;
};