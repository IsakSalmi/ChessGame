#pragma once
#include <iostream>
#include "Config.hpp"

#include <SDL2/SDL.h>

class game
{
private:
    const int WIDTH = BOARD_WIDTH, HEIGHT = BOARD_HEIGHT;

    SDL_Window *window;
    SDL_Renderer *rendere;

    SDL_Event windowEvent;

    int SQ_size;

    void drawEverything();
    void drawBoard();
public:
    game();
    ~game();
    void startGame();
};

