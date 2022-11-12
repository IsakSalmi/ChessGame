#pragma once

#include <iostream>
#include <vector>
#include<cstdlib>
#include<time.h>
#include <math.h>
#include "move.hpp"
#include "Config.hpp"

using namespace std;
class Move;
class moveStorages;
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
    vector<Move> moveLogs;

    void allPossibleMove();

    void getPawnMove(int startr, int startc, int piece);
    void getKnightMove(int startr, int startc, int piece);
    void getRookMove(int startr, int startc, int piece);
    void getBishoppMove(int startr, int startc, int piece);
    void getQueenMove(int startr, int startc, int piece);
    void getKingmove(int startr, int startc, int piece);
    void getCastlingMoves(int startr, int startc, int piece);

    bool castleRightWKS, castleRightBKS, castleRightWQS, castleRightBQS;
    void updateCastlingRights(Move move);

    int wKingLocationR, wKingLocationC, bKingLocationR, bKingLocationC;
    int enPassantPossibleRow, enPassantPossibleCol;

    bool isUnderAttck(int r, int c);

    void checkForPinsAndChecks();
    bool inCheck;
    vector<moveStorages> pins;
    vector<moveStorages> checks;


public:
    bool staleMate, checkMate;
    int pieceOnSquare(int r, int c);
    void makeMove(Move newMove);
    void undoMove();
    vector<Move> getValidMove();
    bool whiteToMove;

    Move findRandomMove(vector<Move> validMove);
    Move findeBestMove(vector<Move> validMoves);

    ChessEngien();
    ~ChessEngien();
};

