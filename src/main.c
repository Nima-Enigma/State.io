#include <stdlib.h>
#include <stdio.h>
#include "gameplay.c"
#include "menu.c"
#include <SDL2/SDL_mixer.h>

int main(){
    if(Run_menu())
    Run(6,3);
    return 0;
}
