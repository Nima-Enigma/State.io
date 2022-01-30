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

void background(SDL_Surface * bg_surface , SDL_Renderer *sdlRenderer){
    for(int i = 0 ; i<1500 ; i+=200){
        for(int j = 0 ; j<800 ; j+=200){
            SDL_Texture* background = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
            SDL_Rect rect = {i , j , 200 , 200};
            SDL_RenderCopy(sdlRenderer , background , NULL , &rect);
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

    regions[0].c_x = rand()%1300;
    regions[0].c_y = rand()%600;
    regions[0].r = 110;
    regions[0].color = 0xffccffff;
    regions[0].existence = 1;
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
        if(regions[a].color == 0xffccffff)regions[a].color = colors[i];
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
            //if(rand()%2 != 0) {
                if (rand() % 2 == 0)regions[reg_head + 1].r = 110;
                else regions[reg_head + 1].r = 90; //}
            //else reg_head --;
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
        filledEllipseColor(sdlRenderer, regions[i].c_x, regions[i].c_y , regions[i].r+10 , regions[i].r-15 , regions[i].color);}
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
void soldiers(TTF_Font * font , region regions[50] , SDL_Renderer *sdlRenderer) {
    int i = 0;
    while (regions[i].c_y != 0) {
        if(regions[i].color != 0xffc0c0c0 && regions[i].existence == 1){
            char num[3];
            int copy = regions[i].soldiers;
            if (copy == 0) {
                num[0] = '0';
            }
            for (int j = num_digit(copy) - 1; copy != 0; j--, copy /= 10) {
                num[j] = (copy % 10 + '0');
            }
            SDL_Rect yo = {regions[i].c_x - 10, regions[i].c_y + 10, 20, 25};
            SDL_Color text_color = {0, 0, 0, 255};
            SDL_Surface *yoo = TTF_RenderText_Solid(font, num, text_color);
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(sdlRenderer, yoo);
            SDL_RenderCopy(sdlRenderer, text_texture, NULL, &yo);}
        i++;
    }
}

void draw_barracks(SDL_Renderer * sdlRenderer,region regions[50], SDL_Surface *surface_tower , SDL_Surface *surface_barracks ){
    int i=0;
    while(regions[i].c_y !=0) {
        if(regions[i].color == 0xffccffff && regions[i].existence == 1){
            SDL_Texture *towers = SDL_CreateTextureFromSurface(sdlRenderer, surface_tower);SDL_Rect rect_b = {regions[i].c_x - 80, regions[i].c_y - 90, 600 / 5, 549 / 5};
            SDL_RenderCopy(sdlRenderer, towers, NULL, &rect_b);
        }
        if(regions[i].color !=0xffccffff && regions[i].color !=0xffc0c0c0 && regions[i].existence == 1) {
            SDL_Texture *barracks = SDL_CreateTextureFromSurface(sdlRenderer, surface_barracks);SDL_Rect rect_b = {regions[i].c_x - 57, regions[i].c_y - 100, 600 / 5, 549 / 5};
            SDL_RenderCopy(sdlRenderer, barracks, NULL, &rect_b);
        }
        i++;
    }
}

int Run(int reg_count , int player_count)
{
    Uint32 colors [10];
    region regions[50];
    region regions_fill[50];
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
    SDL_Surface * bg_surface = IMG_Load("sea2.jpg");
    TTF_Font * font = TTF_OpenFont("fonts/arial.ttf" , 100);
    SDL_Surface *surface_tower = IMG_Load("tower.png");
    SDL_Surface *surface_barracks = IMG_Load("barracks.png");
    while(shallExit == SDL_FALSE) {
        SDL_RenderClear(sdlRenderer);
        background(bg_surface , sdlRenderer);
        draw_shapes(regions , sdlRenderer);
        soldiers(font , regions , sdlRenderer);
        draw_barracks(sdlRenderer,regions,surface_tower,surface_barracks);
        SDL_RenderPresent(sdlRenderer);
        SDL_Event sdlEvent;
        SDL_Delay(2000);
        for(int i=0 ; regions[i].c_y !=0 ; i++){
            if(regions[i].soldiers != 50 && regions[i].color !=0xffccffff && regions[i].color !=0xaac0c0c0)
                regions[i].soldiers++;}
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }
    }
    SDL_DestroyWindow(sdlWindow);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
