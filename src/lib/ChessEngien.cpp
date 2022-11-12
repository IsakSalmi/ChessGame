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

    inCheck = false;
    checkMate = false;
    staleMate = false;

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

    if(movingPiece & 0b00100000){
        if(whiteToMove && newMove.endr == 0){
            board[newMove.endr][newMove.endc] = 0b10000010;  
        }
        else if(!whiteToMove && newMove.endr == 7){
            board[newMove.endr][newMove.endc] = 0b01000010;
        }
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

    if(whiteToMove){
        whiteToMove = false;
    }
    else{
        whiteToMove = true;
    }
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
        
        checkMate = false;
        staleMate = false;
        if(whiteToMove){
            whiteToMove = false;
        }
        else{
            whiteToMove = true;
        }
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

    checkForPinsAndChecks();

    vector<Move> newMove;
    newMove.clear();

    int kingr, kingc;
    if(whiteToMove){
        kingr = wKingLocationR;
        kingc = wKingLocationC;
    }
    if(!whiteToMove){
        kingr = bKingLocationR;
        kingc = bKingLocationC;
    }

    if(inCheck){
        if(checks.size()==1){
            allPossibleMove();
            newMove = moves;
            moveStorages check = checks[0];
            int checkRow = check.startr;
            int checkCol = check.startc;

            int piceChecking = board[checkRow][checkCol];
            vector<pair<int,int>> validSquers;
            pair<int, int> squer;

            if(piceChecking & 0b00001000){
                squer.first = checkRow;
                squer.second = checkCol;
                validSquers.push_back(squer);
            }
            else{
                for(int i=1; i<8; i++){
                    squer.first = kingr + (check.endr * i);
                    squer.second = kingc + (check.endc * i);
                    validSquers.push_back(squer);
                    if((squer.first == checkRow) && (squer.second == checkCol)){
                        break;
                    } 
                }
            }
            moves.clear();
            for(int i = newMove.size()-1; -1 < i ; i--){
                for(int z=0; z<validSquers.size(); z++){
                    if((newMove[i].endr == validSquers[z].first) && (moves[i].endc == validSquers[z].second) or 
                    ((newMove[i].pieceMoved == 0b01000001 or newMove[i].pieceMoved == 0b10000001))){
                        moves.push_back(newMove[i]);
                    }
                }
            }
        }
        else{
            getKingmove(kingr,kingc,this->board[kingr][kingc]);
        }
    }
    else{
        allPossibleMove();
    }
    
    if(moves.size() == 0){
        if(inCheck){
            checkMate = true;
        }
        else{
            staleMate = true;
        }
    }

    getCastlingMoves(kingr,kingc,board[kingr][kingc]);

    return moves;
}


void ChessEngien::getPawnMove(int startr, int startc, int piece){

    bool picePinned = false;
    pair<int,int> pinDirection;
    for(int i=0; i<pins.size(); i++){
        if(pins[i].startr == startr && pins[i].startc == startc){
            picePinned = true;
            pinDirection.first = pins[i].endr;
            pinDirection.second = pins[i].endc;
            pins.erase(pins.begin()+i);
            break;
        }
    }

    if((piece & 0b10000000) && startr != 0){
        if(!picePinned or (pinDirection.first == -1 && pinDirection.second == 0)){
            if((startr == 6) && (board[startr-2][startc] == 0b00000000)){
                moves.push_back(Move(startr,startc,startr - 2, startc, *this));
            }

            if(board[startr-1][startc] == 0b00000000){
                moves.push_back(Move(startr,startc,startr - 1, startc, *this));
            }
        }

        if(!picePinned or (pinDirection.first == -1 && pinDirection.second == 1)){
            if(board[startr-1][startc+1] & 0b01000000){
                moves.push_back(Move(startr,startc,startr-1,startc+1,*this));
            }
            if((startr-1 == enPassantPossibleRow) && (startc + 1 == enPassantPossibleCol)){
                moves.push_back(Move(startr, startc, startr-1, startc+1, *this, false, true));
            }
        }

        if(!picePinned or (pinDirection.first == -1 && pinDirection.second == -1)){
            if(board[startr-1][startc-1] & 0b01000000){
                moves.push_back(Move(startr,startc,startr-1,startc-1,*this));
            }
            if((startr-1 == enPassantPossibleRow) && (startc - 1 == enPassantPossibleCol)){
                moves.push_back(Move(startr, startc, startr -1, startc -1, *this, false, true));
            }
        }
    }
    else if((piece & 0b01000000) && startr != 7){
        if(!picePinned or (pinDirection.first == 1 && pinDirection.second == 0)){
            if((startr == 1)and (board[startr+2][startc] == 0b00000000)){
                moves.push_back(Move(startr,startc,startr + 2, startc, *this));
            }
            if(board[startr+1][startc] == 0b00000000){
                moves.push_back(Move(startr,startc,startr + 1, startc, *this));
            }
        }

        if(!picePinned or (pinDirection.first == 1 && pinDirection.second == 0)){
            if(board[startr+1][startc+1] & 0b10000000){
                moves.push_back(Move(startr,startc,startr+1,startc+1,*this));
            }
            if((startr+1 == enPassantPossibleRow) && (startc + 1 == enPassantPossibleCol)){
                moves.push_back(Move(startr, startc, startr+1, startc+1, *this, false, true));
            }
        }
        if(!picePinned or (pinDirection.first == 1 && pinDirection.second == 0)){
            if(board[startr+1][startc-1] & 0b10000000){
                moves.push_back(Move(startr,startc,startr+1,startc-1,*this));
            }
            if((startr+1 == enPassantPossibleRow) && (startc - 1 == enPassantPossibleCol)){
                moves.push_back(Move(startr, startc, startr+1, startc -1, *this, false, true));
            }
        }
    }
}


void ChessEngien::getKnightMove(int startr, int startc, int piece){

    bool picePinned = false;
    pair<int,int> pinDirection;
    for(int i=0; i<pins.size(); i++){
        if(pins[i].startr == startr && pins[i].startc == startc){
            picePinned = true;
            pins.erase(pins.begin()+i);
            break;
        }
    }

    if(!picePinned){
        int direction[8][2] = {{-1,-2},{-2,-1},{1,-2},{2,-1},{1,2},{2,1},{-1,2},{-2,1}};
        int endr, endc;
        if(piece & 0b10000000){
            for(int d = 0; d < 8;d++){
                endr = startr + direction[d][0];
                endc = startc + direction[d][1];
                if((0 <= endr && endr < BOARD_DIMENTION) && (0 <= endc && endc < BOARD_DIMENTION) && !(board[endr][endc] & 0b10000000)){
                    moves.push_back(Move(startr,startc,endr,endc,*this));
                }
            }
        }
        else{
            for(int d = 0; d < 8;d++){
                endr = startr + direction[d][0];
                endc = startc + direction[d][1];
                if((0 <= endr && endr < BOARD_DIMENTION) && (0 <= endc && endc < BOARD_DIMENTION) && !(board[endr][endc] & 0b01000000)){
                    moves.push_back(Move(startr,startc,endr,endc,*this));
                }
            }
        }
    }
}


void ChessEngien::getRookMove(int startr, int startc, int piece){

    bool picePinned = false;
    pair<int,int> pinDirection;
    for(int i=0; i<pins.size(); i++){
        if(pins[i].startr == startr && pins[i].startc == startc){
            picePinned = true;
            pinDirection.first = pins[i].endr;
            pinDirection.second = pins[i].endc;
            if((board[pins[i].endr][pins[i].endc] & 0b00000010)){
                pins.erase(pins.begin()+i);
            }
            break;
        }
    }

    int direction[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int endr, endc;
    if(piece & 0b10000000){
        for(int i = 0; i < 4;i++){
            for(int z =1 ; z < 8; z++){
                endr = startr + (direction[i][0] * z);
                endc = startc + (direction[i][1] * z);
                if((0 <= endr && endr< BOARD_DIMENTION) && (0 <= endc && endc < BOARD_DIMENTION)){
                    if(!picePinned or (pinDirection.first == direction[i][0] && pinDirection.second == direction[i][1]) or 
                        (pinDirection.first == -direction[i][0] && pinDirection.second == -direction[i][1])){
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
                if((0 <= endr && endr < BOARD_DIMENTION) && (0 <= endc && endc < BOARD_DIMENTION)){
                    if(!picePinned or (pinDirection.first == direction[i][0] && pinDirection.second == direction[i][1]) or 
                        (pinDirection.first == -direction[i][0] && pinDirection.second == -direction[i][1])){
                        if(board[endr][endc] == 0b00000000){
                            moves.push_back(Move(startr,startc,endr,endc,*this));
                        }
                        else if(board[endr][endc] & 0b10000000){
                            moves.push_back(Move(startr,startc,endr,endc,*this));
                            break;
                        }
                        else{break;}
                    }
                }
                else{break;}
            }
        }
    }
}


void ChessEngien::getBishoppMove(int startr, int startc, int piece){

    bool picePinned = false;
    pair<int,int> pinDirection;
    for(int i=0; i<pins.size(); i++){
        if(pins[i].startr == startr && pins[i].startc == startc){
            picePinned = true;
            pinDirection.first = pins[i].endr;
            pinDirection.second = pins[i].endc;
            pins.erase(pins.begin()+i);
            break;
        }
    }


    int direction[4][2] = {{-1,1},{-1,-1},{1,1},{1,-1}};
    int endr, endc;
    if(piece & 0b10000000){
        for(int i = 0; i < 4;i++){
            for(int z =1 ; z < 8; z++){
                endr = startr + (direction[i][0] * z);
                endc = startc + (direction[i][1] * z);
                if((0 <= endr && endr< BOARD_DIMENTION) && (0 <= endc && endc  < BOARD_DIMENTION)){
                    if(!picePinned or (pinDirection.first == direction[i][0] && pinDirection.second == direction[i][1]) or 
                        (pinDirection.first == -direction[i][0] && pinDirection.second == -direction[i][1])){
                        if(board[endr][endc] == 0b00000000){
                            moves.push_back(Move(startr,startc,endr,endc,*this));
                        }
                        else if(board[endr][endc] & 0b01000000){
                            moves.push_back(Move(startr,startc,endr,endc,*this));
                            break;
                        }
                        else{break;}
                    }
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
                if((0 <= endr && endr< BOARD_DIMENTION) && (0 <= endc && endc< BOARD_DIMENTION)){
                    if(!picePinned or (pinDirection.first == direction[i][0] && pinDirection.second == direction[i][1]) or 
                        (pinDirection.first == -direction[i][0] && pinDirection.second == -direction[i][1])){
                        if(board[endr][endc] == 0b00000000){
                            moves.push_back(Move(startr,startc,endr,endc,*this));
                        }
                        else if(board[endr][endc] & 0b10000000){
                            moves.push_back(Move(startr,startc,endr,endc,*this));
                            break;
                        }
                        else{break;}
                    }
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
        if((0 <= endr && endr < BOARD_DIMENTION) && (0 <= endc && endc < BOARD_DIMENTION) && !(board[endr][endc] & team)){
            if(!(isUnderAttck(endr,endc))){
                moves.push_back(Move(startr,startc,endr,endc,*this));
            }
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


bool ChessEngien::isUnderAttck(int r, int c){
    int allayColor, enemyColor;
    int endRow, endCol;
    if(whiteToMove){allayColor = 0b10000000; enemyColor = 0b01000000;}
    else{allayColor = 0b01000000; enemyColor = 0b10000000;}

    int directions[8][2] = {{-1,0},{0,-1},{1,0},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}};
    for(int j=0; j<8; j++){
        int d[2];
        d[0] = directions[j][0];
        d[1] = directions[j][1];
        for(int i=1; i<8; i++){
            endRow = r+(d[0] * i);
            endCol = c+(d[1] * i);
            if((0 <= endRow && endRow < 8) && (0 <= endCol && endCol < 8)){
                int endPiece = board[endRow][endCol];
                if(endPiece & allayColor){
                    break;
                }
                else if(endPiece & enemyColor){
                    int pieceType = endPiece - enemyColor;
                    if(((0<=j && j<=3) and (pieceType == 0b00010000)) or
                        ((4 <= j && j <= 7) and (pieceType == 0b00000100)) or
                        ((i == 1 && pieceType == 0b00100000) and ((enemyColor == 0b10000000 && 6 <= j && j <= 7) or (enemyColor == 0b01000000 && 4 <= j && j <= 5)))or
                        (pieceType == 0b00000010) or
                        (i == 1 and pieceType == 0b00000001)){
                        return true;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                break;
            }
        }
    }

    int knightMoves[8][2] = {{-1,-2},{-2,-1},{1,-2},{2,-1},{1,2},{2,1},{-1,2},{-2,1}};
    for(int m=0; m<8; m++){
        endRow = r+knightMoves[m][0];
        endCol = c+knightMoves[m][1];
        if((0<= endRow && endRow <= 7) and (0<=endCol && endCol<=7)){
            int endPiece = board[endRow][endCol];
            if((endPiece & enemyColor)&&(endPiece - enemyColor == 0b00001000)){
                return true;
            }
        }
    }

    return false;
}

void ChessEngien::checkForPinsAndChecks(){

    pins.clear();
    checks.clear();
    inCheck = false;

    int allayColor, enemyColor, startRow, startCol;
    int endRow, endCol;
    vector<moveStorages> possinlePins;

    if(whiteToMove){
        startRow = wKingLocationR;
        startCol = wKingLocationC;
        allayColor = 0b10000000;
        enemyColor = 0b01000000;
    }
    else{
        startRow = bKingLocationR;
        startCol = bKingLocationC;
        allayColor = 0b01000000;
        enemyColor = 0b10000000;
    }

    int directions[8][2] = {{-1,0},{0,-1},{1,0},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}};
    for(int j=0; j<8; j++){
        int d[2];
        d[0] = directions[j][0];
        d[1] = directions[j][1];
        possinlePins.clear();
        for(int i=1; i<8; i++){
            endRow = startRow+(d[0] * i);
            endCol = startCol+(d[1] * i);
            if((0 <= endRow && endRow < 8) && (0 <= endCol && endCol < 8)){
                int endPiece = board[endRow][endCol];
                if((endPiece & allayColor) && (endPiece-allayColor != 0b00000001)){
                    if(possinlePins.empty()){
                        possinlePins.push_back(moveStorages(endRow,endCol,d[0],d[1]));
                    }
                    else{
                        break;
                    }
                }
                else if(endPiece & enemyColor){
                    int pieceType = endPiece - enemyColor;
                    if(((0 <=j && j <= 3) and (pieceType == 0b00010000)) or
                        ((4 <= j && j <= 7) and (pieceType == 0b00000100)) or
                        ((i == 1 && pieceType == 0b00100000) and ((enemyColor == 0b10000000 && 6 <= j && j <= 7) or (enemyColor == 0b01000000 && 4 <= j && j <= 5)))or
                        (pieceType == 0b00000010) or
                        (i == 1 and pieceType == 0b00000001)){
                        if(possinlePins.empty()){
                            inCheck = true;
                            checks.push_back(moveStorages(endRow,endCol,d[0],d[1]));
                            break;
                        }
                        else{
                            pins.push_back(possinlePins[0]);
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                break;
            }
        }
    }

    int knightMoves[8][2] = {{-1,-2},{-2,-1},{1,-2},{2,-1},{1,2},{2,1},{-1,2},{-2,1}};
    for(int m=0; m<8; m++){
        endRow = startRow+knightMoves[m][0];
        endCol = startCol+knightMoves[m][1];
        if((0<= endRow && endRow <= 7) and (0<=endCol && endCol<=7)){
            int endPiece = board[endRow][endCol];
            if((endPiece & enemyColor)&&(endPiece - enemyColor == 0b00001000)){
                inCheck = true;
                checks.push_back(moveStorages(endRow,endCol,knightMoves[m][0],knightMoves[m][1]));
            }
        }
    }
}



