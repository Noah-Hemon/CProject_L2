//
// Created by alexg on 2023/10/24.
//
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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
    while( temp !=NULL){
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

// arranged numbers  (optional)

void DisplaySortedLevel(int level, t_d_list * list){
    printf("\n[list head_%d @-]--",level);
    t_d_cell * temp = list->head[level];
    t_d_cell * temp0 = list->head[0];
    while( temp !=NULL && temp0 !=NULL){
        if (temp->value == temp0->value){
            printf(">[%d|@-]--",temp->value);
            temp = temp->levels[level];
            temp0 = temp0->levels[0];
        }
        else {

            int x = floor(log10(temp0->value))+1;
            printf("--------");
            for (int i = 0; i < x ; i++) {
                printf("-");
            }
            temp0 = temp0->levels[0];
        }
    }
    while (temp0 != NULL){
        int x = floor(log10(temp0->value))+1;
        printf("--------");
        for (int i = 0; i < x ; i++) {
            printf("-");
        }
        temp0 = temp0->levels[0];
    }
    printf(">NULL");
}

void DisplaySortedList(t_d_list * list){
    for(int i = 0; i<list->max_levels;i++){
        DisplaySortedLevel(i,list);
        printf("\n");
    }
}
//returns 1 if the value is in the list with the test variable
int researchValueOptimized(t_d_list* list,int val){
    int i = (list->max_levels)-1;
    t_d_cell *temp = NULL;
    for(i; i>=0;i--) {
        temp = list->head[i];
        while(temp->levels[i] != NULL && temp->value <val){
            temp = temp->levels[i];
        }
        if(temp->value == val){
            printf("Value found");
            return 1;
        }
    }
    printf("Value not found");
    return 0;
}

int researchValueClassic(t_d_list* list, int val){
    t_d_cell * temp = list->head[0];
    while(temp != NULL && temp->value != val){
        temp = temp->levels[0];
    }
    if(temp == NULL){
        printf("Value not found");
        return 0;
    }
    else{
        printf("Value found");
        return 1;
    }
}



t_d_list * createComplexityList(int nbr_lvl){ //works in debug mode but not on release for reasons unknown

    // we create the levels tab which will have the number of levels to allocate to the cell
    int nbr_cell = pow( 2,nbr_lvl)-1;
    int* levels = calloc(nbr_cell, sizeof(int));

    for (int x=2;x<nbr_cell;x*=2){
        for(int j=0;j<nbr_cell;j++){
            if(j%x == 0 ){
                levels[j]++;
            }
        }
    }
    //printf("Tableau de valeurs :\n");
    //for (int i = 0; i < nbr_cell; i++) {
    //    printf("%d ", levels[i]);
    //}
    //printf("\n");
    //printf("level 0 : %d\n",levels[0]);
        // we now need to make the list
    t_d_list * list = CreateEmptyList(nbr_lvl);
        // start from the last term for better complexity
    for (int m=(nbr_cell); m>0; m--){
        //printf("enter ");
        t_d_cell * input = createCell(m,levels[m]);
        //printf("\n");
        insertCellAscendingList(levels[m],input,list);
    }
    return list;
}