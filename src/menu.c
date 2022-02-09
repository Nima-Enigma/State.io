//
// Created by nima on 30.01.22.
//

#include "all.h"

int Run_menu(SDL_Renderer *sdlRenderer , TTF_Font * font ,SDL_bool *shallExit , char name[20]){
    int name_head =0;
    SDL_Surface * bg_surface = IMG_Load("pics/menu_bg.jpg");
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
    SDL_Rect lb_r = {1110 , 270, 250 , 70};
    SDL_Color lb_color = {0, 0, 0, 5};
    SDL_Surface * lb_sur;
    SDL_Texture * lb_tx;
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
    while(flag && !*shallExit) {
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
                    *shallExit = SDL_TRUE;
                    break;
            }
        }
    }
    while(en_color.a > 5 && !*shallExit){
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
    while(gar_color.a < 250 && !*shallExit){
        gar_sur = TTF_RenderText_Solid(font, "Generate a random map", gar_color);
        gar_tx = SDL_CreateTextureFromSurface(sdlRenderer, gar_sur);
        dm_sur = TTF_RenderText_Solid(font, "Default maps", dm_color);
        dm_tx = SDL_CreateTextureFromSurface(sdlRenderer, dm_sur);
        lb_sur = TTF_RenderText_Solid(font, "Leaderboard", lb_color);
        lb_tx = SDL_CreateTextureFromSurface(sdlRenderer, lb_sur);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
        SDL_RenderCopy(sdlRenderer, gar_tx, NULL, &gar);
        SDL_RenderCopy(sdlRenderer, lb_tx, NULL, &lb_r);
        SDL_RenderCopy(sdlRenderer, dm_tx, NULL, &dm);
        SDL_RenderPresent(sdlRenderer);
        SDL_FreeSurface(gar_sur);
        SDL_FreeSurface(dm_sur);
        SDL_DestroyTexture(gar_tx);
        SDL_DestroyTexture(dm_tx);
        SDL_FreeSurface(lb_sur);
        SDL_DestroyTexture(lb_tx);
        gar_color.a += 6;
        dm_color.a += 6;
        lb_color.a += 6;
        SDL_Delay(1000 / FPS);
    }
    lb_sur = TTF_RenderText_Solid(font, "Leaderboard", lb_color);
    lb_tx = SDL_CreateTextureFromSurface(sdlRenderer, lb_sur);
    gar_sur = TTF_RenderText_Solid(font, "Generate a random map", gar_color);
    gar_tx = SDL_CreateTextureFromSurface(sdlRenderer, gar_sur);
    dm_sur = TTF_RenderText_Solid(font, "Default maps", dm_color);
    dm_tx = SDL_CreateTextureFromSurface(sdlRenderer, dm_sur);
    SDL_FreeSurface(gar_sur);
    SDL_FreeSurface(dm_sur);
    SDL_FreeSurface(lb_sur);
    while(*shallExit == SDL_FALSE) {
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, lb_tx, NULL, &lb_r);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state);
        SDL_RenderCopy(sdlRenderer, gar_tx, NULL, &gar);
        SDL_RenderCopy(sdlRenderer, dm_tx, NULL, &dm);
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000/FPS);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    *shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(sdlEvent.motion.x > 1000 && sdlEvent.motion.x < 1450 && sdlEvent.motion.y > 30 && sdlEvent.motion.y < 100){
                        SDL_DestroyTexture(background);
                        SDL_DestroyTexture(state_tx);
                        SDL_DestroyTexture(gar_tx);
                        SDL_DestroyTexture(dm_tx);
                        SDL_DestroyTexture(lb_tx);
                        return 5;}
                    else if(sdlEvent.motion.x > 1090 && sdlEvent.motion.x < 1390 && sdlEvent.motion.y > 150 && sdlEvent.motion.y < 220){
                        SDL_DestroyTexture(background);
                        SDL_DestroyTexture(state_tx);
                        SDL_DestroyTexture(gar_tx);
                        SDL_DestroyTexture(dm_tx);
                        SDL_DestroyTexture(lb_tx);
                        return 1;
                    }
                    if(sdlEvent.motion.x > 1110 && sdlEvent.motion.x < 1360 && sdlEvent.motion.y > 270 && sdlEvent.motion.y < 520){
                        SDL_DestroyTexture(background);
                        SDL_DestroyTexture(state_tx);
                        SDL_DestroyTexture(gar_tx);
                        SDL_DestroyTexture(dm_tx);
                        SDL_DestroyTexture(lb_tx);
                        return 10;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if(sdlEvent.motion.x > 1000 && sdlEvent.motion.x < 1450 && sdlEvent.motion.y > 30 && sdlEvent.motion.y < 100){
                        gar.w =500;
                        gar.h =80;
                        gar.x = 980;
                    }
                    else{
                        gar.w =450;
                        gar.h =70;
                        gar.x = 1000;
                    }
                    if(sdlEvent.motion.x > 1090 && sdlEvent.motion.x < 1390 && sdlEvent.motion.y > 150 && sdlEvent.motion.y < 220){
                        dm.w =340;
                        dm.h =85;
                        dm.x = 1070;
                    }
                    else {
                        dm.w = 300;
                        dm.h = 70;
                        dm.x = 1090;
                    }
                    if(sdlEvent.motion.x > 1110 && sdlEvent.motion.x < 1360 && sdlEvent.motion.y > 270 && sdlEvent.motion.y < 520){
                        lb_r.w = 290;
                        lb_r.h = 85;
                        lb_r.x = 1090;
                    }
                    else{
                        lb_r.w = 250;
                        lb_r.h = 70 ;
                        lb_r.x = 1110;
                    }
            }
        }
    }
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(state_tx);
    SDL_DestroyTexture(gar_tx);
    SDL_DestroyTexture(dm_tx);
    SDL_DestroyTexture(lb_tx);
    return 0;
}
