#include <stdio.h>
#include "cell.h"
#include "list.h"

int main() {
    t_d_list * list = CreateEmptyList(3);
    t_d_cell* cell1 = createCell(3,1);
    insertCellHeadLevel(cell1,list, 2);
    t_d_cell* cell2 = createCell(6,2);
    int tab = {0, 1};
    insertCellAscendingList(tab,cell2,list);
    DisplayList(list);
    return 0;
}



































