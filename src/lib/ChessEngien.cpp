#include "../include/ChessEngine.hpp"

ChessEngien::ChessEngien(){
    whiteToMove = true;
}

ChessEngien::~ChessEngien(){
}

int ChessEngien::pieceOnSquare(int r, int c){return board[r][c];}

void ChessEngien::makeMove(Move newMove){
    int movingPiece = board[newMove.startr][newMove.startc];
    
    board[newMove.endr][newMove.endc] = movingPiece;
    board[newMove.startr][newMove.startc] = 0b00000000;
    whiteToMove = !whiteToMove;

}


vector<Move> ChessEngien::allPossibleMove(){
    moves.clear();
    for(int r = 0; r < BOARD_DIMENTION; r++){
        for(int c = 0; c < BOARD_DIMENTION; c++){
            //white pieces
            if(whiteToMove){
                if(this->board[r][c] & 0b10000000){
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
            else{
            //black pieces
                if((this->board[r][c] & 0b01000000)){
                    switch (this->board[r][c])
                        {
                        case 0b01100000:
                            getPawnMove(r,c,this->board[r][c]);
                            break;
                        
                        default:
                            break;
                    }
                }
            }
        }
    }
    
    return moves;
}

void ChessEngien::getPawnMove(int startr, int startc, int piece){
    if(piece & 0b10000000){
        if((startr == 6) && (board[startr-2][startc] == 0b00000000)){
            moves.push_back(Move(startr,startc,startr - 2, startc, *this));
        }

        if(board[startr-1][startc] == 0b00000000){
            moves.push_back(Move(startr,startc,startr - 1, startc, *this));
        }

        if(board[startr-1][startc+1] & 0b01000000){
            moves.push_back(Move(startr,startc,startr-1,startc+1,*this));
        }
    }
    else if((piece & 0b01000000)){
        if((startr == 1)and (board[startr+2][startc] == 0b00000000)){
            moves.push_back(Move(startr,startc,startr + 2, startc, *this));
        }
        if(board[startr+1][startc] == 0b00000000){
            moves.push_back(Move(startr,startc,startr + 1, startc, *this));
        }
    }
}

