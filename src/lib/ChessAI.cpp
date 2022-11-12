#include "../include/ChessAI.hpp"

ChessAI::ChessAI(){
    checMate = 10000;
    staleMate = 0;
}

Move ChessAI::findRandomMove(vector<Move> validMove){
    srand(time(0));
    int index = rand() % validMove.size();
    return validMove[index];
}

Move ChessAI::findeBestMove(ChessEngien gs, vector<Move> validMoves){
    nextMove = Move(-1,-1,-1,-1, gs);
    int turnMultiplyer;
    if(gs.whiteToMove){turnMultiplyer = 1;}
    else{turnMultiplyer = -1;}

    findMoveNegaMaxAlphaBeta(gs,validMoves,DEPTH,-1*checMate,checMate,turnMultiplyer);

    return nextMove;
}

int ChessAI::findMoveNegaMaxAlphaBeta(ChessEngien gs, vector<Move> validMoves, int depth, int alpha, int beta, int turnMultiplier){
    if(depth == 0){
        return turnMultiplier * scoreBoard(gs);
    }

    int maxScore = -checMate;
    for(int i=0; i<validMoves.size(); i++){
        vector<Move> NextMoves = gs.getValidMove();
        gs.makeMove(validMoves[i]);
        int score = -1*findMoveNegaMaxAlphaBeta(gs,NextMoves,depth-1, -1 * beta, -1 * alpha, -1 * turnMultiplier);
        if(score > maxScore){
            maxScore = score;
            if(depth == DEPTH){
                nextMove = NextMoves[i];
                cout << score << endl;
                cout << " " << endl;
            }
        }
        gs.undoMove();
        if(maxScore > alpha){
            alpha = maxScore;
        }
        if(alpha >= beta){
            break;
        }
    }
    return maxScore;

}



int ChessAI::scoreBoard(ChessEngien gs){
    if(gs.checkMate){
        if(gs.whiteToMove){
            return -checMate;
        }
        else{
            return checMate;
        }
    }
    else if(gs.staleMate){
        return staleMate;
    }
    int score = 0;
    for(int r=0; r<8; r++){
        for(int c=0; c<8; c++){
            int square = gs.pieceOnSquare(r,c);
            if(square != 0b00000000){
                if(square & 0b10000000){
                    switch (square - 0b10000000)
                    {
                    case 0b00100000:
                        score += 1;
                        break;
                    case 0b00010000:
                        score += 5;
                        break;
                    case 0b00001000:
                        score += 3;
                        break;
                    case 0b00000100:
                        score += 3;
                        break;
                    case 0b00000010:
                        score += 10;
                        break;
                    default:
                        break;
                    }
                }
                if(square & 0b01000000){
                    switch (square - 0b01000000)
                    {
                    case 0b00100000:
                        score -= 1;
                        break;
                    case 0b00010000:
                        score -= 5;
                        break;
                    case 0b00001000:
                        score -= 3;
                        break;
                    case 0b00000100:
                        score -= 3;
                        break;
                    case 0b00000010:
                        score -= 10;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    return score;
}
