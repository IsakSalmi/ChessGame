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

    for(int r = 0; r < BOARD_DIMENTION; r++){
        for(int c = 0; c < BOARD_DIMENTION; c++){
            switch (this->board[r][c])
            {
            case 0b10100000:
                getPawnMove(r,c,this->board[r][c]);
                break;
            
            default:
                break;
            }
        }
    }
    
    return moves;
}

void ChessEngien::getPawnMove(int startr, int startc, int piece){
    if(piece & 0b10000000){
        moves.push_back(Move(startr,startc,startr - 2, startc, *this));
        moves.push_back(Move(startr,startc,startr - 1, startc, *this));
    }
}

