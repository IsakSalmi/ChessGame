#include <iostream>
#include "../include/game.hpp"

game::game(){
    window = SDL_CreateWindow("chessGame",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);
    rendere = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SQ_size = BOARD_HEIGHT/BOARD_DIMENTION;
    run = true;

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


    if(window == NULL){
        std::cout << "cant create window" << SDL_GetError() << std::endl;
    }


    while(run){
        int startLoop = SDL_GetTicks();  //for fps
        while(SDL_PollEvent(&windowEvent)){
            switch(windowEvent.type){
                case SDL_QUIT:
                    run = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(firstClick){
                        int sc = windowEvent.motion.x;
                        int sr = windowEvent.motion.y;

                        startc = sc/SQ_size;
                        startr = sr/SQ_size;

                        firstClick = false;
                    }
                    else if(!firstClick){
                        int ec = windowEvent.motion.x;
                        int er = windowEvent.motion.y;

                        endc = ec/SQ_size;
                        endr = er/SQ_size;

                        
                        chessEngien.makeMove(Move(startr,startc,endr,endc,chessEngien));

                        firstClick = true;
                    }

                default:
                    break;
            }
        }
        drawEverything();

        //for fps
        int delta = SDL_GetTicks() - startLoop;
        if (delta < desiredDelta){
            SDL_Delay(desiredDelta-delta);
        }
    }
}


void game::drawEverything(){
    SDL_RenderClear(rendere);
    drawBoard();
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

void game::drawPieces(){
    for(int r = 0; r < BOARD_DIMENTION; r++){
        for(int c = 0; c < BOARD_DIMENTION; c++){

            rect.h = SQ_size;
            rect.w = SQ_size;
            rect.x = c*SQ_size;
            rect.y = r*SQ_size;

            int square = chessEngien.pieceOnSquare(r,c);
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