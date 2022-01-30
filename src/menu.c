//
// Created by nima on 30.01.22.
//
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "main.h"
//#include "gameplay.c"

int Run_menu(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    TTF_Init();
    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_Surface * bg_surface = IMG_Load("menu_bg.jpg");
    SDL_Texture* background = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
    SDL_Rect rect = {0 , 0 , 1500 , 800};
    TTF_Font * font = TTF_OpenFont("fonts/Awake-the-Beauty.ttf" , 500);
    SDL_Rect state = {400 , 30, 500, 200};
    SDL_Color state_color = {0, 0, 0, 255};
    SDL_Surface *state_sur = TTF_RenderText_Solid(font, "State.io", state_color);
    SDL_Texture *state_tx = SDL_CreateTextureFromSurface(sdlRenderer, state_sur);
    SDL_Rect gar = {1000 , 30, 450, 70};
    SDL_Color gar_color = {0, 0, 0, 255};
    SDL_Surface *gar_sur = TTF_RenderText_Solid(font, "Generate a random map", gar_color);
    SDL_Texture *gar_tx = SDL_CreateTextureFromSurface(sdlRenderer, gar_sur);
    SDL_Rect dm = {1090 , 150, 300, 70};
    SDL_Color dm_color = {0, 0, 0, 255};
    SDL_Surface *dm_sur = TTF_RenderText_Solid(font, "Default maps", dm_color);
    SDL_Texture *dm_tx = SDL_CreateTextureFromSurface(sdlRenderer, dm_sur);
//    while(state_color.a < 254){
//        state_sur = TTF_RenderText_Solid(font, "State.io", state_color);
//        state_tx = SDL_CreateTextureFromSurface(sdlRenderer, state_sur);
//        SDL_RenderClear(sdlRenderer);
//        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
//        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
//        SDL_RenderPresent(sdlRenderer);
//        state_color.a += 1;
//        SDL_Delay(1000 / FPS);
//    }
//    while(gar_color.a < 200){
//        SDL_Surface *gar_sur = TTF_RenderText_Solid(font, "Generate a random map", gar_color);
//        SDL_Texture *gar_tx = SDL_CreateTextureFromSurface(sdlRenderer, gar_sur);
//        SDL_Surface *dm_sur = TTF_RenderText_Solid(font, "Default maps", dm_color);
//        SDL_Texture *dm_tx = SDL_CreateTextureFromSurface(sdlRenderer, dm_sur);
//        SDL_RenderClear(sdlRenderer);
//        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
//        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
//        SDL_RenderCopy(sdlRenderer, gar_tx, NULL, &gar);
//        SDL_RenderCopy(sdlRenderer, dm_tx, NULL, &dm);
//        SDL_RenderPresent(sdlRenderer);
//        gar_color.a += 1;
//        dm_color.a += 1;
//        SDL_Delay(100 / FPS);
//    }
    while(shallExit == SDL_FALSE) {
        SDL_FreeSurface(gar_sur);
        gar_sur = TTF_RenderText_Solid(font, "Generate a random map", gar_color);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
        SDL_RenderCopy(sdlRenderer, gar_tx, NULL, &gar);
        SDL_RenderCopy(sdlRenderer, dm_tx, NULL, &dm);
        SDL_RenderPresent(sdlRenderer);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(sdlEvent.motion.x > 1000 && sdlEvent.motion.x < 1450 && sdlEvent.motion.y > 30 && sdlEvent.motion.y < 100){
                        SDL_DestroyWindow(sdlWindow);
                        TTF_Quit();
                        SDL_Quit();
                        return 1;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if(sdlEvent.motion.x > 1000 && sdlEvent.motion.x < 1450 && sdlEvent.motion.y > 30 && sdlEvent.motion.y < 100){
                        gar.w =500;
                        gar.h =80;
                        gar.x = 980;
                        gar_color.r = 255,gar_color.g =  255,gar_color.b =  255;
                    }
                    else{
                        gar.w =450;
                        gar.h =70;
                        gar.x = 1000;
                        gar_color.r = 0,gar_color.g =  0,gar_color.b =  0;
                    }
                    if(sdlEvent.motion.x > 1090 && sdlEvent.motion.x < 1390 && sdlEvent.motion.y > 150 && sdlEvent.motion.y < 220){
                        dm.w =340;
                        dm.h =85;
                        dm.x = 1070;
                        dm_color.r = 255,dm_color.g =  255,dm_color.b =  255;
                    }
                    else{
                        dm.w = 300;
                        dm.h = 70 ;
                        dm.x = 1090;
                        dm_color.r = 0,dm_color.g =  0,dm_color.b =  0;
                    }
            }
        }
    }
    SDL_DestroyWindow(sdlWindow);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
