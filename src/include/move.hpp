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
    bool CastlingMove;

    Move(int sr, int sc, int er, int ec, ChessEngien gameState);
    Move(int sr, int sc, int er, int ec, ChessEngien gameState, bool isCastlingMove);
    ~Move();

    bool operator==(const Move& move);
};

