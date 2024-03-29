#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>
#include "Config.hpp"
#include "move.hpp"
#include "ChessEngine.hpp"
#include "ChessAI.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;
class game
{
private:
    const int WIDTH = BOARD_WIDTH, HEIGHT = BOARD_HEIGHT;
    const int fps = FPS;
    const int desiredDelta = 1000/fps;
    bool run, playerOne, playerTow;
    int startc, startr, endc, endr;

    SDL_Window *window;
    SDL_Renderer *rendere;

    SDL_Texture *wK, *wQ, *wB, *wN, *wR, *wP;
    SDL_Texture *bK, *bQ, *bB, *bN, *bR, *bP;

    SDL_Event windowEvent;

    SDL_Rect rect;
    int SQ_size;

    ChessEngien *chessEngien;
    ChessAI *AI;

    void drawEverything(int sqr, int sqc, vector<Move> validMoves);
    void drawBoard();
    void drawPieces();
    void highlightSquare(int sqr, int sqc, vector<Move> validMoves);
public:
    game();
    ~game();
    void startGame();
};

