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
                        case 0b10001000:
                            getKnightMove(r,c,this->board[r][c]);
                            break;
                        case 0b10010000:
                            getRookMove(r,c,this->board[r][c]);
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
                        case 0b01001000:
                            getKnightMove(r,c,this->board[r][c]);
                            break;
                        case 0b01010000:
                            getRookMove(r,c,this->board[r][c]);
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
    if((piece & 0b10000000) && startr != 0){
        if((startr == 6) && (board[startr-2][startc] == 0b00000000)){
            moves.push_back(Move(startr,startc,startr - 2, startc, *this));
        }

        if(board[startr-1][startc] == 0b00000000){
            moves.push_back(Move(startr,startc,startr - 1, startc, *this));
        }


        if(board[startr-1][startc+1] & 0b01000000){
            moves.push_back(Move(startr,startc,startr-1,startc+1,*this));
        }
        else if(board[startr-1][startc-1] & 0b01000000){
            moves.push_back(Move(startr,startc,startr-1,startc-1,*this));
        }
    }
    else if((piece & 0b01000000) && startr != 7){
        if((startr == 1)and (board[startr+2][startc] == 0b00000000)){
            moves.push_back(Move(startr,startc,startr + 2, startc, *this));
        }
        if(board[startr+1][startc] == 0b00000000){
            moves.push_back(Move(startr,startc,startr + 1, startc, *this));
        }


        if(board[startr+1][startc+1] & 0b10000000){
            moves.push_back(Move(startr,startc,startr+1,startc+1,*this));
        }
        else if(board[startr+1][startc-1] & 0b10000000){
            moves.push_back(Move(startr,startc,startr+1,startc-1,*this));
        }
    }
}


void ChessEngien::getKnightMove(int startr, int startc, int piece){
    int direction[8][2] = {{-1,-2},{-2,-1},{1,-2},{2,-1},{1,2},{2,1},{-1,2},{-2,1}};
    int endr, endc;
    if(piece & 0b10000000){
        for(int d = 0; d < 8;d++){
            endr = startr + direction[d][0];
            endc = startc + direction[d][1];
            if((0 >= endr < BOARD_DIMENTION) && (0 >= endr < BOARD_DIMENTION) && !(board[endr][endc] & 0b10000000)){
                moves.push_back(Move(startr,startc,endr,endc,*this));
            }
        }
    }
    else{
        for(int d = 0; d < 8;d++){
            endr = startr + direction[d][0];
            endc = startc + direction[d][1];
            if((0 >= endr < BOARD_DIMENTION) && (0 >= endc < BOARD_DIMENTION) && !(board[endr][endc] & 0b01000000)){
                moves.push_back(Move(startr,startc,endr,endc,*this));
            }
        }
    }
}


void ChessEngien::getRookMove(int startr, int startc, int piece){
    int direction[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int endr, endc;
    if(piece & 0b10000000){
        for(int i = 0; i < 4;i++){
            for(int z =1 ; z < 8; z++){
                endr = startr + (direction[i][0] * z);
                endc = startc + (direction[i][1] * z);
                if((0 >= endr < BOARD_DIMENTION) && (0 >= endc < BOARD_DIMENTION)){
                    if(board[endr][endc] == 0b00000000){
                        moves.push_back(Move(startr,startc,endr,endc,*this));
                    }
                    else if(board[endr][endc] & 0b01000000){
                        moves.push_back(Move(startr,startc,endr,endc,*this));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
        }
    }
    else{
        for(int i = 0; i < 4;i++){
            for(int z =1 ; z < 8; z++){
                endr = startr + (direction[i][0] * z);
                endc = startc + (direction[i][1] * z);
                if((0 >= endr < BOARD_DIMENTION) && (0 >= endc < BOARD_DIMENTION)){
                    if(board[endr][endc] == 0b00000000){
                        moves.push_back(Move(startr,startc,endr,endc,*this));
                    }
                    else if(board[endr][endc] & 0b10000000){
                        moves.push_back(Move(startr,startc,endr,endc,*this));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
        }
    }
}

