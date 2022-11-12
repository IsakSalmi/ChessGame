#include <iostream>
#include "../include/game.hpp"

game::game(){
    window = SDL_CreateWindow("chessGame",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);
    rendere = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SQ_size = BOARD_HEIGHT/BOARD_DIMENTION;
    SDL_SetRenderDrawBlendMode(rendere,SDL_BLENDMODE_BLEND);
    run = true;
    chessEngien = new ChessEngien;
    AI = new ChessAI;
    playerOne = PLAYER_ONE;
    playerTow = PLAYER_TWO;

    wK = IMG_LoadTexture(rendere,"../src/images/wK.png");
    wQ = IMG_LoadTexture(rendere,"../src/images/wQ.png");
    wB = IMG_LoadTexture(rendere,"../src/images/wB.png");
    wN = IMG_LoadTexture(rendere,"../src/images/wN.png");
    wR = IMG_LoadTexture(rendere,"../src/images/wR.png");
    wP = IMG_LoadTexture(rendere,"../src/images/wP.png");

    bK = IMG_LoadTexture(rendere,"../src/images/bK.png");
    bQ = IMG_LoadTexture(rendere,"../src/images/bQ.png");
    bB = IMG_LoadTexture(rendere,"../src/images/bB.png");
    bN = IMG_LoadTexture(rendere,"../src/images/bN.png");
    bR = IMG_LoadTexture(rendere,"../src/images/bR.png");
    bP = IMG_LoadTexture(rendere,"../src/images/bP.png");
    
}
game::~game(){

    SDL_DestroyRenderer(rendere);
    SDL_DestroyWindow(window);
    SDL_Quit();

    SDL_DestroyTexture(wK);
    SDL_DestroyTexture(wQ);
    SDL_DestroyTexture(wB);
    SDL_DestroyTexture(wN);
    SDL_DestroyTexture(wR);
    SDL_DestroyTexture(wP);

    SDL_DestroyTexture(bK);
    SDL_DestroyTexture(bQ);
    SDL_DestroyTexture(bB);
    SDL_DestroyTexture(bN);
    SDL_DestroyTexture(bR);
    SDL_DestroyTexture(bP);
}

void game::startGame(){
    SDL_Init(SDL_INIT_EVERYTHING);

    bool firstClick = true;
    bool moveMade = false;
    bool gameOver = false;
    bool humanTurn;
    int selectedSQr, selectedSQc = -1;
    vector<Move> validMoves = chessEngien->getValidMove();

    if(window == NULL){
        std::cout << "cant create window" << SDL_GetError() << std::endl;
    }


    while(run){

        if((chessEngien->whiteToMove and playerOne) or (!(chessEngien->whiteToMove) and playerTow)){humanTurn = true;}
        else{humanTurn = false;}

        int startLoop = SDL_GetTicks();  //for fps
        while(SDL_PollEvent(&windowEvent)){
            switch(windowEvent.type){
                case SDL_QUIT:
                    run = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(!gameOver and humanTurn){
                        if(firstClick){
                                int sc = windowEvent.button.x;
                                int sr = windowEvent.button.y;

                                startc = sc/SQ_size;
                                startr = sr/SQ_size;

                                if((chessEngien->pieceOnSquare(startr,startc)&0b10000000) && chessEngien->whiteToMove){
                                    selectedSQr = startr;
                                    selectedSQc = startc;
                                    firstClick = false;
                                }
                                else if((chessEngien->pieceOnSquare(startr,startc)&0b01000000) && !chessEngien->whiteToMove){
                                    selectedSQr = startr;
                                    selectedSQc = startc;
                                    firstClick = false;
                                }
                            }
                        else if(!firstClick){
                            int ec = windowEvent.button.x;
                            int er = windowEvent.button.y;

                            endc = ec/SQ_size;
                            endr = er/SQ_size;


                            Move newMove = Move(startr,startc,endr,endc,*chessEngien);

                            //diselect the squre;
                            selectedSQc = -1;
                            selectedSQr = -1;

                            for(int i=0; i < validMoves.size();i++){
                                if(newMove == validMoves[i]){
                                    chessEngien->makeMove(validMoves[i]);
                                    moveMade = true;
                                    break;
                                }
                            }

                            firstClick = true;
                        }
                    }

                case SDL_KEYDOWN:
                    if(windowEvent.key.keysym.sym == SDLK_z){
                        chessEngien->undoMove();
                        moveMade = true;
                        gameOver = false;
                    }
                    break;
                default:
                    break;   
            }
        }

        if(!gameOver && !humanTurn){
            Move AIMove = AI->findeBestMove(*chessEngien, validMoves);
            if(AIMove.startr == -1 && AIMove.startc == -1){
                AIMove = AI->findRandomMove(validMoves);
            }
            chessEngien->makeMove(AIMove);
            moveMade = true;
        }

        if(moveMade){
                validMoves.clear(); 
                validMoves = chessEngien->getValidMove();
                moveMade = false;
            }

        if(chessEngien->checkMate && !gameOver){
            gameOver = true;
            if(chessEngien->whiteToMove){
                cout << "black Won by Checkmate!"<< endl;
            }
            else{
                cout << "white won bu Checkmate!" << endl;
            }
        }
        if(chessEngien->staleMate && !gameOver){
            gameOver = true;
            cout << "Draw due to stalemate!" << endl;
        }

        drawEverything(selectedSQr,selectedSQc, validMoves);

        //for fps
        int delta = SDL_GetTicks() - startLoop;
        if (delta < desiredDelta){
            SDL_Delay(desiredDelta-delta);
        }
    }
}


void game::drawEverything(int sqr, int sqc, vector<Move> validMoves){
    SDL_RenderClear(rendere);
    drawBoard();
    highlightSquare(sqr, sqc, validMoves);
    drawPieces();
    SDL_RenderPresent(rendere);
}

void game::drawBoard(){
    rect.h = SQ_size;
    rect.w = SQ_size;
    for(int r = 0; r < BOARD_DIMENTION; r++){
        for(int c = 0; c < BOARD_DIMENTION; c++){
            if((r+c)%2 == 1){ SDL_SetRenderDrawColor(rendere,241,223,197,255); }
            else{SDL_SetRenderDrawColor(rendere,178,135,108,255);}
            rect.x = SQ_size * c;
            rect.y = SQ_size * r;
            SDL_RenderDrawRect(rendere,&rect);
            SDL_RenderFillRect(rendere,&rect);
        }
    }
}


void game::highlightSquare(int sqr, int sqc, vector<Move> validMoves){
    int team;
    if(chessEngien->whiteToMove){team = 0b10000000;}
    else{team = 0b01000000;}

    if(sqr != -1 && sqc != -1){
        if(chessEngien->pieceOnSquare(sqr,sqc)&team){
            rect.h = SQ_size;
            rect.w = SQ_size;
            rect.x = sqc * SQ_size;
            rect.y = sqr * SQ_size;
            SDL_SetRenderDrawColor(rendere,255,0,0,100);
            SDL_RenderDrawRect(rendere,&rect);
            SDL_RenderFillRect(rendere,&rect);
            for(int i=0; i<validMoves.size(); i++){
                if(validMoves[i].startr == sqr && validMoves[i].startc == sqc){
                    if(!(chessEngien->pieceOnSquare(validMoves[i].endr , validMoves[i].endc) & team)){
                        rect.x = validMoves[i].endc * SQ_size;
                        rect.y = validMoves[i].endr * SQ_size;
                        SDL_RenderDrawRect(rendere,&rect);
                        SDL_RenderFillRect(rendere,&rect);
                    }
                }
            }
        }
    }
}


void game::drawPieces(){
    for(int r = 0; r < BOARD_DIMENTION; r++){
        for(int c = 0; c < BOARD_DIMENTION; c++){

            rect.h = SQ_size;
            rect.w = SQ_size;
            rect.x = c*SQ_size;
            rect.y = r*SQ_size;

            int square = chessEngien->pieceOnSquare(r,c);
            if(square & 0b10000000){
                switch (square)
                {
                case 0b10100000:
                    SDL_RenderCopy(rendere, wP, NULL, &rect);
                    break;
                case 0b10010000:
                    SDL_RenderCopy(rendere, wR, NULL, &rect);
                    break;
                case 0b10001000:
                    SDL_RenderCopy(rendere, wN, NULL, &rect);
                    break;
                case 0b10000100:
                    SDL_RenderCopy(rendere, wB, NULL, &rect);
                    break;
                case 0b10000010:
                    SDL_RenderCopy(rendere, wQ, NULL, &rect);
                    break;
                case 0b10000001:
                    SDL_RenderCopy(rendere, wK, NULL, &rect);
                    break;
                default:
                    break;
                }
            }
            else if (square & 0b01000000)
            {
                switch (square)
                {
                case 0b01100000:
                    SDL_RenderCopy(rendere, bP, NULL, &rect);
                    break;
                case 0b01010000:
                    SDL_RenderCopy(rendere, bR, NULL, &rect);
                    break;
                case 0b01001000:
                    SDL_RenderCopy(rendere, bN, NULL, &rect);
                    break;
                case 0b01000100:
                    SDL_RenderCopy(rendere, bB, NULL, &rect);
                    break;
                case 0b01000010:
                    SDL_RenderCopy(rendere, bQ, NULL, &rect);
                    break;
                case 0b01000001:
                    SDL_RenderCopy(rendere, bK, NULL, &rect);
                    break;
                default:
                    break;
                }
            }
        }
    }
}