//
// Created by nima on 30.01.22.
//

#ifndef STATE_IO_MAIN_H
#define STATE_IO_MAIN_H

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;
int reg_head = 0;
int army_head = 0;

SDL_bool shallExit = SDL_FALSE;
int selected = -1;

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
#endif //STATE_IO_MAIN_H
