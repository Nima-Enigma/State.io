//
// Created by nima on 30.01.22.
//
#ifndef STATE_IO_MAIN_H
#define STATE_IO_MAIN_H

#include <sys/time.h>
#include "SDL2/SDL_mixer.h"

typedef struct region{
    char existence;
    int soldiers;
    Uint32 color;
    Sint16 c_x;
    Sint16 c_y;
    Sint16 r;
    Sint16 r_cpy;
    int attack;
}region;

typedef struct soldier{
    float x;
    float y;
    float v_x;
    float v_y;
    int target;
    int team;
    char existence;
    Uint32 color;
    int dest_x;
    int dest_y;
    double delay;
}soldier;

typedef struct direction{
    int x;
    int y;
}direction;

typedef struct spell{
    int existance;
    int x;
    int y;
    int type;
    int cast_time;
    Uint32 color;
}spell;

typedef struct on_spells{
    int cast_time;
    int type;
}on_spells;


void call_AI(region regions[50]);
void background(SDL_Texture * background , SDL_Renderer *sdlRenderer);
void initialize(region regions[50], direction directions[6] , region regions_fill[50] ,int map [1500][800]);
int check_availability(int map[1500][800],region regions[50], direction next , int i);
void colors_init(Uint32 colors[10]);
void give_colors(region regions [50] ,int reg_count ,int player_count , Uint32 colors[10]);
void make_map(int map [1500][800] ,region regions[50] , region regions_fill[50], direction directions[6],int head );
void draw_shapes(region regions[50] , SDL_Renderer *sdlRenderer);
void nums(TTF_Font * font , region regions[50] , SDL_Renderer *sdlRenderer);
void create_sol_tex(SDL_Renderer *sdlRenderer , SDL_Surface * sol_sur[10],SDL_Texture * sol_tex[10]);
void draw_barracks(SDL_Renderer * sdlRenderer,region regions[50], SDL_Texture *barracks, SDL_Texture *towers, SDL_Texture *ruins_tex ,Uint32 colors[10] ,int player_count , SDL_RendererFlip flip);
void draw_arrow(SDL_Renderer *sdlRenderer , region regions [50] , SDL_Surface * arrow_sur);
void attack(soldier army [500]  ,region regions[50] , Uint32 colors[10], int player_count);
int ready(soldier guy);
void draw_soldiers_and_attack(SDL_Renderer *sdlRenderer ,region regions[50] , SDL_Texture * sol_tex[10] ,soldier army[500] ,SDL_RendererFlip flip , Uint32 colors[10] , int player_count);
int Run(int reg_count , int player_count, SDL_Renderer *sdlRenderer , int random_or_not , Mix_Music *start , SDL_bool *shallExit);

#endif //STATE_IO_MAIN_H
