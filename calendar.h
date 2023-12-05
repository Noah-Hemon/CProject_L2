//
// Created by alexg on 27/11/2023.
//

#ifndef PROJL2_CALENDAR_H
#define PROJL2_CALENDAR_H
#include "cell.h"
#include "list.h"


typedef struct contact{
    char* surname;
    char* name;
}contact;

typedef struct appointement{
    struct appointement * next;
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int lenght;
    char* purpose;
}appointement;

typedef struct entry{
    char* key;
    contact * contact;
    appointement* appointementLinkedList ;
}entry;

typedef struct cal_cell{
    struct cal_cell ** levels;
    entry* entry;
    int lvl_max;
}cal_cell;

typedef struct caldendar{
    cal_cell** head;
}calendar;

void getContactInfo(entry* entry);
void InsertAppointement(entry* entry, appointement* app);
void createAppointement(entry* entry);
void DisplayAppointements(entry* entry);
void DeleteAppointement(entry* entry, int val);
cal_cell * createCalCell(entry* ent);
calendar * createCalendar(void);
void replaceLetter(cal_cell * calCell,cal_cell * letter,calendar* cal);
void insertCellAscendingCal(cal_cell * calCell, calendar* cal);


#endif //PROJL2_CALENDAR_H
