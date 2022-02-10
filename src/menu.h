//
// Created by nima on 04.02.22.
//

#ifndef STATE_IO_MENU_H
#define STATE_IO_MENU_H

int Run_menu( SDL_Renderer *sdlRenderer , TTF_Font * font , SDL_bool *shallExit , char name[20]);
int default_map(SDL_Renderer * sdlRenderer , TTF_Font * font , SDL_bool *shallExit);
int p_r(int random_config[2] , SDL_Renderer *sdlRenderer , TTF_Font * font , SDL_bool *shallExit) ;
int leaderboard(SDL_bool * shallExit , SDL_Renderer * sdlRenderer , TTF_Font * font);
void add_scores(int winning_team , char name[20]);
void swap1(char **str1_ptr, char **str2_ptr );

#endif //STATE_IO_MENU_H
