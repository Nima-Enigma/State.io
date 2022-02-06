//
// Created by nima on 04.02.22.
//

#include "all.h"

int p_r(int random_config[2] , SDL_Window *sdlWindow , SDL_Renderer *sdlRenderer , TTF_Font * font) {
    SDL_bool shallExit = SDL_FALSE;
    int flag =0 ;
    char pc[4]={0};
    char rc[4]={0};
    int pc_head = 0;
    SDL_Surface * bg_surface = IMG_Load("bg2.png");
    SDL_Texture* background = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
    SDL_Rect pc_r = {1190 , 150, 40 , 60};
    SDL_Color pc_color = {102, 0, 0, 255};
    SDL_Surface * pc_sur;
    SDL_Texture * pc_tx ;
    SDL_Rect rect = {0 , 0 , 1500 , 800};
    SDL_Rect state_r = {100 , 150, 700 , 60};
    SDL_Color state_color = {102, 0, 0, 255};
    SDL_Surface * state_sur = TTF_RenderText_Solid(font, "Enter number of regions (Max is 20) :", state_color);
    SDL_Texture * state_tx = SDL_CreateTextureFromSurface(sdlRenderer, state_sur);
    SDL_Rect p_r = {100 , 350, 700 , 60};
    SDL_Color p_color = {102, 0, 0, 255};
    SDL_Surface * p_sur = TTF_RenderText_Solid(font, "Enter number of players (Max is 10) :", p_color);
    SDL_Texture * p_tx = SDL_CreateTextureFromSurface(sdlRenderer, p_sur);
    SDL_Rect rc_r = {1190 , 350, 40 , 60};
    SDL_Color rc_color = {102, 0, 0, 255};
    SDL_Surface * rc_sur;
    SDL_Texture * rc_tx ;
    while (shallExit == SDL_FALSE) {
        pc_sur = TTF_RenderText_Solid(font , pc , pc_color);
        pc_tx = SDL_CreateTextureFromSurface(sdlRenderer, pc_sur);
        rc_sur = TTF_RenderText_Solid(font , rc , rc_color);
        rc_tx = SDL_CreateTextureFromSurface(sdlRenderer, rc_sur);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer , pc_tx , NULL , &pc_r);
        SDL_RenderCopy(sdlRenderer , rc_tx , NULL , &rc_r);
        SDL_RenderCopy(sdlRenderer , p_tx , NULL , &p_r);
        SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state_r);
        SDL_RenderPresent(sdlRenderer);
        SDL_DestroyTexture(pc_tx);
        SDL_FreeSurface(pc_sur);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_KEYDOWN:
                    if(sdlEvent.key.keysym.sym  == SDLK_BACKSPACE) {
                        if (flag == 0) {
                            if (pc_head != 0) {
                                pc[pc_head - 1] = 0;
                                pc_head--;
                                pc_r.w = 20 * pc_head;
                                pc_r.x += 8;
                            }
                        }
                        else{
                            if (pc_head != 0) {
                                rc[pc_head - 1] = 0;
                                pc_head--;
                                rc_r.w = 20 * pc_head;
                                rc_r.x += 8;
                            }
                        }
                    }
                    else if(sdlEvent.key.keysym.sym  == SDLK_RETURN) {
                        if(flag == 0) {
                            flag = 1;
                            pc_head = 0;
                        }
                        else{
                            for(int i=0 ; pc[i]!= 0 ; i++) {
                                random_config[0] *= 10;
                                random_config[0] += pc[i]-'0';
                            }
                            for(int i=0 ; rc[i]!= 0 ; i++) {
                                random_config[1] *= 10;
                                random_config[1] += rc[i]-'0';
                            }
                            return 1;
                        }
                    }
                    else {
                        if (flag == 0) {
                            pc[pc_head] = sdlEvent.key.keysym.sym;
                            pc_head++;
                            pc_r.w = 20 * pc_head;
                            pc_r.x -= 8;
                        }
                        else{
                            rc[pc_head] = sdlEvent.key.keysym.sym;
                            pc_head++;
                            rc_r.w = 20 * pc_head;
                            rc_r.x -= 8;
                        }
                    }
                    break;
            }
        }
    }return 0;
}