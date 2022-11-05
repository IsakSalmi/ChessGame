#include <iostream>


#include "../include/game.hpp"


game::game(){
    window = SDL_CreateWindow("chessGame",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);
    rendere = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SQ_size = BOARD_HEIGHT/BOARD_DIMENTION;
}
game::~game(){
    SDL_DestroyRenderer(rendere);
    SDL_DestroyWindow(window);
}

void game::startGame(){
    SDL_Init(SDL_INIT_EVERYTHING);


    if(window == NULL){
        std::cout << "cant create window" << SDL_GetError() << std::endl;
    }


    while(true){
        if(SDL_PollEvent(&windowEvent)){
            if(SDL_QUIT==windowEvent.type){break;}
        }
        drawBoard();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}


void game::drawEverything(){
    drawBoard();
}

void game::drawBoard(){
    SDL_RenderClear(rendere);

    SDL_Rect rect;
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
    SDL_RenderPresent(rendere);
}