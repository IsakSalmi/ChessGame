#pragma once 

#include<iostream>
#include<vector>
#include<math.h>
#include<cstdlib>
#include<time.h>
#include "move.hpp"
#include "Config.hpp"

using namespace std;
class Move;
class ChessAI{
    private:
        int checMate, staleMate;

        Move nextMove;
        int findMoveNegaMaxAlphaBeta(ChessEngien gs, vector<Move> validMoves, int depth, int alpha, int beta, int turnMultiplier);
        int scoreBoard(ChessEngien gs);
        int findMoveMinMax(ChessEngien gs, vector<Move> validMoves, int depth ,bool whiteToMove, int alpha, int beta);

    public:
        Move findRandomMove(vector<Move> validMove);
        Move findeBestMove(ChessEngien gs, vector<Move> validMoves);
        ChessAI();
        ~ChessAI(){}
};