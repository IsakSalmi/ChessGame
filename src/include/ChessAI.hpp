#pragma once 

#include<iostream>
#include<vector>
#include<math.h>
#include<cstdlib>
#include<time.h>
#include <algorithm>
#include <thread>
#include <future>
#include <chrono>
#include <random>
#include "move.hpp"
#include "Config.hpp"

using namespace std;
class Move;
class ChessAI{
    private:

    public:
        int checMate, staleMate;

        int knightScore[8][8] = {{0,0,1,1,1,1,0,0},
                                 {0,1,2,2,2,2,1,0},
                                 {0,2,3,3,3,3,2,0},
                                 {0,2,3,4,4,3,2,0},
                                 {0,2,3,4,4,3,2,0},
                                 {0,2,3,3,3,3,2,0},
                                 {0,1,2,2,2,2,1,0},
                                 {0,0,1,1,1,1,0,0}};
    
        int bishopScore[8][8] = {{3,2,1,1,1,1,2,3},
                                 {2,3,2,2,2,2,3,2},
                                 {1,2,3,2,2,3,2,1},
                                 {1,2,2,3,3,2,2,1},
                                 {1,2,2,3,3,2,2,1},
                                 {1,2,3,2,2,3,2,1},
                                 {2,3,2,2,2,2,3,2},
                                 {3,2,1,1,1,1,2,3}};

        int queenScore[8][8] = {{1,1,1,2,1,1,1,1},
                                {1,2,2,2,1,1,1,1},
                                {1,3,3,3,3,3,2,1},
                                {1,2,3,3,3,3,2,1},
                                {1,2,3,3,3,3,2,1},
                                {1,3,3,3,3,3,2,1},
                                {1,2,2,2,1,1,1,1},
                                {1,1,1,2,1,1,1,1}};

        int rookScore[8][8] = {{2,2,3,4,4,3,2,2},
                               {4,4,4,4,4,4,4,4},
                               {1,2,3,3,3,3,2,1},
                               {1,2,3,3,3,3,2,1},
                               {1,2,3,3,3,3,2,1},
                               {1,2,3,3,3,3,2,1},
                               {4,4,4,4,4,4,4,4},
                               {2,2,3,4,4,3,2,2}};

        int whitePawnScore[8][8] = {{8,8,8,8,8,8,8,8},
                                    {8,8,8,8,8,8,8,8},
                                    {5,6,6,7,7,6,6,5},
                                    {2,3,3,5,5,3,3,2},
                                    {1,2,3,6,6,3,2,1},
                                    {1,1,2,4,4,2,1,1},
                                    {1,1,1,0,0,1,1,1},
                                    {0,0,0,0,0,0,0,0}};

        int blackPawnScore[8][8] = {{0,0,0,0,0,0,0,0},
                                    {1,1,1,0,0,1,1,1},
                                    {1,1,2,4,4,2,1,1},
                                    {1,2,3,6,6,3,2,1},
                                    {2,3,3,5,5,3,3,2},
                                    {5,6,6,7,7,6,6,5},
                                    {8,8,8,8,8,8,8,8},
                                    {8,8,8,8,8,8,8,8}};

        int  kingScore[8][8] = {{1,2,4,0,0,0,4,1},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {1,2,4,0,0,0,4,1}};

        Move nextMove;
        int findMoveNegaMaxAlphaBeta(ChessEngien gs, vector<Move> validMoves, int depth, int alpha, int beta, int turnMultiplier);
        int scoreBoard(ChessEngien gs);
        int findMoveMinMaxAlphaBeta(ChessEngien gs, vector<Move> validMoves, int depth ,bool whiteToMove, int alpha, int beta);
        Move findRandomMove(vector<Move> validMove);
        Move findeBestMove(ChessEngien gs, vector<Move> validMoves);
        ChessAI();
        ~ChessAI(){}
};