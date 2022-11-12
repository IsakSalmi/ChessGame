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
    shuffle(validMoves.begin(), validMoves.end(),default_random_engine());
    if(gs.whiteToMove){turnMultiplyer = 1;}
    else{turnMultiplyer = -1;}

    findMoveMinMaxAlphaBeta(gs,validMoves,DEPTH,gs.whiteToMove,-checMate, checMate);

    return nextMove;
}

int ChessAI::findMoveMinMaxAlphaBeta(ChessEngien gs, vector<Move> validMoves, int depth ,bool whiteToMove, int alpha, int beta){
    int score;
    if(depth == 0){
        return scoreBoard(gs);
    }
    if(whiteToMove){
        int maxScore = -checMate;
        for(int i=0; i<validMoves.size();i++){
            gs.makeMove(validMoves[i]);
            vector<Move> nextMoves = gs.getValidMove();
            score = findMoveMinMaxAlphaBeta(gs,nextMoves,depth-1,false,alpha,beta);
            if(score > maxScore){
                maxScore = score;
                if(depth == DEPTH){
                    nextMove = validMoves[i];
                }
            }
            gs.undoMove();
            alpha = max(alpha, maxScore);
            if(beta <= alpha){
                break;
            }
        }
        return maxScore;
    }
    else{
        int minScore = checMate;
        for(int i=0; i<validMoves.size(); i++){
            gs.makeMove(validMoves[i]);
            vector<Move> nextMoves = gs.getValidMove();
            score = findMoveMinMaxAlphaBeta(gs,nextMoves,depth-1,true,alpha,beta);
            if(score < minScore){
                minScore = score;
                if(depth == DEPTH){
                    nextMove = validMoves[i];
                }
            }
            beta = min(beta, minScore);
            if(beta <= alpha){
                break;
            }
            gs.undoMove();

        }
        return minScore;
    }
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
    int piceInfluence = 5;
    int score = 0;
    for(int r=0; r<8; r++){
        for(int c=0; c<8; c++){
            int square = gs.pieceOnSquare(r,c);
            if(square != 0b00000000){
                if(square & 0b10000000){
                    switch (square - 0b10000000)
                    {
                    case 0b00100000:
                        score += (1 * piceInfluence);
                        score += whitePawnScore[r][c];
                        break;
                    case 0b00010000:
                        score += (5 * piceInfluence);
                        score += rookScore[r][c];
                        break;
                    case 0b00001000:
                        score += (3 * piceInfluence);
                        score += knightScore[r][c];
                        break;
                    case 0b00000100:
                        score += (3 * piceInfluence);
                        score += bishopScore[r][c];
                        break;
                    case 0b00000010:
                        score += (10 * piceInfluence);
                        score += queenScore[r][c];
                        break;
                    default:
                        break;
                    }
                }
                else if(square & 0b01000000){
                    switch (square - 0b01000000)
                    {
                    case 0b00100000:
                        score -= (1*piceInfluence);
                        score -= blackPawnScore[r][c];
                        break;
                    case 0b00010000:
                        score -= (5*piceInfluence);
                        score -= rookScore[r][c];
                        break;
                    case 0b00001000:
                        score -= (3*piceInfluence);
                        score -= knightScore[r][c];
                        break;
                    case 0b00000100:
                        score -= (3*piceInfluence);
                        score -= bishopScore[r][c];
                        break;
                    case 0b00000010:
                        score -= (10*piceInfluence);
                        score -= queenScore[r][c];
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
