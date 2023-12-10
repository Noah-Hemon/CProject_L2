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

    DisplayList(list);
    DisplaySortedList(list);
     */

    //Part 2

    t_timer _timer_;
    t_d_list * listcomp = createComplexityList(4);
    DisplaySortedList(listcomp);
    startTimer();
    //value search
    int isHere = researchValueClassic(listcomp,3);
    //int isHere = researchValueOptimized(listcomp,3);
    printf("isHere = %d",isHere);
    stopTimer();
    //displayTime();*/


    //Part 3
/*
   calendar * cal = createCalendar();


    entry * joseph = createEntry();
    cal_cell * joseph_cal = createCalCell(joseph);
    insertCellAscendingCal(joseph_cal,cal);

    entry * jeff = createEntry();
    cal_cell * jeff_cal = createCalCell(jeff);
    insertCellAscendingCal(jeff_cal,cal);

    DisplayCalendar(cal);

    entry * cesar = createEntry();
    cal_cell * cesar_cal = createCalCell(cesar);
    insertCellAscendingCal(cesar_cal,cal);

    DisplayCalendar(cal);

    entry * bob = createEntry();
    cal_cell  * bob_cal = createCalCell(bob);
    insertCellAscendingCal(bob_cal,cal);

    printf("\n");
    DisplayCalendar(cal);
*/

/*
    //Console interface
    calendar * cal = createCalendar();
    entry * newEntry;
    cal_cell * newCell;
    int resp = 0;
    int x = 0;
    printf("For this application Yes = 1 and No = 0\n\n");
    printf("What do you want to do ?\n");
    printf("1-Search for a contact\n");
    printf("2-Create a contact\n");
    printf("3-See the time taken to insert a new contact\n");
    printf("4-EXIT\n");

    while(x<1 || x>4){
        scanf("%d",&x);
        if(x<1 || x>4){
            printf("Your answer needs to be one of the prompted ones\nretry:");
        }
    }
    switch(x){
        case 1 :
            printf("What is the last name of your contact ? :\n");
            char name[20];
            scanf("%s",name);
            printf("name : %s",name);
            char key_tab[4];
            GetString(name,key_tab);
            cal_cell * contact = SearchContactOptimized(cal,key_tab);
            printf("works");
            if(contact == NULL){
                printf("Going back to main menu.\n");
                main();
            }
            printf("Your contact : %s was found what do you want to do ?\n",contact->entry->contact->surname);
            printf("1-View appointements\n");
            printf("2-Go back to main menu\n");
            printf("3-EXIT\n");
            scanf("%d",&resp);
            switch(resp){
                        case 1:
                            DisplayAppointements(contact);
                            printf("What do you want to do now ?\n");
                            printf("1-Create an appointement\n");
                            printf("2-Delete an appointement\n");
                            printf("3-Go back to main menu\n");
                            printf("4-EXIT");
                            scanf("%d",&resp);
                            switch(resp){
                                case 1:
                                    while(resp == 1 ) {
                                        createAppointement(contact);
                                        printf("The appointement has been added\n");
                                        printf("Do you want to add another one ?\n");
                                        scanf("%d", &resp);
                                    }
                                    printf("What do you want to do now ?\n");
                                    printf("1-Go back to main menu\n");
                                    printf("2-EXIT\n");
                                    scanf("%d",&resp);
                                    if(resp == 1){
                                        main();
                                    }
                                    else{
                                        return 0;
                                    }
                            }
                        case 2:
                            main();
                        case 3:
                            return 0;
                    }

        case 2 :    newEntry = createEntry(); //for a contact we need an entry
                    newCell = createCalCell(newEntry);
                    insertCellAscendingCal(newCell,cal);
                    printf("The new contact is now in the list.\n");
                    printf("Do you want to create an appointement for this contact ?\n");
                    scanf("%d",&resp);
                    if(resp == 0) { //No
                        printf("What do you want to do ?\n");
                        printf("1-Go back to main menu\n");
                        printf("2-EXIT\n");
                        scanf("%d",&resp);
                        if(resp == 1){
                            main();
                        }
                        else{
                            return 0;
                        }
                    }
                    else{ //Yes
                        while(resp == 1 ) {
                            createAppointement(newEntry);
                            printf("The appointement has been added\n");
                            printf("Do you want to add another one ?\n");
                            scanf("%d", &resp);
                        }
                        printf("What do you want to do now ?\n");
                        printf("1-Go back to main menu\n");
                        printf("2-EXIT\n");
                        scanf("%d",&resp);
                        if(resp == 1){
                            main();
                        }
                        else{
                            return 0;
                        }
                    }

        case 3 :
            printf("Enter a new contact for insertion\n");
            cal_cell * jeff_cal = createCalCell(createEntry());
            startTimer();
            insertCellAscendingCal(jeff_cal,cal);
            stopTimer();
            printf("Time for an optimized insertion :");
            displayTime();
            printf("\nTime for an optimized search :");
            startTimer();
            cal_cell * search = SearchContactOptimized(cal, jeff_cal->entry->key);
            stopTimer();
            displayTime();
            printf("Time for an unoptimized insertion :");
            startTimer();
            printf("\nstart\n");
            cal_cell * joff_cell = createCalCell(createEntry());
            printf("createcell\n");
            insertCellClassic(jeff_cal,cal);
            stopTimer();
            printf("end\n");
            displayTime();
            printf("Time for an unoptimized search :");
            startTimer();
            cal_cell * search2 = SearchContactClassic(cal,jeff_cal->entry->key);
            stopTimer();
            displayTime();
            printf("What do you want to do now ?\n");
            printf("1-Go back to main menu\n");
            printf("2-EXIT\n");
            scanf("%d",&resp);
            if(resp == 1){
                main();
            }
            else{
                return 0;
            }

        case 4 : return 0;
    }
    */
    return 0;
}
