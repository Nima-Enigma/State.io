
#include "all.h"
#include "structs_and_functions.h"
#include "SDL2/SDL_mixer.h"


int main(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    TTF_Init();
    TTF_Font * font = TTF_OpenFont("fonts/Awake-the-Beauty.ttf" , 500);
    SDL_Window *sdlWindow = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    int random_config [2]= {0 , 0};
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *start = Mix_LoadMUS("menu.mp3");
    Mix_PlayMusic(start,-1);
    if(Run_menu(sdlWindow , sdlRenderer , font) == 5){
        if(p_r(random_config,sdlWindow , sdlRenderer, font) == 1) {
           Mix_FreeMusic(start);
            start = Mix_LoadMUS("gameplay.mp3");
            Mix_PlayMusic(start,-1);
            Run(random_config[0] , random_config[1] , sdlWindow, sdlRenderer);
        }
    }
    SDL_DestroyWindow(sdlWindow);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
