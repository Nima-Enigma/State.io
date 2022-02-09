//
// Created by nima on 07.02.22.
//
#include "all.h"
#include "menu.h"

void create_tex(SDL_Rect names_r[7],SDL_Texture * names_tex[7],char names[40][20],int scores[7] ,SDL_Renderer * sdlRenderer,TTF_Font * font){
    for(int i=0;i<7;i++){
        char num[10];
        if(names[i][0] != 0){
        sprintf( num,"_____%d" , scores[i]);
        strcat(names[i],num);}
        SDL_Color b = {0,0,0,255};
        SDL_Surface * a = TTF_RenderText_Solid(font, names[i] , b);
        names_tex[i] = SDL_CreateTextureFromSurface(sdlRenderer,a);
        names_r[i].x = 120;
        names_r[i].y = 30 + 80*(i+1);
        names_r[i].w = strlen(names[i])*20;
        names_r[i].h = 50;
        SDL_FreeSurface(a);
    }
}

int leaderboard(SDL_bool * shallExit , SDL_Renderer * sdlRenderer , TTF_Font * font){
    char names[40][20] = {0} ;
    int scores[40] = {0} ;
    FILE * leaderboard = fopen("src/leaderboard.txt" , "r+");
    int m=0;
    int a;
    for(int i=0 ;; i++){
        char a = getc(leaderboard);
        if(a == EOF)break;
        else if(a == '\n'){
            m++;
            i=-1;
        }
        else if(a == '_'){
            fscanf(leaderboard , "%d" , scores + m);
        }
        else names[m][i] = a;
    }
    SDL_Texture * names_tex[7];
    SDL_Rect names_r[7];
    create_tex(names_r , names_tex , names , scores , sdlRenderer , font);
    SDL_Surface * bg_surface = IMG_Load("leaderboard2.jpg");
    SDL_Texture* background = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
    SDL_FreeSurface(bg_surface);
    SDL_Rect rect = {0 , 0 , 1500 , 800};
    SDL_Rect lb = {100 , 30, 320, 60};
    SDL_Color lb_color = {0, 0, 0, 255};
    SDL_Surface *lb_sur = TTF_RenderText_Solid(font, "Leaderboard", lb_color);
    SDL_Texture *lb_tx = SDL_CreateTextureFromSurface(sdlRenderer,lb_sur);
    SDL_Rect menu = {550 , 30, 300, 70};
    SDL_Color menu_color = {0, 0, 0, 255};
    SDL_Surface * menu_sur = TTF_RenderText_Solid(font, "Back to menu", menu_color);
    SDL_Texture * menu_tx = SDL_CreateTextureFromSurface(sdlRenderer, menu_sur);
    SDL_FreeSurface(menu_sur);
    while (!*shallExit) {
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL  , &rect);
        for(int i=0;i<7;i++){
            SDL_RenderCopy(sdlRenderer,names_tex[i],NULL,&names_r[i]);
        }
        SDL_RenderCopy(sdlRenderer ,lb_tx , NULL , &lb);
        SDL_RenderCopy(sdlRenderer ,menu_tx , NULL , &menu);
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    *shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEMOTION:
                    if(sdlEvent.motion.x > 550 && sdlEvent.motion.x < 850 && sdlEvent.motion.y > 30 && sdlEvent.motion.y < 100){
                        menu.w =340;
                        menu.h =85;
                        menu.x = 520;
                    }
                    else {
                        menu.w = 300;
                        menu.h = 70;
                        menu.x = 550;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(sdlEvent.motion.x > 550 && sdlEvent.motion.x < 850 && sdlEvent.motion.y > 30 && sdlEvent.motion.y < 100){
                        return 1;
                    }
            }
        }
    }
    return 0 ;
}