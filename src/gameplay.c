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
#include <math.h>
#include <SDL2/SDL_mixer.h>

void background(SDL_Surface * bg_surface , SDL_Renderer *sdlRenderer){
    for(int i = 0 ; i<1500 ; i+=200){
        for(int j = 0 ; j<800 ; j+=200){
            SDL_Texture* background = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
            SDL_Rect rect = {i , j , 200 , 200};
            SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
            SDL_DestroyTexture(background);
        }
    }
}

void initialize(region regions[50], direction directions[6] , region regions_fill[50] , int map [1500][800]){
    directions[0].x = 90 ; directions[0].y = 130;
    directions[1].x = 90 ; directions[1].y = -130;
    directions[2].x = 180 ; directions[2].y = 0;
    directions[3].x = -180 ; directions[3].y = 0;
    directions[4].x = -90 ; directions[4].y = -130;
    directions[5].x = -90 ; directions[5].y = 130;
    regions[0].r_cpy = 110;
    regions[0].c_x = rand()%1300;
    regions[0].c_y = rand()%600;
    regions[0].r = 110;
    regions[0].color = 0xffccffff;
    regions[0].existence = 1;
    regions[0].attack = -1 ;
    regions[0].soldiers = 10 ;
    while(regions[0].c_x<200 || regions[0].c_y<200){
        regions[0].c_x = rand()%1300;
        regions[0].c_y = rand()%600;
    }
    regions_fill[0].c_x = regions[0].c_x;
    regions_fill[0].c_y = regions[0].c_y;
    map[regions[0].c_x][regions[0].c_y] = 1 ;
}

int check_availability(int map[1500][800],region regions[50], direction next , int i){
    if(map[regions[i].c_x + next.x][regions[i].c_y + next.y] == 1)return 0;
    if(regions[i].c_x + next.x > 1300 || regions[i].c_y + next.y > 670 || regions[i].c_x + next.x < 200 || regions[i].c_y + next.y < 120){
        map[regions[i].c_x + next.x][regions[i].c_y + next.y] = 1;
        return 0;
    }
    else {
        map[regions[i].c_x + next.x][regions[i].c_y + next.y] = 1;
        return 1;
    }
}

void colors_init(Uint32 colors[10]){
    colors[0]= 0xff0000cc; colors[1]= 0xff00cc00; colors[2]= 0xffcc0066; colors[3]= 0xffe3cca9; colors[4]= 0xff3fd0f4; colors[5]= 0xff0054d3 ; colors[6]= 0xffd39bc3 ; colors[7]= 0xfff1f0ec ; colors[8]= 0xff9db345 ; colors[9]= 0xffaab0e6 ;
}

void give_colors(region regions [50] ,int reg_count ,int player_count ,int colors[10]){
    for(int i=0 ; i<player_count ; i++){
        int a = rand()%(reg_head);
        if(regions[a].color == 0xffccffff){
            regions[a].color = colors[i];
            regions[a].soldiers = 0;
        }
        else i--;
    }int copy = reg_head;
    while(copy > reg_count){
       int a = rand() % (reg_head);
       if(regions[a].color == 0xffccffff && regions[a].existence == 1){
           if(rand()%5)regions[a].existence =0;
           else regions[a].color = 0xffc0c0c0;
           copy --;
       }
    }
}

void make_map(int map [1500][800] ,region regions[50] , region regions_fill[50], direction directions[6],int head ){
    for(int j=0 ; j<6 ; j++) {
        if(check_availability(map, regions_fill , directions[j] , head)){
            regions[reg_head + 1].c_x = regions_fill[head].c_x + directions[j].x;
            regions[reg_head + 1].c_y = regions_fill[head].c_y + directions[j].y;
            regions_fill[head +1].c_x = regions_fill[head].c_x + directions[j].x;
            regions_fill[head +1].c_y = regions_fill[head].c_y + directions[j].y;
            regions[reg_head + 1].color = 0xffccffff;
            regions[reg_head + 1].existence = 1;
            regions[reg_head + 1].attack = -1 ;
            regions[reg_head + 1].soldiers = 10;
                if (rand() % 2 == 0)regions[reg_head + 1].r = 110;
                else regions[reg_head + 1].r = 90;
            regions[reg_head + 1].r_cpy = regions[reg_head + 1].r;
            reg_head++;
            head++;
            make_map(map , regions , regions_fill , directions , head );
        }
    }
}

void draw_shapes(region regions[50] , SDL_Renderer *sdlRenderer){
    int i=0;
    while(regions[i].c_y !=0)
    {
        if(regions[i].r == 0) {
            i++;
            continue;
        }
        if(regions[i].existence){
        filledEllipseRGBA(sdlRenderer, regions[i].c_x + 2, regions[i].c_y + 2, regions[i].r+14 ,regions[i].r-12 , 0 , 0 , 0 , 255);
        filledEllipseColor(sdlRenderer, regions[i].c_x, regions[i].c_y , regions[i].r+10 , regions[i].r-15 , regions[i].color);
        }
        i++;
    }
}

int num_digit(int num){
    int count = 0;
    while(num != 0) {
        num /= 10;
        count++;
    }
    return count;
}
void nums(TTF_Font * font , region regions[50] , SDL_Renderer *sdlRenderer) {
    int i = 0;
    while (regions[i].c_y != 0) {
        if(regions[i].color != 0xffc0c0c0 && regions[i].existence == 1){
            char num[5];
            sprintf(num ,"%d" , regions[i].soldiers);
            SDL_Rect yo = {regions[i].c_x - 10, regions[i].c_y + 10, 20, 25};
            SDL_Color text_color = {0, 0, 0, 255};
            SDL_Surface *yoo = TTF_RenderText_Solid(font, num, text_color);
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(sdlRenderer, yoo);
            SDL_RenderCopy(sdlRenderer, text_texture, NULL, &yo);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(yoo);
        }
        i++;
    }
}

void draw_barracks(SDL_Renderer * sdlRenderer,region regions[50], SDL_Surface *surface_tower , SDL_Surface *surface_barracks ){
    int i=0;
    while(regions[i].c_y !=0) {
        if(regions[i].color == 0xffccffff && regions[i].existence == 1){
            SDL_Texture *towers = SDL_CreateTextureFromSurface(sdlRenderer, surface_tower);SDL_Rect rect_b = {regions[i].c_x - 100, regions[i].c_y - 80, 1024/7, 748/7};
            SDL_RenderCopy(sdlRenderer, towers, NULL, &rect_b);
            SDL_DestroyTexture(towers);
        }
        if(regions[i].color !=0xffccffff && regions[i].color !=0xffc0c0c0 && regions[i].existence == 1) {
            SDL_Texture *barracks = SDL_CreateTextureFromSurface(sdlRenderer, surface_barracks);SDL_Rect rect_b = {regions[i].c_x - 57, regions[i].c_y - 100, 600 / 5, 549 / 5};
            SDL_RenderCopy(sdlRenderer, barracks, NULL, &rect_b);
            SDL_DestroyTexture(barracks);
        }
        i++;
    }
}

void draw_arrow(SDL_Renderer *sdlRenderer , region regions [50] , SDL_Surface * arrow_sur){
    if(selected != -1){
        SDL_Texture *tex = SDL_CreateTextureFromSurface(sdlRenderer, arrow_sur);
        SDL_Rect rect_b = {regions[selected].c_x - 50, regions[selected].c_y - 190, 100, 100};
        SDL_RenderCopy(sdlRenderer, tex, NULL, &rect_b);
        SDL_DestroyTexture(tex);
    }
}

void attack(soldier army [200]  ,region regions[50] ){
    for(int i=0 ; i<=reg_head ; i++){
        if(regions[i].attack != -1 && regions[i].existence ==1){
            int a = regions[i].soldiers;
            for(int m=0 ; m <a ; m++){
                if(army_head == 200)army_head =0;
                army[army_head].dest_x = regions[regions[i].attack].c_x -30;
                army[army_head].dest_y = regions[regions[i].attack].c_y -30;
                army[army_head].target = regions[i].attack;
                army[army_head].color = regions[i].color;
                army[army_head].x = rand()%100 + regions[i].c_x - 60;
                army[army_head].y = rand()%100 + regions[i].c_y - 60;
                float cos = (regions[regions[i].attack].c_x -30 - army[army_head].x) / sqrt(pow((army[army_head].y - regions[regions[i].attack].c_y) + 30,2)+pow((army[army_head].x - regions[regions[i].attack].c_x ) +30,2));
                float sin = (regions[regions[i].attack].c_y -30 - army[army_head].y ) / sqrt(pow((army[army_head].y - regions[regions[i].attack].c_y) + 30,2)+pow((army[army_head].x - regions[regions[i].attack].c_x ) +30,2));
                army[army_head].v_y = sin* 7;
                army[army_head].v_x = cos* 7;
                army[army_head].existence = 1;
                army_head ++;
            }
            regions[i].soldiers = 0;
            regions[i].attack = -1;
        }
    }
}

void draw_soldiers_and_attack(SDL_Renderer *sdlRenderer ,region regions[50] ,SDL_Surface * sol_sur ,soldier army[200] ,SDL_RendererFlip flip){
    for(int i = 0 ; i<200 ; i++) {
        if(army[i].existence == 0)continue;
        if(army[i].dest_x - 5 < army[i].x && army[i].x < army[i].dest_x + 5 && army[i].dest_y - 5 < army[i].y && army[i].y < army[i].dest_y + 5) {
            army[i].existence = 0;
            if(army[i].color == regions[army[i].target].color)regions[army[i].target].soldiers ++;
            else regions[army[i].target].soldiers --;
            if(regions[army[i].target].soldiers < 0)regions[army[i].target].color = army[i].color;
        }
        army[i].x += army[i].v_x;
        army[i].y += army[i].v_y;
        SDL_Texture *tex = SDL_CreateTextureFromSurface(sdlRenderer, sol_sur);
        SDL_Rect rect_b = {army[i].x, army[i].y, 60, 60};
        if(army[i].v_x < 0)
            SDL_RenderCopy(sdlRenderer, tex, NULL, &rect_b);
        else
            SDL_RenderCopyEx(sdlRenderer, tex, NULL, &rect_b, 0 , 0 , flip);
        SDL_DestroyTexture(tex);
    }
}

int Run(int reg_count , int player_count)
{
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *start = Mix_LoadMUS(".mp3");
    Uint32 colors [10];
    region regions[50];
    region regions_fill[50];
    soldier army[200];
    int map[1500][800]={};
    srand(time(NULL));
    direction directions[6];
    initialize(regions , directions , regions_fill , map);
    colors_init(colors);
    make_map(map , regions , regions_fill , directions , 0 );
    give_colors(regions , reg_count ,player_count , colors);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    TTF_Init();
    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    //Mix_PlayMusic(start,-1);
    SDL_Surface * bg_surface = IMG_Load("sea2.jpg");
    TTF_Font * font = TTF_OpenFont("fonts/arial.ttf" , 100);
    SDL_Surface *surface_tower = IMG_Load("tower.png");
    SDL_Surface *surface_barracks = IMG_Load("barracks.png");
    SDL_Surface *arrow_sur = IMG_Load("arrow.png");
    SDL_Surface *sol_sur = IMG_Load("soldier.png");
    while(shallExit == SDL_FALSE) {
        attack( army,regions );
        SDL_RenderClear(sdlRenderer);
        background(bg_surface , sdlRenderer);
        draw_shapes(regions , sdlRenderer);
        draw_soldiers_and_attack(sdlRenderer ,regions ,sol_sur , army , flip);
        nums(font , regions , sdlRenderer);
        draw_barracks(sdlRenderer,regions,surface_tower,surface_barracks);
        draw_arrow(sdlRenderer , regions , arrow_sur);
        SDL_RenderPresent(sdlRenderer);
        SDL_Event sdlEvent;
        SDL_Delay(1000/FPS);
        for(int i=0 ; regions[i].c_y !=0 ; i++){
            if(regions[i].soldiers < 50.3 && regions[i].color !=0xffccffff && regions[i].color !=0xaac0c0c0)
                regions[i].soldiers+=1;}
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEMOTION:
                    for(int i=0 ; i <= reg_head ; i++) {
                        if (regions[i].existence == 0)continue;
                        if (pow(sdlEvent.motion.x - regions[i].c_x, 2) + pow(sdlEvent.motion.y - regions[i].c_y, 2) <
                            pow(regions[i].r_cpy - 30, 2)){
                            regions[i].r = regions[i].r_cpy + 10;
                        } else
                            regions[i].r = regions[i].r_cpy;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for(int i=0 ;i <= reg_head ; i++) {
                        if (pow(sdlEvent.motion.x - regions[i].c_x, 2) + pow(sdlEvent.motion.y - regions[i].c_y, 2) <
                            pow(regions[i].r_cpy - 30, 2) && regions[i].color != 0xffccffff && regions[i].color != 0xffc0c0c0)
                            selected = i;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    for(int i=0 ;i <= reg_head ; i++) {
                        if (pow(sdlEvent.motion.x - regions[i].c_x, 2) + pow(sdlEvent.motion.y - regions[i].c_y, 2) <
                            pow(regions[i].r_cpy - 30, 2)  && regions[i].color != 0xffc0c0c0 && selected != -1 && regions[selected].color != regions[i].color) {
                            regions[selected].attack = i;
                        }
                    }
                    break;
            }
        }
    }
    SDL_DestroyWindow(sdlWindow);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
