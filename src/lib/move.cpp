#include "../include/move.hpp"



Move::Move(int sr, int sc, int er, int ec, ChessEngien gameState){
    startc = sc;
    startr = sr;
    endr = er;
    endc = ec;
    pieceMoved = gameState.pieceOnSquare(startc,startr);
    pieceCapture = gameState.pieceOnSquare(endc,endr);
}

Move::~Move()
{
}