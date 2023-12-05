//
// Created by alexg on 2023/10/24.
//

#ifndef PROJL2_CELL_H
#define PROJL2_CELL_H
#include "list.h"

typedef struct s_d_cell{
    int value;
    struct s_d_cell ** levels;
}t_d_cell;

t_d_cell * createCell (int val, int max_level);
void insertCellHeadLevel(t_d_cell* cell, struct s_d_list* list,int level);
void insertCellAscending(t_d_cell* cell, struct s_d_list* list,int level);
void insertCellAscendingList(int level ,t_d_cell* cell,struct s_d_list* list);

#endif //PROJL2_CELL_H
