//
// Created by nima on 30.01.22.
//

#include "all.h"

int Run_menu(SDL_Window *sdlWindow , SDL_Renderer *sdlRenderer , TTF_Font * font){
    SDL_bool shallExit = SDL_FALSE;
    char name [25] = {0};
    int name_head =0;
    SDL_Surface * bg_surface = IMG_Load("menu_bg.jpg");
    SDL_Texture* background = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
    SDL_FreeSurface(bg_surface);
    SDL_Rect rect = {0 , 0 , 1500 , 800};
    SDL_Rect state = {400 , 30, 500, 200};
    SDL_Color state_color = {0, 0, 0, 5};
    SDL_Surface *state_sur;
    SDL_Texture *state_tx;
    SDL_Rect gar = {1000 , 30, 450, 70};
    SDL_Color gar_color = {0, 0, 0, 5};
    SDL_Surface *gar_sur;
    SDL_Texture *gar_tx;
    SDL_Rect dm = {1090 , 150, 300, 70};
    SDL_Color dm_color = {0, 0, 0, 5};
    SDL_Surface *dm_sur;
    SDL_Texture *dm_tx;
    SDL_Rect en = {1000 , 30, 450, 70};
    SDL_Color en_color = {0, 0, 0, 5};
    SDL_Surface *en_sur;
    SDL_Texture *en_tx;
    SDL_Rect name_r = {1190 , 150, 20 , 50};
    SDL_Color name_color = {102, 0, 0, 255};
    SDL_Surface * name_sur;
    SDL_Texture * name_tx;
    while(state_color.a < 250){
        state_sur = TTF_RenderText_Solid(font, "State.io", state_color);
        state_tx = SDL_CreateTextureFromSurface(sdlRenderer, state_sur);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
        SDL_RenderPresent(sdlRenderer);
        state_color.a += 6;
        SDL_FreeSurface(state_sur);
        SDL_DestroyTexture(state_tx);
        SDL_Delay(1000 / FPS);
    }
    state_sur = TTF_RenderText_Solid(font, "State.io", state_color);
    state_tx = SDL_CreateTextureFromSurface(sdlRenderer, state_sur);
    SDL_FreeSurface(state_sur);
    while(en_color.a < 250){
        en_sur = TTF_RenderText_Solid(font, "Enter your name :", en_color);
        en_tx = SDL_CreateTextureFromSurface(sdlRenderer, en_sur);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
        SDL_RenderCopy(sdlRenderer, en_tx, NULL, &en);
        SDL_RenderPresent(sdlRenderer);
        en_color.a += 6;
        SDL_FreeSurface(en_sur);
        SDL_DestroyTexture(en_tx);
        SDL_Delay(1000 / FPS);
    }
    en_sur = TTF_RenderText_Solid(font, "Enter your name :", en_color);
    en_tx = SDL_CreateTextureFromSurface(sdlRenderer, en_sur);
    SDL_FreeSurface(en_sur);
    int flag = 1;
    while(flag && !shallExit) {
        name_sur = TTF_RenderText_Solid(font, name, name_color);
        name_tx = SDL_CreateTextureFromSurface(sdlRenderer, name_sur);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
        SDL_RenderCopy(sdlRenderer, en_tx, NULL, &en);
        SDL_RenderCopy(sdlRenderer, name_tx, NULL, &name_r);
        SDL_RenderPresent(sdlRenderer);
        SDL_FreeSurface(name_sur);
        SDL_DestroyTexture(name_tx);
        SDL_Delay(1000/FPS);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_KEYDOWN:
                    if(sdlEvent.key.keysym.sym  == SDLK_BACKSPACE){
                        if(name_head !=0){
                        name[name_head -1] = 0 ;
                        name_head --;
                        name_r.w = 20 * name_head;
                        name_r.x += 8;}}
                    else if(sdlEvent.key.keysym.sym  == SDLK_RETURN)
                        flag = 0;
                    else {
                        name[name_head] = sdlEvent.key.keysym.sym;
                        name_head ++;
                        name_r.w = 20 * name_head;
                        name_r.x -= 8;}
                    break;
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }
    }
    while(en_color.a > 5 && !shallExit){
        name_sur = TTF_RenderText_Solid(font, name, name_color);
        name_tx = SDL_CreateTextureFromSurface(sdlRenderer, name_sur);
        en_sur = TTF_RenderText_Solid(font, "Enter your name :", en_color);
        en_tx = SDL_CreateTextureFromSurface(sdlRenderer, en_sur);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, name_tx, NULL, &name_r);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
        SDL_RenderCopy(sdlRenderer, en_tx, NULL, &en);
        SDL_RenderPresent(sdlRenderer);
        en_color.a -= 6;
        name_color.a -= 6;
        SDL_FreeSurface(en_sur);
        SDL_DestroyTexture(en_tx);
        SDL_FreeSurface(name_sur);
        SDL_DestroyTexture(name_tx);
        SDL_Delay(1000 / FPS);
    }
    while(gar_color.a < 250 && !shallExit){
        gar_sur = TTF_RenderText_Solid(font, "Generate a random map", gar_color);
        gar_tx = SDL_CreateTextureFromSurface(sdlRenderer, gar_sur);
        dm_sur = TTF_RenderText_Solid(font, "Default maps", dm_color);
        dm_tx = SDL_CreateTextureFromSurface(sdlRenderer, dm_sur);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
        SDL_RenderCopy(sdlRenderer, gar_tx, NULL, &gar);
        SDL_RenderCopy(sdlRenderer, dm_tx, NULL, &dm);
        SDL_RenderPresent(sdlRenderer);
        SDL_FreeSurface(gar_sur);
        SDL_FreeSurface(dm_sur);
        SDL_DestroyTexture(gar_tx);
        SDL_DestroyTexture(dm_tx);
        gar_color.a += 6;
        dm_color.a += 6;
        SDL_Delay(1000 / FPS);
    }
    gar_sur = TTF_RenderText_Solid(font, "Generate a random map", gar_color);
    gar_tx = SDL_CreateTextureFromSurface(sdlRenderer, gar_sur);
    dm_sur = TTF_RenderText_Solid(font, "Default maps", dm_color);
    dm_tx = SDL_CreateTextureFromSurface(sdlRenderer, dm_sur);
    SDL_FreeSurface(gar_sur);
    SDL_FreeSurface(dm_sur);
    while(shallExit == SDL_FALSE) {
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
                        SDL_DestroyTexture(background);
                        SDL_DestroyTexture(state_tx);
                        SDL_DestroyTexture(gar_tx);
                        SDL_DestroyTexture(dm_tx);
                        return 5;}
                    break;
                case SDL_MOUSEMOTION:
                    if(sdlEvent.motion.x > 1000 && sdlEvent.motion.x < 1450 && sdlEvent.motion.y > 30 && sdlEvent.motion.y < 100){
                        gar.w =500;
                        gar.h =80;
                        gar.x = 980;
//                        gar_color.r = 255,gar_color.g =  255,gar_color.b =  255;
                    }
                    else{
                        gar.w =450;
                        gar.h =70;
                        gar.x = 1000;
                        //gar_color.r = 0,gar_color.g =  0,gar_color.b =  0;
                    }
                    if(sdlEvent.motion.x > 1090 && sdlEvent.motion.x < 1390 && sdlEvent.motion.y > 150 && sdlEvent.motion.y < 220){
                        dm.w =340;
                        dm.h =85;
                        dm.x = 1070;
                        //dm_color.r = 255,dm_color.g =  255,dm_color.b =  255;
                    }
                    else{
                        dm.w = 300;
                        dm.h = 70 ;
                        dm.x = 1090;
                        //dm_color.r = 0,dm_color.g =  0,dm_color.b =  0;
                    }
            }
        }
    }
    SDL_DestroyWindow(sdlWindow);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
