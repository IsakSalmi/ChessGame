#pragma once

#include <iostream>
#include "ChessEngine.hpp"

class ChessEngien;

using namespace std;

class Move
{
private:

public:
    int startr, startc, endr, endc;
    int pieceMoved;
    int pieceCapture;

    Move(int sr, int sc, int er, int ec, ChessEngien gameState);
    ~Move();
};

