//
// Created by nima on 30.01.22.
//

#include"all.h"
#include "gameplay.h"


int reg_head = 0;
int army_head = 0;
int selected = -1;
int spell_head = 0;
on_spells on_spell[10];

void background(SDL_Texture * background , SDL_Renderer *sdlRenderer){
    for(int i = 0 ; i<1500 ; i+=150){
        for(int j = 0 ; j<800 ; j+=150){
            SDL_Rect rect = {i , j , 150 , 150};
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
    regions[0].r_cpy = 110;
    regions[0].c_x = rand()%1300;
    regions[0].c_y = rand()%600;
    regions[0].r = 110;
    regions[0].color = 0xff8cB4d2;
    regions[0].existence = 1;
    regions[0].attack = -1 ;
    regions[0].soldiers = 10 ;
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
    colors[0]= 0xff0000cc; colors[1]= 0xff0d8c22; colors[2]= 0xffcc0066; colors[3]= 0xffe3cca9; colors[4]= 0xff3fd0f4; colors[5]= 0xff0054d3 ; colors[6]= 0xffd39bc3 ; colors[7]= 0xfff1f0ec ; colors[8]= 0xff9db345 ; colors[9]= 0xffaab0e6 ;
}

void give_colors(region regions [50] ,int reg_count ,int player_count , Uint32 colors[10] ,int random_config){
    if(random_config != 9) {
        for (int i = 0; i < player_count; i++) {
            int a;
            if(random_config == 5)a = rand() % (reg_head + 1);
            else a = rand() % (reg_head);
            if (regions[a].color == 0xff8cB4d2) {
                regions[a].color = colors[i];
                regions[a].soldiers = 0;
            } else i--;
        }
        int copy = reg_head;
        while (copy > reg_count) {
            int a;
            if(random_config == 5)a = rand() % (reg_head + 1);
            else a = rand() % (reg_head);
            if (regions[a].color == 0xff8cB4d2 && regions[a].existence == 1) {
                if (rand() % 5)regions[a].existence = 0;
                else regions[a].color = 0xffc0c0c0;
                copy--;
            }
        }
    }
    else{
        regions[0].color = colors[1];
        regions[0].soldiers = 0;
        for(int i=1;i<12;i++){
            regions[i].color = colors[0];
            regions[i].soldiers = 0;
        }
        for(int i=12;i<=reg_head;i++)regions[i].existence=0;
    }
}

void make_map(int map [1500][800] ,region regions[50] , region regions_fill[50], direction directions[6],int head ){
    for(int j=0 ; j<6 ; j++) {
        if(check_availability(map, regions_fill , directions[j] , head)){
            regions[reg_head + 1].c_x = regions_fill[head].c_x + directions[j].x;
            regions[reg_head + 1].c_y = regions_fill[head].c_y + directions[j].y;
            regions_fill[head +1].c_x = regions_fill[head].c_x + directions[j].x;
            regions_fill[head +1].c_y = regions_fill[head].c_y + directions[j].y;
            regions[reg_head + 1].color = 0xff8cB4d2;
            regions[reg_head + 1].existence = 1;
            regions[reg_head + 1].attack = -1 ;
            regions[reg_head + 1].soldiers = 20;
                if (rand() % 2 == 0)regions[reg_head + 1].r = 110;
                else regions[reg_head + 1].r = 90;
            regions[reg_head + 1].r_cpy = regions[reg_head + 1].r;
            reg_head++;
            head++;
            make_map(map , regions , regions_fill , directions , head );
        }
    }
}

void draw_shapes(region regions[50] , SDL_Renderer *sdlRenderer){
    int i=0;
    while(regions[i].c_y !=0) {
        if(regions[i].r == 0) {
            i++;
            continue;
        }
        if(regions[i].existence){
        filledEllipseRGBA(sdlRenderer, regions[i].c_x + 2, regions[i].c_y + 2, regions[i].r+14 ,regions[i].r-12 , 0 , 0 , 0 , 255);
        filledEllipseColor(sdlRenderer, regions[i].c_x, regions[i].c_y , regions[i].r+10 , regions[i].r-15 , regions[i].color);
        }
        i++;
    }
}

void nums(TTF_Font * font , region regions[50] , SDL_Renderer *sdlRenderer) {
    int i = 0;
    while (regions[i].c_y != 0) {
        if(regions[i].color != 0xffc0c0c0 && regions[i].existence == 1){
            char num[5];
            sprintf(num ,"%d" , regions[i].soldiers);
            SDL_Rect yo = {regions[i].c_x - 10, regions[i].c_y + 10, 20, 25};
            SDL_Color text_color = {0, 0, 0, 255};
            SDL_Surface *yoo = TTF_RenderText_Solid(font, num, text_color);
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(sdlRenderer, yoo);
            SDL_RenderCopy(sdlRenderer, text_texture, NULL, &yo);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(yoo);
        }
        i++;
    }
}

void create_sol_tex( SDL_Renderer *sdlRenderer ,SDL_Surface * sol_sur[10],SDL_Texture * sol_tex[10]){
    sol_sur[0] = IMG_Load("../pics/soldier1.png");
    sol_sur[1] = IMG_Load("../pics/soldier2.png");
    sol_sur[2] = IMG_Load("../pics/soldier3.png");
    sol_sur[3] = IMG_Load("../pics/soldier4.png");
    sol_sur[4] = IMG_Load("../pics/soldier5.png");
    sol_sur[5] = IMG_Load("../pics/soldier6.png");
    sol_sur[6] = IMG_Load("../pics/soldier7.png");
    sol_sur[7] = IMG_Load("../pics/soldier8.png");
    sol_sur[8] = IMG_Load("../pics/soldier9.png");
    sol_sur[9] = IMG_Load("../pics/soldier10.png");
    for(int i=0;i<10;i++){
        sol_tex[i] = SDL_CreateTextureFromSurface(sdlRenderer,sol_sur[i]);
        SDL_FreeSurface(sol_sur[i]);
    }
}

void create_spells_tex(SDL_Renderer *sdlRenderer ,SDL_Surface * spell_sur[10],SDL_Texture * spell_tex[10]){
    spell_sur[0] = IMG_Load("../pics/speed.png");
    spell_sur[1] = IMG_Load("../pics/power.png");
    spell_sur[2] = IMG_Load("../pics/reverse.png");
    spell_sur[3] = IMG_Load("../pics/productivity.png");
    for(int i=0;i<4;i++){
        spell_tex[i] = SDL_CreateTextureFromSurface(sdlRenderer,spell_sur[i]);
        SDL_FreeSurface(spell_sur[i]);
    }
}

void draw_barracks(SDL_Renderer * sdlRenderer,region regions[50], SDL_Texture *barracks , SDL_Texture *towers ,SDL_Texture *ruins_tex , Uint32 colors[10] ,int player_count , SDL_RendererFlip flip){
    int i=0;
    while(regions[i].c_y !=0) {
        if(regions[i].color == 0xff8cB4d2 && regions[i].existence == 1){
            SDL_Rect rect_b = {regions[i].c_x - 100, regions[i].c_y - 80, 1024/7, 748/7};
            SDL_RenderCopy(sdlRenderer, towers, NULL, &rect_b);
        }
        else if(regions[i].color == 0xffc0c0c0){
            SDL_Rect rect_b = {regions[i].c_x -60, regions[i].c_y -30 , 3700 /30, 2400 /30};
            SDL_RenderCopy(sdlRenderer, ruins_tex, NULL, &rect_b);
        }
        else if(regions[i].color !=0xff8cB4d2 && regions[i].color !=0xffc0c0c0 && regions[i].existence == 1) {
            SDL_Rect rect_b = {regions[i].c_x - 57, regions[i].c_y - 100, 600 / 5, 549 / 5};
            int n=0;
            for(; n<player_count ;n++) {
                if (regions[i].color == colors[n]) break;
            }
            if (on_spell[n].type == 3) {
                rect_b.h = 549 / 4;
                rect_b.w = 600 / 4;
                rect_b.x = regions[i].c_x - 600 / 8;
                rect_b.y = regions[i].c_y - 549 / 4;
            }
            if (on_spell[n].type ==2)
                SDL_RenderCopyEx(sdlRenderer, barracks, NULL, &rect_b, 0, 0, flip);
            else
                SDL_RenderCopy(sdlRenderer, barracks, NULL, &rect_b);

        }
        i++;
    }
}

void draw_arrow(SDL_Renderer *sdlRenderer , region regions [50] , SDL_Surface * arrow_sur){
    if(selected != -1){
        SDL_Texture *tex = SDL_CreateTextureFromSurface(sdlRenderer, arrow_sur);
        SDL_Rect rect_b = {regions[selected].c_x - 50, regions[selected].c_y - 190, 100, 100};
        SDL_RenderCopy(sdlRenderer, tex, NULL, &rect_b);
        SDL_DestroyTexture(tex);
    }
}

void attack(soldier army [700]  , region regions[50] , Uint32 colors[10], int player_count){
    for(int i=0 ; i<=reg_head ; i++){
        if(regions[i].attack != -1 && regions[i].existence == 1){
            double mytime = 0 ;
            struct timeval start;
            gettimeofday(&start , NULL);
            int a = regions[i].soldiers;
            for(int m=0 ; m <a ; m++){
                if(army_head == 700)army_head =0;
                int a = rand()%100;
                int b = rand()%100;
                army[army_head].dest_x =regions[regions[i].attack].c_x -30 ;
                army[army_head].dest_y =regions[regions[i].attack].c_y -30 ;
                army[army_head].target = regions[i].attack;
                int l=0;
                for( ; l<player_count ;l++){
                    if(regions[i].color == colors[l])
                        break;
                }army[army_head].team = l;
                army[army_head].color = regions[i].color;
                army[army_head].x = a + regions[i].c_x - 80;
                army[army_head].y = b + regions[i].c_y - 80;
                army[army_head].delay = start.tv_sec + mytime;
                float cos = (regions[regions[i].attack].c_x - 30 - army[army_head].x) / sqrt(pow((army[army_head].y - regions[regions[i].attack].c_y +30)  ,2)+pow((army[army_head].x - regions[regions[i].attack].c_x ) +30 ,2));
                float sin = (regions[regions[i].attack].c_y - 30 - army[army_head].y) / sqrt(pow((army[army_head].y - regions[regions[i].attack].c_y) +30 ,2)+pow((army[army_head].x - regions[regions[i].attack].c_x ) + 30 ,2));
                army[army_head].v_y = sin* 3;
                army[army_head].v_x = cos* 3;
                army[army_head].existence = 1;
                army_head ++;
                mytime += 0.2;
            }
            regions[i].soldiers = 0;
            regions[i].attack = -1;
        }
    }
}

int ready(soldier guy){
    struct timeval now;
    gettimeofday(&now , NULL);
    if(now.tv_sec > guy.delay)return 1;
    else return 0;
}

void draw_soldiers_and_attack(SDL_Renderer *sdlRenderer ,region regions[50] , SDL_Texture * sol_tex[10] ,soldier army[700] ,SDL_RendererFlip flip , Uint32 colors[10] , int player_count){
    for(int i = 0 ; i<700 ; i++) {
        if (army[i].existence == 0)continue;
        if (ready(army[i])) {
            for (int j = i + 1; j < 700; j++) {
                if (army[i].color != army[j].color && army[i].x - army[j].x > -10 && army[i].x - army[j].x < 10 &&
                    army[i].y - army[j].y > -10 && army[i].y - army[j].y < 10 && army[j].existence != 0) {
                    int temp = army[i].existence;
                    army[i].existence -= army[j].existence;
                    army[j].existence -= temp;
                    if(army[j].existence == -1)army[j].existence = 0;
                    if(army[i].existence == -1)army[i].existence = 0;
                    break;
                }
            }
            if (army[i].existence == 0)continue;
            if (army[i].dest_x - 5 < army[i].x && army[i].x < army[i].dest_x + 5 && army[i].dest_y - 5 < army[i].y &&
                army[i].y < army[i].dest_y + 5) {
                if (army[i].color == regions[army[i].target].color)
                    regions[army[i].target].soldiers += army[i].existence ;
                else {
                    int n=0;
                    for( ; n<player_count; n++){
                        if(regions[army[i].target].color == colors[n])
                            break;
                    }
                    if(on_spell[n].type == 2)
                        regions[army[i].target].soldiers += army[i].existence ;
                    else
                        regions[army[i].target].soldiers -= army[i].existence ;
                }
                army[i].existence = 0;
                if (regions[army[i].target].soldiers < 1)regions[army[i].target].color = army[i].color;
            }
            army[i].x += army[i].v_x;
            army[i].y += army[i].v_y;
            SDL_Rect rect_b = {army[i].x, army[i].y, 80, 80};
            if (army[i].existence == 2) {
                rect_b.w = 110;
                rect_b.h = 110;
            }
            if (army[i].v_x < 0)
                SDL_RenderCopy(sdlRenderer, sol_tex[army[i].team], NULL, &rect_b);
            else
                SDL_RenderCopyEx(sdlRenderer, sol_tex[army[i].team], NULL, &rect_b, 0, 0, flip);
        }
    }
}

void call_AI(region regions[50] , struct timeval game_start , int player_count) {
    struct timeval now;
    gettimeofday(&now, NULL);
    if(player_count > 3) {
        for (int j = 0; j <= reg_head; j++) {
            int distance = 1000000000;
            if (regions[j].existence == 1 && regions[j].color != 0xff0000cc && regions[j].color != 0xff8cB4d2 &&
                regions[j].color != 0xffc0c0c0) {
                for (int i = 0; i <= reg_head; i++) {
                    if (now.tv_sec - game_start.tv_sec < 16 && regions[i].existence == 1 &&
                        regions[i].color != 0xffc0c0c0 && i != j) {
                        if (pow((regions[j].c_x - regions[i].c_x), 2) + pow((regions[j].c_y - regions[i].c_y), 2) <=
                            distance && regions[i].color == 0xff8cB4d2 &&
                            regions[j].soldiers >= 20) {
                            distance = pow((regions[j].c_x - regions[i].c_x), 2) +
                                       pow((regions[j].c_y - regions[i].c_y), 2);
                            regions[j].attack = i;
                        }
                    }
                }
                for (int i = 0; i <= reg_head; i++) {
                    if (now.tv_sec - game_start.tv_sec >= 16 && regions[i].existence == 1 &&
                        regions[i].color != 0xffc0c0c0 && i != j) {
                        if (pow((regions[j].c_x - regions[i].c_x), 2) + pow((regions[j].c_y - regions[i].c_y), 2) <=
                            distance && regions[i].color != regions[j].color) {
                            distance = pow((regions[j].c_x - regions[i].c_x), 2) +
                                       pow((regions[j].c_y - regions[i].c_y), 2);
                            regions[j].attack = i;
                        }
                    }
                }
            }
        }
    }
    else {
        for (int j = 0; j <= reg_head; j++) {
            int distance = 1000000000;
            if (regions[j].existence == 1 && regions[j].color != 0xff0000cc && regions[j].color != 0xff8cB4d2 &&
                regions[j].color != 0xffc0c0c0) {
                for (int i = 0; i <= reg_head; i++) {
                    if (regions[i].existence == 1 && regions[i].color != 0xffc0c0c0 && i != j) {
                        if (pow((regions[j].c_x - regions[i].c_x), 2) + pow((regions[j].c_y - regions[i].c_y), 2) <=
                            distance && regions[i].color != regions[j].color) {
                            distance = pow((regions[j].c_x - regions[i].c_x), 2) +
                                       pow((regions[j].c_y - regions[i].c_y), 2);
                            regions[j].attack = i;
                        }
                    }
                }
                for (int i = 0; i <= reg_head; i++) {
                    if (now.tv_sec - game_start.tv_sec > 5 && regions[i].existence == 1 && regions[i].color != 0xffc0c0c0 && i != j && regions[i].color != regions[j].color) {
                        if (regions[i].soldiers < 5)
                            regions[j].attack = i;
                    }
                }
            }
        }
    }
}

void drop_spell(region regions[50] , Uint32 color , spell spells[15]){
    int a = (rand() % reg_head) + 1;
    while(regions[a].existence == 0  || regions[a].color == 0xffc0c0c0){
        a = (rand()% reg_head) + 1;
    }
    int b = (rand() % reg_head) + 1;
    while(regions[b].existence == 0  || regions[b].color == 0xffc0c0c0 || a==b){
        b = (rand()% reg_head) + 1;
    }
    if(spell_head == 14)spell_head = 0 ;
    if(regions[a].c_x > regions[b].c_x)
    spells[spell_head].x =rand() % (regions[a].c_x - regions[b].c_x) + regions[b].c_x;
    else if(regions[a].c_x < regions[b].c_x) spells[spell_head].x = rand() % (regions[b].c_x - regions[a].c_x) + regions[a].c_x;
    else spells[spell_head].x = regions[a].c_x ;
    if(regions[a].c_y > regions[b].c_y)
        spells[spell_head].y =rand() % (regions[a].c_y - regions[b].c_y) + regions[b].c_y;
    else if(regions[a].c_y < regions[b].c_y)spells[spell_head].y =rand() % (regions[b].c_y - regions[a].c_y) + regions[a].c_y;
    else spells[spell_head].y = regions[a].c_y;
    spells[spell_head].type = rand() % 4;
    spells[spell_head].color = color ;
    spells[spell_head].existance =1 ;
    struct timeval s_t;
    gettimeofday(&s_t , NULL);
    spells[spell_head].cast_time = s_t.tv_sec ;
    spell_head ++;
}

void draw_spell(spell spells[15] , SDL_Renderer * sdlRenderer , SDL_Texture * spell_tex[4]){
    struct timeval now;
    gettimeofday(&now , NULL);
    for(int i=0 ; i<15 ; i++){
        if(spells[i].existance ==1 && now.tv_sec - spells[i].cast_time < 5) {
            aaellipseColor(sdlRenderer, spells[i].x + 2, spells[i].y + 2, 80, 65, 0xff000000);
            filledEllipseColor(sdlRenderer, spells[i].x + 2, spells[i].y + 2, 80, 65, spells[i].color - 0xaa000000);
            SDL_Rect rect = {spells[i].x -30, spells[i].y -20, 60 , 40};
            SDL_RenderCopy(sdlRenderer , spell_tex[spells[i].type] , NULL , &rect);
        }
        else spells[i].existance = 0;
    }
}

void spells_active(soldier army[700],spell spells[15] ,int player_count , int counter , region regions[50] , Uint32 colors[10]) {
    for (int i = 0; i < 700; i++) {
        if (army[i].existence == 0 || on_spell[army[i].team].type != -1)continue;
        for (int j = 0; j < 14; j++) {
            if (spells[j].color != army[i].color)continue;
            if (pow(army[i].x + 3- spells[j].x, 2) + pow(army[i].y + 3 - spells[j].y, 2) < pow(65, 2) && spells[j].existance !=0) {
                on_spell[army[i].team].type = spells[j].type;
                struct timeval cast;
                gettimeofday(&cast,NULL);
                on_spell[army[i].team].cast_time = cast.tv_sec;
            }
        }
    }
    for(int i=0 ; i<player_count ; i++){
        if(on_spell[i].type == -1)continue;
        if(on_spell[i].type == 0){
            for(int j=0 ; j<700 ;j++){
                if(army[j].team == i){
                    if(pow(army[j].v_y ,2) + pow(army[j].v_x , 2) < 20){
                        army[j].v_x *=2;
                        army[j].v_y *=2;
                    }
                }
            }
        }
        if(on_spell[i].type == 3){
            if(counter == 20){
                for(int j=0 ; j<reg_head ; j++){
                    if(regions[j].existence != 0 && regions[j].color == colors[i]) {
                        if(regions[j].soldiers <= 50)
                        regions[j].soldiers++;
                    }
                }
            }
        }
        if(on_spell[i].type == 1){
            if(counter == 20){
                for(int j=0 ;j<700 ;j++){
                    if(army[j].team == i && army[j].existence ==1)
                        army[j].existence =2;
                }
            }
        }
    }
}

void normalize(soldier army[700] , int player_count) {
    struct timeval now;
    gettimeofday(&now, NULL);
    for (int i = 0; i < player_count; i++) {
        if(on_spell[i].type != -1){
            if (now.tv_sec - on_spell[i].cast_time > 5)
                on_spell[i].type = -1;
        }
        if (on_spell[i].type == -1){
            for (int j = 0; j < 700; j++) {
                if (army[j].team == i) {
                    if(army[j].existence == 2)army[j].existence -- ;
                }
                if (army[j].team == i){
                    if(pow(army[j].v_y,2) + pow (army[j].v_x , 2) > 25){
                        army[j].v_x /=2;
                        army[j].v_y /=2;
                    }
                }
            }
        }
    }
}

int win_condition(region regions[50] , Uint32 colors[10] , int player_count){
    int flag = 1;
    for(int i=0 ; i<player_count ;i++){
        flag =1;
        for(int j=0 ; j<=reg_head && flag; j++){
            if(regions[j].color != colors[i] && regions[j].color != 0xff8cB4d2 && regions[j].color != 0xffc0c0c0){
                flag = 0;
            }
        }if(flag)return i;
    }
    return -1;
}

void reinit(soldier army[700] , region regions[50] , region regions_fill[50]){
    region region_mio [1] = {0};
      for(int i=0 ; i<50 ; i++) {
            regions[i] = region_mio[0];
            regions_fill[i] = region_mio[0];
    }
      soldier mio [1]={0};
    for(int i=0 ; i<700 ; i++){
        army[i] = mio[0];
    }
}

int Run(int reg_count , int player_count , SDL_Renderer *sdlRenderer , int random_or_not , Mix_Music *start ,SDL_bool * shallExit)
{
    int c =-1 ;
    reg_head = 0;
    army_head = 0;
    selected = -1;
    spell_head = 0;
    if(random_or_not != 5){
        srand(random_or_not);
        player_count = rand()%10 + 1;
        reg_count = rand()%10 + 10;
    }
    else
        srand(time(NULL));
    if(random_or_not == 9){
        player_count = 2;
        reg_count = 12;
    }
    spell spells[15];
    for(int i=0 ; i<15 ; i++)spells[i].existance =0;
    for(int i=0 ; i<10 ; i++)on_spell[i].type = -1;
    Uint32 colors [10];
    region regions[50];
    region regions_fill[50];
    soldier army[700];
    SDL_Surface * sol_sur[10];
    SDL_Texture * sol_tex[10];
    SDL_Surface * spell_sur[10];
    SDL_Texture * spell_tex[10];
    int counter = 0 ;
    create_sol_tex(sdlRenderer ,sol_sur,sol_tex);
    create_spells_tex(sdlRenderer ,spell_sur,spell_tex);
    int map[1500][800]={};
    direction directions[6];
    initialize(regions , directions , regions_fill , map);
    colors_init(colors);
    make_map(map , regions , regions_fill , directions , 0 );
    give_colors(regions , reg_count ,player_count , colors , random_or_not);
    srand(time(NULL));
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    TTF_Font * font2 = TTF_OpenFont("../fonts/Awake-the-Beauty.ttf" , 100);
    SDL_Surface * bg_surface = IMG_Load("../pics/grass.png");
    SDL_Texture* backg = SDL_CreateTextureFromSurface(sdlRenderer, bg_surface);
    SDL_FreeSurface(bg_surface);
    TTF_Font * font = TTF_OpenFont("../fonts/arial.ttf" , 100);
    SDL_Surface *surface_tower = IMG_Load("../pics/tower.png");
    SDL_Surface *arrow_sur = IMG_Load("../pics/arrow.png");
    SDL_Surface *ruins_sur = IMG_Load("../pics/rock.png");
    SDL_Texture *ruins_tex = SDL_CreateTextureFromSurface(sdlRenderer, ruins_sur);
    SDL_FreeSurface(ruins_sur);
    SDL_Surface *barracks_sur = IMG_Load("../pics/barracks.png");
    SDL_Texture *barracks_tex = SDL_CreateTextureFromSurface(sdlRenderer, barracks_sur);
    SDL_Texture *towers = SDL_CreateTextureFromSurface(sdlRenderer, surface_tower);
    SDL_Rect state_r = {250 , 150, 900 , 170};
    struct timeval game_start;
    gettimeofday(&game_start,NULL);
    while(*shallExit == SDL_FALSE && c==-1) {
        for(int i=0 ; i<player_count ; i++){
            if(rand() % 300 == 5)drop_spell(regions,colors[i],spells);
        }
        normalize(army , player_count);
        call_AI(regions , game_start , player_count);
        attack(army,regions ,colors,player_count);
        spells_active(army,spells,player_count ,counter ,regions,colors);
        SDL_RenderClear(sdlRenderer);
        background(backg , sdlRenderer);
        draw_shapes(regions , sdlRenderer);
        draw_barracks(sdlRenderer,regions,barracks_tex ,towers ,ruins_tex,colors,player_count , flip);
        draw_soldiers_and_attack(sdlRenderer ,regions ,sol_tex , army , flip , colors , player_count);
        nums(font , regions , sdlRenderer);
        draw_spell(spells , sdlRenderer , spell_tex);
        draw_arrow(sdlRenderer , regions , arrow_sur);
        c = win_condition(regions,colors,player_count);
        if(c != -1){
            SDL_Color state_color = {0,0,0,5};
            //if(start != NULL)Mix_FreeMusic(start);
            start = Mix_LoadMUS("../music/victory.mp3");
            if(start != NULL)Mix_PlayMusic(start,1);
            while(state_color.a <239) {
                SDL_Surface *state_sur = TTF_RenderText_Solid(font2, "__Victory__", state_color);
                SDL_Texture *state_tx = SDL_CreateTextureFromSurface(sdlRenderer, state_sur);
                SDL_Surface *state_sur2 = TTF_RenderText_Solid(font2, "__Defeat__", state_color);
                SDL_Texture *state_tx2 = SDL_CreateTextureFromSurface(sdlRenderer, state_sur2);
                SDL_FreeSurface(state_sur);
                SDL_RenderClear(sdlRenderer);
                background(backg , sdlRenderer);
                draw_shapes(regions , sdlRenderer);
                draw_barracks(sdlRenderer,regions,barracks_tex ,towers ,ruins_tex,colors,player_count , flip);
                if(c==0)SDL_RenderCopy(sdlRenderer, state_tx, NULL, &state_r);
                else SDL_RenderCopy(sdlRenderer, state_tx2, NULL, &state_r);
                SDL_DestroyTexture(state_tx);
                SDL_RenderPresent(sdlRenderer);
                SDL_Delay(1000 / FPS);
                state_color.a++ ;
            }
        }
        SDL_RenderPresent(sdlRenderer);
        SDL_Event sdlEvent;
        SDL_Delay(1000/FPS);
        for(int i=0 ; regions[i].c_y !=0 ; i++) {
            if (regions[i].soldiers < 50 && regions[i].color != 0xff8cB4d2 && regions[i].color != 0xaac0c0c0) {
                if (counter == 20) {
                    regions[i].soldiers += 1;
                }
            }
        }
            if (counter == 20)counter=0;
            counter ++;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    *shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEMOTION:
                    for(int i=0 ; i <= reg_head ; i++) {
                        if (regions[i].existence == 0)continue;
                        if (pow(sdlEvent.motion.x - regions[i].c_x, 2) + pow(sdlEvent.motion.y - regions[i].c_y, 2) <
                            pow(regions[i].r_cpy - 30, 2)){
                            regions[i].r = regions[i].r_cpy + 10;
                        } else
                            regions[i].r = regions[i].r_cpy;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for(int i=0 ;i <= reg_head ; i++) {
                        if (regions[i].existence == 1 && regions[i].color == 0xff0000cc && regions[i].color != 0xff8cB4d2 && regions[i].color != 0xffc0c0c0 && pow(sdlEvent.motion.x - regions[i].c_x, 2) + pow(sdlEvent.motion.y - regions[i].c_y, 2) <
                            pow(regions[i].r_cpy - 30, 2))
                            selected = i;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    for(int i=0 ;i <= reg_head ; i++) {
                        if (regions[i].existence==1 && pow(sdlEvent.motion.x - regions[i].c_x, 2) + pow(sdlEvent.motion.y - regions[i].c_y, 2) <
                            pow(regions[i].r_cpy - 30, 2)  && regions[i].color != 0xffc0c0c0 && selected != -1) {
                            if(selected != i)
                            regions[selected].attack = i;
                        }
                    }
                    break;
            }
        }
    }
    SDL_FreeSurface(surface_tower);
    SDL_FreeSurface(barracks_sur);
    SDL_FreeSurface(arrow_sur);
    SDL_DestroyTexture(backg);
    SDL_DestroyTexture(ruins_tex);
    for(int i=0;i<10;i++)SDL_DestroyTexture(sol_tex[i]);
    for(int i=0;i<10;i++)SDL_DestroyTexture(spell_tex[i]);
    SDL_DestroyTexture(towers);
    SDL_DestroyTexture(barracks_tex);
    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    reinit(army,regions,regions_fill);
    return c;
}
