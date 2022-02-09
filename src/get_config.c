//
// Created by nima on 04.02.22.
//

#include "all.h"

int p_r(int random_config[2] , SDL_Renderer *sdlRenderer , TTF_Font * font , SDL_bool* shallExit) {
    int flag =0 ;
    char pc[4]={0};
    char rc[4]={0};
    int pc_head = 0;
    SDL_Surface * bg_surface = IMG_Load("bg2.png");
    SDL_Texture* background = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
    SDL_FreeSurface(bg_surface);
    SDL_Rect pc_r = {1190 , 150, 40 , 60};
    SDL_Color pc_color = {102, 0, 0, 255};
    SDL_Surface * pc_sur;
    SDL_Texture * pc_tx ;
    SDL_Rect rect = {0 , 0 , 1500 , 800};
    SDL_Rect state_r = {100 , 150, 700 , 60};
    SDL_Color state_color = {102, 0, 0, 255};
    SDL_Surface * state_sur = TTF_RenderText_Solid(font, "Enter number of regions (Max is 20) :", state_color);
    SDL_Texture * state_tx = SDL_CreateTextureFromSurface(sdlRenderer, state_sur);
    SDL_FreeSurface(state_sur);
    SDL_Rect p_r = {100 , 350, 700 , 60};
    SDL_Color p_color = {102, 0, 0, 255};
    SDL_Surface * p_sur = TTF_RenderText_Solid(font, "Enter number of players (Max is 10) :", p_color);
    SDL_Texture * p_tx = SDL_CreateTextureFromSurface(sdlRenderer, p_sur);
    SDL_FreeSurface(p_sur);
    SDL_Rect rc_r = {1190 , 350, 40 , 60};
    SDL_Color rc_color = {102, 0, 0, 255};
    SDL_Surface * rc_sur;
    SDL_Texture * rc_tx ;
    while (*shallExit == SDL_FALSE) {
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
        SDL_DestroyTexture(rc_tx);
        SDL_FreeSurface(rc_sur);
        SDL_Event sdlEvent;
        SDL_Delay(1000/FPS);
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    *shallExit = SDL_TRUE;
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
                            SDL_DestroyTexture(background);
                            SDL_DestroyTexture(state_tx);
                            SDL_DestroyTexture(p_tx);
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


int default_map(SDL_Renderer * sdlRenderer , TTF_Font * font ,SDL_bool *shallExit) {
    SDL_Rect rect = {0 , 0 , 1500 , 800};
    SDL_Surface *bg_surface = IMG_Load("bg2.png");
    SDL_Texture *background = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
    SDL_FreeSurface(bg_surface);
    SDL_Rect p_r = {500 , 100, 500 , 60};
    SDL_Color p_color = {0, 0, 0, 255};
    SDL_Surface * p_sur = TTF_RenderText_Solid(font, "Choose a default map :", p_color);
    SDL_Texture * p_tx = SDL_CreateTextureFromSurface(sdlRenderer, p_sur);
    SDL_FreeSurface(p_sur);
    SDL_Rect rect20 = {200 , 170 , 1500/3 , 800/3};
    SDL_Surface *sur20 = IMG_Load("20.png");
    SDL_Texture *tex20 = SDL_CreateTextureFromSurface(sdlRenderer, sur20);
    SDL_FreeSurface(sur20);
    SDL_Rect rect15 = {750 ,170 , 1500/3 , 800/3};
    SDL_Surface *sur15 = IMG_Load("15.png");
    SDL_Texture *tex15 = SDL_CreateTextureFromSurface(sdlRenderer, sur15);
    SDL_FreeSurface(sur15);
    SDL_Rect rect14 = {200 , 450 , 1500/3 , 800/3};
    SDL_Surface *sur14 = IMG_Load("14.png");
    SDL_Texture *tex14 = SDL_CreateTextureFromSurface(sdlRenderer, sur14);
    SDL_FreeSurface(sur14);
    SDL_Rect rect7 = {750 , 450 , 1500/3 , 800/3};
    SDL_Surface *sur7 = IMG_Load("7.png");
    SDL_Texture *tex7 = SDL_CreateTextureFromSurface(sdlRenderer, sur7);
    SDL_FreeSurface(sur7);
    SDL_Event sdlEvent;
    SDL_Delay(1000 / FPS);
    while (*shallExit == SDL_FALSE) {
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
        SDL_RenderCopy(sdlRenderer, tex20 , NULL, &rect20);
        SDL_RenderCopy(sdlRenderer, tex15 , NULL, &rect15);
        SDL_RenderCopy(sdlRenderer, tex14 , NULL, &rect14);
        SDL_RenderCopy(sdlRenderer, tex7 , NULL, &rect7);
        SDL_RenderCopy(sdlRenderer , p_tx , NULL , &p_r);
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(2000/FPS);
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    *shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (sdlEvent.motion.x > 200 && sdlEvent.motion.x < 700 && sdlEvent.motion.y > 170 &&
                        sdlEvent.motion.y < 170 + 800 / 3) {
                        SDL_DestroyTexture(background);
                        SDL_DestroyTexture(p_tx);
                        SDL_DestroyTexture(tex20);
                        SDL_DestroyTexture(tex14);
                        SDL_DestroyTexture(tex15);
                        SDL_DestroyTexture(tex7);
                        return 20;
                    } else if (sdlEvent.motion.x > 750 && sdlEvent.motion.x < 1250 && sdlEvent.motion.y > 170 &&
                               sdlEvent.motion.y < 170 + 800 / 3) {
                        SDL_DestroyTexture(background);
                        SDL_DestroyTexture(p_tx);
                        SDL_DestroyTexture(tex20);
                        SDL_DestroyTexture(tex14);
                        SDL_DestroyTexture(tex15);
                        SDL_DestroyTexture(tex7);
                        return 15;
                    } else if (sdlEvent.motion.x > 200 && sdlEvent.motion.x < 700 && sdlEvent.motion.y > 450 &&
                               sdlEvent.motion.y < 450 + 800 / 3) {
                        SDL_DestroyTexture(background);
                        SDL_DestroyTexture(p_tx);
                        SDL_DestroyTexture(tex20);
                        SDL_DestroyTexture(tex14);
                        SDL_DestroyTexture(tex15);
                        SDL_DestroyTexture(tex7);
                        return 14;
                    } else if (sdlEvent.motion.x > 750 && sdlEvent.motion.x < 1250 && sdlEvent.motion.y > 450 &&
                               sdlEvent.motion.y < 450 + 800 / 3) {
                        SDL_DestroyTexture(background);
                        SDL_DestroyTexture(p_tx);
                        SDL_DestroyTexture(tex20);
                        SDL_DestroyTexture(tex14);
                        SDL_DestroyTexture(tex15);
                        SDL_DestroyTexture(tex7);
                        return 7;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (sdlEvent.motion.x > 200 && sdlEvent.motion.x < 700 && sdlEvent.motion.y > 170 &&
                        sdlEvent.motion.y < 170 + 800 / 3) {
                        rect20.w = 1650 / 3;
                        rect20.h = 880 / 3;
                        rect20.x = 170;
                        rect20.y = 140;
                    } else {
                        rect20.w = 1500 / 3;
                        rect20.h = 800 / 3;
                        rect20.x = 200;
                        rect20.y = 170;
                    }
                    if (sdlEvent.motion.x > 750 && sdlEvent.motion.x < 1250 && sdlEvent.motion.y > 170 &&
                        sdlEvent.motion.y < 170 + 800 / 3) {
                        rect15.w = 1650 / 3;
                        rect15.h = 880 / 3;
                        rect15.x = 720;
                        rect15.y = 140;
                    } else {
                        rect15.w = 1500 / 3;
                        rect15.h = 800 / 3;
                        rect15.x = 750;
                        rect15.y = 170;
                    }
                    if (sdlEvent.motion.x > 200 && sdlEvent.motion.x < 700 && sdlEvent.motion.y > 450 &&
                        sdlEvent.motion.y < 450 + 800 / 3) {
                        rect14.w = 1650 / 3;
                        rect14.h = 880 / 3;
                        rect14.x = 170;
                        rect14.y = 420;
                    } else {
                        rect14.w = 1500 / 3;
                        rect14.h = 800 / 3;
                        rect14.x = 200;
                        rect14.y = 450;
                    }
                    if (sdlEvent.motion.x > 750 && sdlEvent.motion.x < 1250 && sdlEvent.motion.y > 450 &&
                        sdlEvent.motion.y < 450 + 800 / 3) {
                        rect7.w = 1650 / 3;
                        rect7.h = 880 / 3;
                        rect7.x = 720;
                        rect7.y = 420;
                    } else {
                        rect7.w = 1500 / 3;
                        rect7.h = 800 / 3;
                        rect7.x = 750;
                        rect7.y = 450;
                    }
            }
            }
    }
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(p_tx);
    SDL_DestroyTexture(tex20);
    SDL_DestroyTexture(tex14);
    SDL_DestroyTexture(tex15);
    SDL_DestroyTexture(tex7);
    return 0;
}


