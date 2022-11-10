#include "../include/move.hpp"



Move::Move(int sr, int sc, int er, int ec, ChessEngien gameState){
    startc = sc;
    startr = sr;
    endr = er;
    endc = ec;
    pieceMoved = gameState.pieceOnSquare(startr,startc);
    pieceCapture = gameState.pieceOnSquare(endr,endc);
    CastlingMove = false;
    EnPassantMove = false;
}

Move::Move(int sr, int sc, int er, int ec, ChessEngien gameState, bool isCastlingMove, bool isEnPassantMove){
    startc = sc;
    startr = sr;
    endr = er;
    endc = ec;
    pieceMoved = gameState.pieceOnSquare(startr,startc);
    pieceCapture = gameState.pieceOnSquare(endr,endc);
    CastlingMove = isCastlingMove;
    EnPassantMove = isEnPassantMove;
    if(isEnPassantMove){
        pieceCapture = gameState.pieceOnSquare(startr,endc);
    }
}

Move::~Move()
{
}

bool Move::operator==(const Move& move){
    if((move.startc == startc)&&(move.startr == startr)&&(move.endc == endc)&&(move.endr == endr)){return true;}
    else{return false;}
}




moveStorages::moveStorages(int sr, int sc, int er, int ec){
    startr = sr;
    startc = sc;
    endr = er;
    endc = ec;
}