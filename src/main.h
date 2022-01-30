//
// Created by nima on 30.01.22.
//

#ifndef STATE_IO_MAIN_H
#define STATE_IO_MAIN_H

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;
int reg_head = 0;

SDL_bool shallExit = SDL_FALSE;

typedef struct region{
    int existence;
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
#endif //STATE_IO_MAIN_H
