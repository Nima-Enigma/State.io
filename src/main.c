
#include "all.h"
#include "gameplay.h"
#include "menu.h"
//#include "get_config.h"

int main(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    TTF_Init();
    TTF_Font * font = TTF_OpenFont("../fonts/Awake-the-Beauty.ttf" , 500);
    SDL_Window *sdlWindow = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    srand(time(NULL));
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *start = Mix_LoadMUS("../music/menu.mp3");
    Mix_PlayMusic(start, 1);
    SDL_bool shallExit = SDL_FALSE;
    int t=0;
    while(shallExit == SDL_FALSE){
        char name[20] = {0};
        int random_config[2] = {0, 0};
        int a = Run_menu(sdlRenderer, font , &shallExit , name);
        SDL_RenderClear(sdlRenderer);
        if (a == 5) {
            if (p_r(random_config, sdlRenderer, font , &shallExit) == 1) {
                SDL_RenderClear(sdlRenderer);
                if(t%2 == 1)
                    start = Mix_LoadMUS("../music/music2.mp3");
                else
                    start = Mix_LoadMUS("../music/gameplay.mp3");
                if(start != NULL)Mix_PlayMusic(start, -1);
                int x = Run(random_config[0] - 1, random_config[1], sdlRenderer, 5, start , &shallExit);
                add_scores(x , name);
            }
        } else if (a == 1) {
            int b = default_map(sdlRenderer, font , &shallExit);
            if (b != 0) {
                //if(start != NULL)Mix_FreeMusic(start);
                if(t%2 == 1)
                    start = Mix_LoadMUS("../music/music2.mp3");
                else
                    start = Mix_LoadMUS("../music/gameplay.mp3");
                if(start != NULL)Mix_PlayMusic(start, -1);
                int x = Run(3, 1, sdlRenderer, b, start , &shallExit);
                add_scores(x , name);
            }
        }
        else if (a == 10){
            leaderboard(&shallExit , sdlRenderer , font);
        }
        SDL_RenderClear(sdlRenderer);
        t++;
    }
    Mix_FreeMusic(start);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
