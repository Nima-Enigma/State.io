//
// Created by nima on 30.01.22.
//
#ifndef STATE_IO_MAIN_H
#define STATE_IO_MAIN_H

typedef struct region{
    int existence;
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
    int existence;
    Uint32 color;
    int dest_x;
    int dest_y;
}soldier;

typedef struct direction{
    int x;
    int y;
}direction;

int p_r(int random_config[2] , SDL_Window *sdlWindow , SDL_Renderer *sdlRenderer , TTF_Font * font);
int Run_menu(SDL_Window *sdlWindow , SDL_Renderer *sdlRenderer , TTF_Font * font);
void background(SDL_Surface * bg_surface , SDL_Renderer *sdlRenderer);
void initialize(region regions[50], direction directions[6] , region regions_fill[50] , int map [1500][800]);
int check_availability(int map[1500][800],region regions[50], direction next , int i);
void colors_init(Uint32 colors[10]);
void give_colors(region regions [50] ,int reg_count ,int player_count , Uint32 colors[10]);
void make_map(int map [1500][800] ,region regions[50] , region regions_fill[50], direction directions[6],int head );
void draw_shapes(region regions[50] , SDL_Renderer *sdlRenderer);
void nums(TTF_Font * font , region regions[50] , SDL_Renderer *sdlRenderer);
void draw_barracks(SDL_Renderer * sdlRenderer,region regions[50], SDL_Surface *surface_tower , SDL_Surface *surface_barracks );
void draw_arrow(SDL_Renderer *sdlRenderer , region regions [50] , SDL_Surface * arrow_sur);
void attack(soldier army [300]  ,region regions[50] );
void draw_soldiers_and_attack(SDL_Renderer *sdlRenderer ,region regions[50] , SDL_Surface * sol_sur[10] ,soldier army[300] ,SDL_RendererFlip flip , Uint32 colors[10]);
int Run(int reg_count , int player_count , SDL_Window *sdlWindow , SDL_Renderer *sdlRenderer);

#endif //STATE_IO_MAIN_H
