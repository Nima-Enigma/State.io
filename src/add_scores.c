//
// Created by nima on 08.02.22.
//

#include "all.h"
#include <string.h>

void swap1(char **str1_ptr, char **str2_ptr )
{
    char *temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
}

void add_scores(int winning_team , char name[20]){
    char names[40][15] = {0} ;
    int scores[40] = {0} ;
    FILE * leaderboard = fopen("src/leaderboard.txt" , "r+");
    int m=0;
    for(int i=0 ;; i++){
        char a = getc(leaderboard);
        if(a == EOF)break;
        else if(a == '\n'){
            m++;
            i=-1;
        }
        else if(a == '_'){
            fscanf(leaderboard , "%d" , scores + m);
        }
        else names[m][i] = a;
    }
    int flamg = 0;
    for(int i=0;i<40;i++){
        if(strcmp(name,names[i])==0){
            flamg =1;
            if(winning_team == 0)scores[i]+=30;
            else scores[i] -=5;
            if(scores[i] < 0)scores[i]=0;
        }
    }
    if(flamg == 0) {
        if (m == 39)m = 0;
        scores[m] = 0;
        if (winning_team == 0)scores[m] = 30;
        strcpy(names[m], name);
        m++;
    }
    if(winning_team != 0){
        for(int i=0;i<40;i++) {
            char a[2];
            sprintf(a,"%d",winning_team);
            char b[6]="bot";
            if (strcmp(strcat(b, a), names[i]) == 0) {
                scores[i] += 30;
            }
        }
    }
    for(int i=0 ; i<40 ; i++){
        for(int j=0 ; j<40 ; j++){
            if(scores[i] < scores[j] && j>i){
                int temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
                swap1(&names[j] , &names[i]);
            }
        }
    }
    freopen("src/leaderboard.txt" , "w" , leaderboard);
    for(int i=0 ; i<m ; i++)
    fprintf(leaderboard , "%s_%d\n" , names[i] , scores[i]);
    fclose(leaderboard);
}
