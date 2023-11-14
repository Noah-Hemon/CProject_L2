//
// Created by alexg on 2023/10/24.
//
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

t_d_list * CreateEmptyList(int max){
    t_d_list * list = malloc(sizeof(t_d_list));
    list->max_levels = max;
    list->head = malloc(sizeof(t_d_cell*)*max);
    for(int i=0;i<max;i++){
        list->head[i] = NULL;
    }
    return list;
}

void DisplayLevel(int level, t_d_list * list){
    printf("\n[list head_%d @-]-->",level);
    t_d_cell * temp = list->head[level];
    while(temp!=NULL){
        printf("[%d|@-]-->",temp->value);
        temp = temp->levels[level];
    }
    printf("NULL");
}

void DisplayList(t_d_list * list){
    for(int i = 0; i<list->max_levels;i++){
        DisplayLevel(i,list);
        printf("\n");
    }
}
