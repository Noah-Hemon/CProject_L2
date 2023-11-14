#include <stdlib.h>
#include <stdio.h>
#include "cell.h"


t_d_cell * createCell (int val, int max_level){ //max_level = list.max_level
    t_d_cell *cell = malloc(sizeof(t_d_cell));
    cell->value =val;
    cell->levels = malloc(sizeof(t_d_cell*)*max_level);
    for (int i=0;i<max_level;i++){
        cell->levels[i] = NULL;
    }
    return cell;
}

void insertCellHeadLevel(t_d_cell* cell, t_d_list* list, int level){
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
    if(temp == NULL){
        temp = cell;
        return;
    }
    else {
        t_d_cell *temp_prev;
        while (cell->value > temp->value) {
            temp_prev = temp;
            if (temp->levels[level] != NULL) {
                temp = temp->levels[level];
            } else { break; }
        }
        temp_prev->levels[level] = cell;
        cell->levels[level] = temp;
    }
}

//continuation of previous function
//taking an array in parameter for easier access, may change it if necessary
void insertCellAscendingList(int tab[],t_d_cell* cell,t_d_list* list){
    int length = sizeof(tab)/sizeof(tab[0]); //error because clion stupid
    for(int i=0; i < length ;i++){
        insertCellAscending(cell,list,i);
    }
}


