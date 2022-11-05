#pragma once
#include <iostream>
#include "Config.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;
class game
{
private:
    const int WIDTH = BOARD_WIDTH, HEIGHT = BOARD_HEIGHT;

    SDL_Window *window;
    SDL_Renderer *rendere;

    SDL_Texture *wK, *wQ, *wB, *wN, *wR, *wP;
    SDL_Texture *bK, *bQ, *bB, *bN, *bR, *bP;

    SDL_Event windowEvent;

    int SQ_size;

    void drawEverything();
    void drawBoard();
    void drawPieces();
public:
    game();
    ~game();
    void startGame();
};

