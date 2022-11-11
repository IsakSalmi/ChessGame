#include "../include/ChessAI.hpp"

Move ChessAI::findRandomMove(vector<Move> validMove){
    srand(time(0));
    int index = rand() % validMove.size();
    return validMove[index];
}