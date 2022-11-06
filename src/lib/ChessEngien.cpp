#include "../include/ChessEngine.hpp"

ChessEngien::ChessEngien(){
}

ChessEngien::~ChessEngien(){
}

int ChessEngien::pieceOnSquare(int c, int r){return board[c][r];}

void ChessEngien::makeMove(int startc, int startr, int endc, int endr){
    int movingPiece = board[startr][startc];
    
    board[endr][endc] = movingPiece;
    board[startr][startc] = 0b00000000;
}