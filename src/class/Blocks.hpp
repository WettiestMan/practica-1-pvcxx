#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "../functions/Consts.hpp"
#include "../functions/Utils.hpp"

class Blocks {
public:
    Blocks(SDL_Renderer* r, int rows, int cols, int& pref) : renderer(r), pointsRef(pref),
        rows(rows), cols(cols) {
        bricks.reserve(rows * cols);
        int totalW  = cols * Consts::BLOCK_W + (cols - 1) * Consts::BLOCK_GAP;
        int offsetX = (Consts::WINDOW_WIDTH - totalW) / 2;
        int offsetY = 60;

        for (int row = 0; row < rows; ++row)
            for (int col = 0; col < cols; ++col) {
                SDL_Rect b{ offsetX + col * (Consts::BLOCK_W + Consts::BLOCK_GAP),
                            offsetY + row * (Consts::BLOCK_H + Consts::BLOCK_GAP),
                            Consts::BLOCK_W, Consts::BLOCK_H };
                bricks.push_back(b);
            }
    }
    void checkCollisions(Ball& ball) {
        const auto& ballRect = ball.getRect();
        for (auto it = bricks.begin(); it != bricks.end();) {
            if (Utils::checkCollision(ballRect, *it)) {
                it = bricks.erase(it);
                ball.reverseY();
                pointsRef++;
            } else {
                ++it;
            }
        }
    }

    void checkDoneAndSpeedUp(Ball& ball) {
        if (bricks.empty()) {
            pointsRef += 10;
            reset();
            ball.speedUp();
        }
    }
    void fill() {
        int totalW  = cols * Consts::BLOCK_W + (cols - 1) * Consts::BLOCK_GAP;
        int offsetX = (Consts::WINDOW_WIDTH - totalW) / 2;
        int offsetY = 60;

        for (int row = 0; row < rows; ++row)
            for (int col = 0; col < cols; ++col) {
                SDL_Rect b{ offsetX + col * (Consts::BLOCK_W + Consts::BLOCK_GAP),
                            offsetY + row * (Consts::BLOCK_H + Consts::BLOCK_GAP),
                            Consts::BLOCK_W, Consts::BLOCK_H };
                bricks.push_back(b);
            }
    }

    void reset() {
        bricks.clear();
        fill();
    }

    void show() const {
        SDL_SetRenderDrawColor(renderer, 0, 180, 255, 255);
        for (const auto& b : bricks) SDL_RenderFillRect(renderer, &b);
    }
private:
    const int rows;
    const int cols;
    SDL_Renderer* renderer;
    std::vector<SDL_Rect> bricks;
    int& pointsRef;
};
