#include "../include/move.hpp"



Move::Move(int sr, int sc, int er, int ec, ChessEngien gameState){
    startc = sc;
    startr = sr;
    endr = er;
    endc = ec;
    pieceMoved = gameState.pieceOnSquare(startr,startc);
    pieceCapture = gameState.pieceOnSquare(endr,endc);
    CastlingMove = false;
}

Move::Move(int sr, int sc, int er, int ec, ChessEngien gameState, bool isCastlingMove){
    startc = sc;
    startr = sr;
    endr = er;
    endc = ec;
    pieceMoved = gameState.pieceOnSquare(startr,startc);
    pieceCapture = gameState.pieceOnSquare(endr,endc);
    CastlingMove = isCastlingMove;
}

Move::~Move()
{
}

bool Move::operator==(const Move& move){
    if((move.startc == startc)&&(move.startr == startr)&&(move.endc == endc)&&(move.endr == endr)){return true;}
    else{return false;}
}