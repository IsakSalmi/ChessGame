#include "../include/ChessEngine.hpp"

ChessEngien::ChessEngien(){
    whiteToMove = true;

    castleRightBKS = true;
    castleRightBQS = true;
    castleRightWKS = true;
    castleRightWQS = true;

    wKingLocationR = 7;
    wKingLocationC = 4;
    bKingLocationR = 0;
    bKingLocationC = 4;

    enPassantPossibleCol = -1;
    enPassantPossibleRow = -1;

}

ChessEngien::~ChessEngien(){
}

int ChessEngien::pieceOnSquare(int r, int c){return board[r][c];}


void ChessEngien::makeMove(Move newMove){
    int movingPiece = board[newMove.startr][newMove.startc];
    int team;
    if(whiteToMove){team = 0b10000000;}
    else{team = 0b01000000;}
    
    board[newMove.endr][newMove.endc] = movingPiece;
    board[newMove.startr][newMove.startc] = 0b00000000;
    moveLogs.push_back(newMove);

    if(movingPiece == 0b10000001){
        wKingLocationR = newMove.endr;
        wKingLocationC = newMove.endc;
    }
    else if(movingPiece == 0b01000001){
        bKingLocationR = newMove.endr;
        bKingLocationC = newMove.endc;
    }

    if(newMove.CastlingMove){
        if(newMove.endc < newMove.startc){
            board[newMove.endr][0] = 0b00000000;
            board[newMove.endr][newMove.endc + 1] = team + 0b00010000;
        }
        else{
            board[newMove.endr][7] = 0b00000000;
            board[newMove.endr][newMove.endc - 1] = team + 0b00010000;
        }
    }

    if((newMove.pieceMoved & 0b00100000) && (abs(newMove.endr - newMove.startr) == 2)){
        enPassantPossibleRow = floor((newMove.startr + newMove.endr) / 2);
        enPassantPossibleCol = newMove.endc; 
    }
    else{
        enPassantPossibleCol = -1;
        enPassantPossibleRow = -1;
    }

    if(newMove.EnPassantMove){
        board[newMove.startr][newMove.endc] = 0b00000000;
    }

    whiteToMove = !whiteToMove;
    updateCastlingRights(newMove);

}


void ChessEngien::undoMove(){
    if(moveLogs.size() != 0){
        Move move = moveLogs.back();
        moveLogs.pop_back();
        board[move.startr][move.startc] = move.pieceMoved;
        if(!move.EnPassantMove){
            board[move.endr][move.endc] = move.pieceCapture;
        }

        if(move.pieceMoved == 0b10000001){
            wKingLocationR = move.startr;
            wKingLocationC = move.startc;
        }
        if(move.pieceMoved == 0b01000001){
            bKingLocationR = move.startr;
            bKingLocationC = move.startc;
        }

        if(move.CastlingMove){
            if(move.endc < move.startc){
                if(move.pieceMoved == 0b10000001){
                    board[7][0] = 0b10010000;
                    board[7][3] = 0b00000000;
                    castleRightWQS = true;
                    castleRightWKS = true;
                }
                else{
                    board[0][0] = 0b01010000;
                    board[0][3] = 0b00000000;
                    castleRightBQS = true;
                    castleRightBKS = true;
                }
            }
            else{
                if(move.pieceMoved == 0b10000001){
                    board[7][7] = 0b10010000;
                    board[7][5] = 0b00000000;
                    castleRightWKS = true;
                    castleRightWQS = true;
                }
                else{
                    board[0][7] = 0b01010000;
                    board[0][5] = 0b00000000;
                    castleRightBKS = true;
                    castleRightBQS = true;
                }
            }
        }

        if(move.pieceMoved & 0b00010000){
            if(move.startr == 7 && move.startc == 7){
                castleRightWKS = true;
            }
            else if(move.startr == 7 && move.startc == 0){
                castleRightWQS = true;
            }
            else if(move.startr == 0 && move.startc == 7){
                castleRightBKS = true;
            }
            else if(move.startr == 0 && move.startc == 0){
                castleRightBQS = true;
            }
        }

        if(move.EnPassantMove){
            board[move.endr][move.endc] = 0b00000000;
            board[move.startr][move.endc] = move.pieceCapture;
        }
        

        whiteToMove = !whiteToMove;
    }
    else{
        cout << "no move to undo" << endl;
    }
}



void ChessEngien::updateCastlingRights(Move move){
    if(move.pieceMoved == 0b10000001){
        castleRightWKS = false;
        castleRightWQS = false;
    }
    else if(move.pieceMoved == 0b01000001){
        castleRightBKS = false;
        castleRightBQS = false;
    }
    else if(move.pieceMoved == 0b10010000){
        if((move.startr == 7) &&(move.startc == 0)){
            castleRightWQS = false;
        }
        if((move.startr == 7)&&(move.startc == 7)){
            castleRightWKS = false;
        }
    }
    else if(move.pieceMoved == 0b01010000){
        if((move.startr == 0) && (move.startc == 0)){
            castleRightBQS = false;
        }
        if((move.startr == 0) && (move.startc == 7)){
            castleRightBKS = false;
        }
    }
}


void ChessEngien::allPossibleMove(){
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
                        case 0b10000100:
                            getBishoppMove(r,c,this->board[r][c]);
                            break;
                        case 0b10000010:
                            getQueenMove(r,c,this->board[r][c]);
                        case 0b10000001:
                            getKingmove(r,c,this->board[r][c]);
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
                        case 0b01000100:
                            getBishoppMove(r,c,this->board[r][c]);
                            break;
                        case 0b01000010:
                            getQueenMove(r,c,this->board[r][c]);
                        case 0b01000001:
                            getKingmove(r,c,this->board[r][c]);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}


vector<Move> ChessEngien::getValidMove(){
    moves.clear();

    allPossibleMove();
    

    int kingr, kingc;
    if(whiteToMove){
        kingr = wKingLocationR;
        kingc = wKingLocationC;
    }
    if(!whiteToMove){
        kingr = bKingLocationR;
        kingc = bKingLocationC;
    }

    getCastlingMoves(kingr,kingc,board[kingr][kingc]);

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


        if((startr-1 == enPassantPossibleRow) && (startc - 1 == enPassantPossibleCol)){
            moves.push_back(Move(startr, startc, startr -1, startc -1, *this, false, true));
        }
        if((startr-1 == enPassantPossibleRow) && (startc + 1 == enPassantPossibleCol)){
            moves.push_back(Move(startr, startc, startr-1, startc+1, *this, false, true));
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

        if((startr+1 == enPassantPossibleRow) && (startc - 1 == enPassantPossibleCol)){
            moves.push_back(Move(startr, startc, startr+1, startc -1, *this, false, true));
        }
        if((startr+1 == enPassantPossibleRow) && (startc + 1 == enPassantPossibleCol)){
            moves.push_back(Move(startr, startc, startr+1, startc+1, *this, false, true));
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
                    else{break;}
                }
                else{break;}
            }
        }
    }
}


void ChessEngien::getBishoppMove(int startr, int startc, int piece){


    int direction[4][2] = {{-1,1},{-1,-1},{1,1},{1,-1}};
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
                    else{break;}
                }
                else{break;}
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
                    else{break;}
                }
                else{break;}
            }
        }
    }
}


void ChessEngien::getQueenMove(int startr, int startc, int piece){
    getBishoppMove(startr, startc, piece);
    getRookMove(startr, startc, piece);
}


void ChessEngien::getKingmove(int startr, int startc, int piece){
    int direction[8][2] = {{1,-1},{1,0},{1,1},{-1,-1},{-1,0},{-1,1},{0,-1},{0,1}};
    int endr, endc, team;
    if(piece & 0b10000000){team = 0b10000000;}
    else{team = 0b01000000;}

    for(int i=0; i<8; i++){
        endr = startr + direction[i][0];
        endc = startc + direction[i][1];
        if((0 >= endr < BOARD_DIMENTION) && (0 >= endc < BOARD_DIMENTION) && !(board[endr][endc] & team)){
            moves.push_back(Move(startr,startc,endr,endc,*this));
        }
    }
}


void ChessEngien::getCastlingMoves(int startr, int startc, int piece){
    if((whiteToMove && castleRightWKS) or (!(whiteToMove) && castleRightBKS)){
        if((board[startr][startc +1] == 0b00000000) && (board[startr][startc+2] == 0b00000000)){
            moves.push_back(Move(startr,startc,startr,startc+2,*this,true,false));
        }
    }
    if((whiteToMove && castleRightWQS) or (!(whiteToMove) && castleRightBQS)){
        if((board[startr][startc -1] == 0b00000000) && (board[startr][startc-2] == 0b00000000)){
            moves.push_back(Move(startr,startc,startr,startc-2,*this,true,false));
        }
    }
}









