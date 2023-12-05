#include <stdio.h>
#include "cell.h"
#include "list.h"
#include "timer.h"
#include "calendar.h"

int main() {
    //Part 1

    /*
    t_d_list * list = CreateEmptyList(3);
    t_d_cell* cell1 = createCell(8,1);
    insertCellAscendingList(0,cell1,list);

    t_d_cell* cell2 = createCell(6,3);
    insertCellAscendingList(1,cell2,list);

    t_d_cell* cell3 = createCell(7,2);
    insertCellAscendingList(1,cell3,list);

    t_d_cell* cell4 = createCell(5,3);
    insertCellAscendingList(2,cell4,list);

    t_d_cell* cell5 = createCell(9,3);
    insertCellAscendingList(2,cell5,list);

    DisplayList(list);
    printf("\n");
    DisplaySortedList(list);

    researchValueClassic(list,7);

    DisplayLevel(1,list);
    */

    //Part 2

    t_timer _timer_;
    t_d_list * listcomp = createComplexityList(20);
    DisplayList(listcomp);

    startTimer();
    researchValueClassic(listcomp,10000);
    stopTimer();
    printf("\n Search time "); displayTime();
    startTimer();
    researchValueOptimized(listcomp,10000);
    stopTimer();
    printf("\n Search time "); displayTime();


    //Part 3



    return 0;
}



