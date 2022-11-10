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
    bool CastlingMove, EnPassantMove;

    Move(int sr, int sc, int er, int ec, ChessEngien gameState);
    Move(int sr, int sc, int er, int ec, ChessEngien gameState, bool isCastlingMove, bool isEnPassantMove);
    ~Move();

    bool operator==(const Move& move);
};

class moveStorages{
    private: 
    public:
        int startr, startc, endr, endc;

        moveStorages(int sr, int sc, int er, int ec);
        ~moveStorages(){};
};

