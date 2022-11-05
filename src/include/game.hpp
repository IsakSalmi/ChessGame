#pragma once
#include <iostream>
#include "Config.hpp"
#include "ChessEngine.hpp"

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

    SDL_Rect rect;
    int SQ_size;

    ChessEngien chessEngien;

    void drawEverything();
    void drawBoard();
    void drawPieces();
public:
    game();
    ~game();
    void startGame();
};

