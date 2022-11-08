#pragma once

#include <vector>
#include <iostream>
#include "move.hpp"
#include "Config.hpp"

using namespace std;
class Move;
class ChessEngien{
private:
    // 0b10000000 = white    0b010000000 = black
    // 0b00100000 = pawn 0b00010000 = rook   0b00001000 = knight   0b00000100 = biship 
    // 0b00000010 = quine   0b00000001 = king  0b00000000 = emty
    int board[8][8] = {{0b01010000, 0b01001000, 0b01000100, 0b01000010, 0b01000001, 0b01000100, 0b01001000, 0b01010000},
                       {0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01100000},
                       {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
                       {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
                       {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
                       {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
                       {0b10100000, 0b10100000, 0b10100000, 0b10100000, 0b10100000, 0b10100000, 0b10100000, 0b10100000},
                       {0b10010000, 0b10001000, 0b10000100, 0b10000010, 0b10000001, 0b10000100, 0b10001000, 0b10010000}}; 
    vector<Move> moves;
    void getPawnMove(int startr, int startc, int piece);
    void getKnightMove(int startr, int startc, int piece);

    bool whiteToMove;

public:
    int pieceOnSquare(int r, int c);
    void makeMove(Move newMove);
    vector<Move> allPossibleMove();

    ChessEngien();
    ~ChessEngien();
};

