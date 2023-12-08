#include <stdlib.h>
#include <stdio.h>
#include "cell.h"


t_d_cell * createCell (int val, int max_level){ //max_level = list.max_level

    //printf(" val : %d; Max lvl : %d",val,max_level);
    t_d_cell *cell = NULL;
    cell = (t_d_cell*) malloc(sizeof(t_d_cell));
    if(cell == NULL){printf(" no memory ");}
    cell->value =val;
    cell->levels = malloc(sizeof(t_d_cell*)*max_level);
    for (int i=0;i<max_level;i++){
        cell->levels[i] = NULL;
    }
    return cell;
}

void insertCellHeadLevel(t_d_cell* cell, t_d_list* list,int level){
    if(sizeof(cell->levels)/sizeof(t_d_cell*) > list->max_levels) {
        printf("Maximum number of levels exceeded.");
        return;
    }
    cell->levels[level] = list->head[level];
    list->head[level] = cell;
}

//will be called later in an iteration
void insertCellAscending(t_d_cell* cell, t_d_list* list,int level){

    t_d_cell* temp = list->head[level];
    t_d_cell* prev = NULL;

     //check basic conditions
    if(temp == NULL || temp->value >= cell->value ){
        insertCellHeadLevel(cell,list,level);
        return;
    }
    //as the counter won't enter the while if it is the first value of a list :
    if(temp->levels[level] == NULL){
        prev = temp;
        temp = temp->levels[level];
    }
    else {
        while (temp->levels[level] != NULL && cell->value > temp->levels[level]->value) {
            prev = temp;
            temp = temp->levels[level];
        }
        //stops before calculating a non existing value so we need another round
        prev = temp;
        temp = temp->levels[level];
    }
    prev->levels[level] = cell;
    cell->levels[level] = temp;
}


//continuation of previous function
//taking an array in parameter for easier access, may change it if necessary
void insertCellAscendingList(int level,t_d_cell* cell,t_d_list* list){

    for(int i=0; i <= level ;i++){
        insertCellAscending(cell,list,i);
    }
}


