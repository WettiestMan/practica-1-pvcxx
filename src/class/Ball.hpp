#pragma once
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include "../functions/Consts.hpp"
#include "../functions/Utils.hpp"

class Ball
{
private:
    static constexpr float BALL_ACCEL_FACTOR = 1.1f;
public:
    explicit Ball(SDL_Renderer *r, const Paddle& paddle) // Modificar constructor
        : renderer(r), paddle(paddle)
    { // Inicializar referencia al paddle
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        rect.w = rect.h = Consts::BALL_SIZE;
    }
    void center()
    {
        rect.x = (Consts::WINDOW_WIDTH - rect.w) / 2;
        rect.y = (Consts::WINDOW_HEIGHT - rect.h) / 2;
    }
    void startMovement()
    {
        vx = (std::rand() % 2 ? 1 : -1) * Consts::BALL_SPEED;
        vy = -Consts::BALL_SPEED;
    }
    void update(bool& gameOver)
    {
        rect.x += static_cast<int>(vx);
        rect.y += static_cast<int>(vy);

        // Colisión con bordes
        if (rect.x <= 0 || rect.x + rect.w >= Consts::WINDOW_WIDTH)
            reverseX();
        if (rect.y <= 0)
            reverseY();

        // Colisión con paddle
        if (Utils::checkCollision(rect, paddle.getRect()))
        {
            reverseY();
            rect.y = paddle.getRect().y - rect.h; // Ajuste de posición
        }

        // Colisión con el fondo (reinicio)
        if (rect.y + rect.h >= Consts::WINDOW_HEIGHT)
        {
            gameOver = true;
            center();
            startMovement();
        }
    }
    void reverseY()
    {
        vy = -vy;
    }
    void reverseX()
    {
        vx = -vx;
    }
    const SDL_Rect &getRect() const
    {
        return rect;
    }
    void show() const
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    void speedUp() noexcept
    {
        vx *= BALL_ACCEL_FACTOR;
        vy *= BALL_ACCEL_FACTOR;
    }

private:
    SDL_Renderer *renderer;
    const Paddle& paddle;
    SDL_Rect rect{};
    float vx = 0, vy = 0;
};
