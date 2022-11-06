#include "../include/ChessEngine.hpp"

ChessEngien::ChessEngien(){
}

ChessEngien::~ChessEngien(){
}

int ChessEngien::pieceOnSquare(int r, int c){return board[r][c];}

void ChessEngien::makeMove(Move newMove){
    int movingPiece = board[newMove.startr][newMove.startc];
    
    board[newMove.endr][newMove.endc] = movingPiece;
    board[newMove.startr][newMove.startc] = 0b00000000;

}


vector<Move> ChessEngien::allPossibleMove(){
    moves.clear();

    moves.push_back(Move(6,0,5,0,*this));
    return moves;
}

