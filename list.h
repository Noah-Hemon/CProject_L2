//
// Created by alexg on 2023/10/24.
//

#ifndef PROJL2_LIST_H
#define PROJL2_LIST_H
#include "cell.h"


typedef struct s_d_list
{
    struct s_d_cell ** head;
    int max_levels;
} t_d_list;

t_d_list * CreateEmptyList(int max);
void DisplayLevel(int level, t_d_list * list);
void DisplayList(t_d_list * list);
void DisplaySortedLevel(int level, t_d_list * list);
void DisplaySortedList(t_d_list * list);
int researchValueOptimized(t_d_list* list,int val);
int researchValueClassic(t_d_list* list, int val);
int* createcomplextab(int nbr_lvl,int nbr_cell);
t_d_list * createComplexityList(int nbr_lvl);

#endif //PROJL2_LIST_H
