#pragma once 

#include<iostream>
#include<vector>
#include<math.h>
#include<cstdlib>
#include<time.h>
#include "move.hpp"

using namespace std;
class Move;
class ChessAI{
    private:

    public:
        Move findRandomMove(vector<Move> validMove);
        ChessAI(){}
        ~ChessAI(){}
};