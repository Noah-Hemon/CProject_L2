//
// Created by alexg on 27/11/2023.
//

#include "calendar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//NEED TO IMPLEMENT THOMAS FUNCTION AND NORMALIZATION FOR NAMES : "surname_name"
//NEED TO DO THE INTERFACE IN THE MAIN

void getContactInfo(entry* entry){
     char temp[20];
     printf("\ninput surname: ");
     scanf("%s",temp);
     entry->contact->surname = temp;
     char* array = malloc(3*sizeof(char));
     array[0] = temp[0];
     array[1] = temp[1];
     array[2] = temp[2];
     entry->key = array;
     printf("\ninput name : ");
     scanf("%s",temp);
     entry->contact->name = temp;
}

entry* createEntry(void){
    entry * new = malloc(sizeof(entry*));
    new->contact = malloc(sizeof(contact*));
    new->appointementLinkedList = NULL;
    getContactInfo(new);
    return new;
}

// creation of an appointement
//only works if the name matches the entry else just ask for creation of new contact

void InsertAppointement(entry* entry, appointement* app){
    if (entry->appointementLinkedList == NULL){
        entry->appointementLinkedList = app;
        return;
    }
    else{
        app->next = entry->appointementLinkedList;
        entry->appointementLinkedList = app;
    }
}

void createAppointement(entry* entry){
    appointement * new = malloc(sizeof(appointement));
    char temp[20];
    printf("\nWhat is the purpose of the appointement ? : ");
    gets(temp);
    new->purpose = malloc(sizeof(char)*strlen(temp));
    for(int i=0;i< strlen(temp);i++){
        new->purpose[i] = temp[i];
    }
    printf("\nWhat is the day of the appointement in this format : day/month/year ?\n");
    scanf("%d/%d/%d",&(new->day),&(new->month),&(new->year));
    printf("\nAt what hour and minute will the appointement be ? example : 23:12 ");
    scanf("%d:%d",&(new->hour),&(new->minute));
    printf("\nWhat is the lenght of the appointement in minutes ? : ");
    scanf("%d",&(new->lenght));
    InsertAppointement(entry,new); // adds it to the linked list for now in its head;
}

void DisplayAppointements(entry* entry){
    appointement * td = entry->appointementLinkedList; // to display
    for(int i=0;td->next != NULL;i++){
        printf("Appointement number %d : \n",i+1);
        printf("date : %d/%d/%d\n",td->day,td->month,td->year);
        printf("hour : %d:%d\n",td->hour,td->minute);
        printf("length : %d",td->lenght);
        printf("purpose : %s",td->purpose);
        td = td->next;
    }
}


// ask the number of the appointement to delete
void DeleteAppointement(entry* entry, int val){
    appointement * temp = entry->appointementLinkedList;
    for(int i =0; i<(val-1);i++){
        temp = temp->next;
    }
    temp->next = temp->next->next;
}


/* implement calendar with a new struct based on the cell that will be able to use renewed version of them*/
cal_cell * createCalCell(entry* ent){
    cal_cell * cell = NULL;
    cell->levels = malloc(sizeof(cal_cell*)*4); // always 4 lvls
    for(int i=0; i<4; i++){
        cell->levels[i]=NULL;
    }
    cell->entry = ent;
    cell->lvl_max = 4;
    return cell;
}

calendar * createCalendar(void){
    calendar* cal = malloc(sizeof(calendar));
    cal->head = malloc(sizeof(t_d_cell*)*4);
    for(int i=0;i<4;i++){
        cal->head[i] = NULL;
    }

    return cal;
}

void replaceLetter(cal_cell * calCell,cal_cell * letter,calendar * cal){
    /*
    We want to replace the current level 3 cell (letter) by calCell,
    we need to go through the list again :(

     Might need to review it as the end of the code is a bit rough
     */
    cal_cell *tempo = cal->head[0];
    while(tempo->levels[3] != letter){
        tempo = tempo->levels[3];
    }
    for(int i = 0; i<4; i++){
        tempo->levels[i] = calCell;
    }
    calCell->levels[3] = letter->levels[3];
    letter->lvl_max = letter->lvl_max - 1; // for the display function;
    if (calCell->entry->key[1] == letter->entry->key[1]){
        calCell->levels[2] = letter->levels[2];
        if(calCell->entry->key[2] == letter->entry->key[2]){
            calCell->levels[1] = letter->levels[1];
        }
        else{
            calCell->levels[1] = letter;
        }
    }
    else{
        calCell->levels[2] = letter;
        if (calCell->entry->key[2] == letter->entry->key[2]){
            calCell->levels[1] = letter->levels[1];
        }
        else{
            calCell->levels[1] = letter;
        }
    }
    calCell->levels[0] = letter;


}

void insertCellAscendingCal(cal_cell * calCell, calendar* cal){
    if(cal->head[0] == NULL){
        //insert at head
        for(int i=0; i<4;i++){
            cal->head[i] = calCell;
        }
        return;
    }
    else if(cal->head[0]->levels[0] == NULL){
        //insert next to the head with respect to the alphabetical order
        if(cal->head[0]->entry->key[2] > calCell->entry->key[2]){
            // insert calCell at head
            for(int i=0; i<4;i++){
                calCell->levels[i] = cal->head[i];
                cal->head[i] = calCell;
            }
        }
        else{
            if(calCell->entry->key[1] < cal->head[0]->entry->key[1]){
                replaceLetter(calCell,cal->head[0],cal);
            }
            else {
                for (int i = 3; i > -1; i++) {
                    if (i == 0 || cal->head[0]->entry->key[i - 1] < calCell->entry->key[i - 1]) {
                        cal->head[0]->levels[i] = calCell;
                    }
                }
            }
        }
        return;
    }
    else{
        cal_cell *temp = cal->head[3];
        cal_cell *prev = NULL; // for insertion
        int key_count = 0;

        for(int i = 3; i>-1;i++){ //to check at each level of keys

            if(i==0){ // if i==0 we will always put it next independent of the rest
                calCell->levels[i] = temp;
                prev->levels[i] = calCell;
                return;
            }
            //don't forget the test so that it stays in the correct letter
            while(calCell->entry->key[key_count] > temp->entry->key[key_count] && temp->entry->key[0] <=calCell->entry->key[0]) {
                prev = temp;
                temp = temp->levels[i];
                if(temp == NULL ){
                    //put next
                    //no need to check if prev == NULL because of the second if at the start
                    break;
                }
            }

            if (i ==3 && calCell->entry->key[1] < prev->entry->key[1]){
                //replace the letter in level 3
                replaceLetter(calCell,prev,cal);
            }

            else if(prev->entry->key[i] != calCell->entry->key[i]) { // to prevent the case of same letter
                calCell->levels[i] = temp;
                prev->levels[i] = calCell;
            }

            else{
                calCell->levels[i] = NULL; // just to be sure as it already initiallized at NULL
            }

            key_count++; //because keys are inverse to i
        }
    }
    // asigning lvl max to the cell
}




