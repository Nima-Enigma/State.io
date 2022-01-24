#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
//#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;
int reg_head = 0;

SDL_bool shallExit = SDL_FALSE;

typedef struct region{
    int soldiers;
    Uint32 color;
    Sint16 c_x;
    Sint16 c_y;
    Sint16 r;
}region;


typedef struct direction{
    int x;
    int y;
}direction;

void initialize(region regions[50], direction directions[6] , region regions_fill[50] , int map [1500][800]){
    directions[0].x = 90 ; directions[0].y = 140;
    directions[1].x = 90 ; directions[1].y = -140;
    directions[2].x = 180 ; directions[2].y = 0;
    directions[3].x = -180 ; directions[3].y = 0;
    directions[4].x = -90 ; directions[4].y = -140;
    directions[5].x = -90 ; directions[5].y = 140;

    regions[0].c_x = rand()%1300;
    regions[0].c_y = rand()%600;
    regions[0].r = 110;
    regions[0].color = 0xffccffff;
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
    if(regions[i].c_x + next.x > 1300 || regions[i].c_y + next.y > 650 || regions[i].c_x + next.x < 200 || regions[i].c_y + next.y < 150){
        map[regions[i].c_x + next.x][regions[i].c_y + next.y] = 1;
        return 0;
    }
    else {
        map[regions[i].c_x + next.x][regions[i].c_y + next.y] = 1;
        return 1;
    }
}

void give_colors(region regions [50]){
    int i=0;
    while(regions[i].c_y !=0){
        if(rand()%5==0)regions[i].color = 0xaac0c0c0;
        i++;
    }
    regions[0].color = 0xff0000cc;
    i = rand()%reg_head;
    while(regions[i].r ==0 || regions[i].color == 0xff0000cc) i = rand()%reg_head;
    regions[i].color = 0xff00cc00;
    while(regions[i].r ==0 || regions[i].color == 0xff0000cc || regions[i].color == 0xff00cc00) i = rand()%reg_head;
    regions[i].color = 0xffcc0066;
}

void make_map(int map [1500][800] ,region regions[50] , region regions_fill[50], direction directions[6],int head ){
    for(int j=0 ; j<6 ; j++) {
        if(check_availability(map, regions_fill , directions[j] , head)){
                regions[reg_head + 1].c_x = regions_fill[head].c_x + directions[j].x;
                regions[reg_head + 1].c_y = regions_fill[head].c_y + directions[j].y;
                regions_fill[head +1].c_x = regions_fill[head].c_x + directions[j].x;
                regions_fill[head +1].c_y = regions_fill[head].c_y + directions[j].y;
                regions[reg_head + 1].color = 0xffccffff;
                if(rand()%3 != 0) {
                if (rand() % 2 == 0)regions[reg_head + 1].r = 110;
                else regions[reg_head + 1].r = 90; }
                else reg_head --;
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
        if(regions[i].color != 0xaac0c0c0)
            filledCircleRGBA(sdlRenderer, regions[i].c_x, regions[i].c_y , regions[i].r+5 , 0 , 0 , 0 , 255);
        else{
            aacircleRGBA(sdlRenderer, regions[i].c_x, regions[i].c_y , regions[i].r , 0 , 0 , 0 , 255);
        }
        filledCircleColor(sdlRenderer, regions[i].c_x, regions[i].c_y , regions[i].r , regions[i].color);
            i++;
        }
    }

int main()
{
    region regions[50];
    region regions_fill[50];
    int map[1500][800]={};
    srand(time(NULL));
    direction directions[6];
    initialize(regions , directions , regions_fill , map);
    make_map(map , regions , regions_fill , directions , 0 );
    give_colors(regions);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    //TTF_Init();
    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_Rect background = {0 , 0 , 1500 , 800};
    int background_w = 1500 , background_h = 800;
    SDL_Texture * Background = NULL;
    Background = IMG_LoadTexture(sdlRenderer , "sea.jpeg");
    SDL_QueryTexture(Background , NULL , NULL , &background_h , &background_w);
    SDL_RenderCopy(sdlRenderer , Background , NULL , &background);
    while(shallExit == SDL_FALSE) {
        //SDL_SetRenderDrawColor(sdlRenderer, 0x99, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        draw_shapes(regions , sdlRenderer);

        SDL_RenderPresent(sdlRenderer);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }
    }
    SDL_DestroyWindow(sdlWindow);
    //TTF_Quit();
    SDL_Quit();
    return 0;
}