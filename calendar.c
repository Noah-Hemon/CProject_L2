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
    printf("here\n");
    if (entry->appointementLinkedList == NULL){
        printf("if\n");
        entry->appointementLinkedList = app;
        return;
    }
    else{
        printf("else\n");
        app->next = entry->appointementLinkedList;
        entry->appointementLinkedList = app;
    }
}

void createAppointement(entry* entry){
    appointement * new = malloc(sizeof(appointement));
    new->next = NULL;
    char temp[20];
    printf("\nWhat is the purpose of the appointement ? : ");
    scanf("%s",temp);
    new->purpose = malloc(sizeof(char)*strlen(temp));
    for(int i=0;i< strlen(temp);i++){
        new->purpose[i] = temp[i];
    }
    printf("\nWhat is the day of the appointement in this format : day/month/year ?\n");
    scanf("%d/%d/%d",&(new->day),&(new->month),&(new->year));
    printf("\nAt what hour and minute will the appointement be ? example : 23:12 \n");
    scanf("%d:%d",&(new->hour),&(new->minute));
    printf("\nWhat is the lenght of the appointement in minutes ? :\n");
    scanf("%d",&(new->lenght));
    InsertAppointement(entry,new); // adds it to the linked list for now in its head;
}

void DisplayAppointements(entry* entry){
    appointement * td = entry->appointementLinkedList; // to display
    if(td == NULL){
        printf("No appointements.\n");
    }
    for(int i=0;td != NULL;i++){
        printf("Appointement number %d : \n",i+1);
        printf("date : %d/%d/%d\n",td->day,td->month,td->year);
        printf("hour : %d:%d\n",td->hour,td->minute);
        printf("length : %d\n",td->lenght);
        printf("purpose : %s\n",td->purpose);
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
    cal_cell * cell = malloc(sizeof(cal_cell));
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


    printf("letter : %c\n",letter->entry->key[0]);

    printf("start tempo\n");
    int init = 0;
    cal_cell *tempo = cal->head[0];
    if(tempo->levels[3]!=NULL && letter!=cal->head[0]){
        while(tempo->levels[3] != letter){
            tempo = tempo->levels[3];
        }
    }
    printf("tempo found : %c\n",tempo->entry->key[0]);

    if(calCell->entry->key[0] == letter->entry->key[0]) {
        letter->lvl_max = letter->lvl_max - 1; // for the display function;
        printf("first\n");
        if(letter->levels[3] == NULL){
            calCell->levels[3] = NULL;
        }
        else if(letter->levels[3]->levels[3] != NULL) {
            calCell->levels[3] = letter->levels[3]->levels[3];
        }
        else{
            calCell->levels[3] = letter->levels[3];
        }
    }
    else if(letter == cal->head[0]){
        printf("letter head\n");
        for(int j=0;j<4;j++){
            calCell->levels[j] = cal->head[j];
            cal->head[j] = calCell;
        }
        return;
    }
    else{
        printf("\nelse\n");
        for(int i=3;i>-1;i--){
            while(init !=0 && tempo->levels[i]!=letter){
                printf("\n enter : %d",i);
                tempo = tempo->levels[i];
            }
            init++;
            calCell->levels[i] = tempo->levels[i];
            tempo->levels[i] = calCell;
        }
        return;
    }
    if(letter != cal->head[0]) {
        for (int j = 0; j < 4; j++) {
            tempo->levels[j] = calCell;
        }
    }
    printf("calCell>key 1 : %c\nletter>key 1: %c",calCell->entry->key[1],letter->entry->key[1]);
    if (calCell->entry->key[1] == letter->entry->key[1]){
        printf("third\n");
        calCell->levels[2] = letter->levels[2];
        if(calCell->entry->key[2] == letter->entry->key[2]){
            printf("fourth\n");
            calCell->levels[1] = letter->levels[1];
        }
        else{
            printf("fith\n");
            calCell->levels[1] = letter;
        }
    }
    else{
        printf("sixth\n");
        calCell->levels[2] = letter;
        if (calCell->entry->key[2] == letter->entry->key[2] && calCell->entry->key[1] == letter->entry->key[1]){
            printf("seven\n");
            calCell->levels[1] = letter->levels[1];
        }
        else{
            printf("eight\n");
            calCell->levels[1] = letter;
        }
    }
    if(letter == calCell) {printf("letter cal equal\n");}
    if(letter == NULL) {printf("letter NULL\n");}
    calCell->levels[0] = letter;
    if(letter == cal->head[0] && letter->entry->key[0] == calCell->entry->key[0]){
        printf("is head\n");
        for(int i=0; i<4;i++){
            cal->head[i] = calCell;
        }
    }
    printf("%c\n",cal->head[0]->levels[0]->entry->key[2]);
    if(letter == calCell) {printf("letter cal equal\n");}
}

void insertCellAscendingCal(cal_cell * calCell, calendar* cal){
    int test = 0;
    if(cal->head[0] == NULL){
        //insert at head
        for(int i=0; i<4;i++){
            cal->head[i] = calCell;
        }
        return;
    }
    else if(cal->head[0]->levels[0] == NULL){
        //insert next to the head with respect to the alphabetical order
        if(cal->head[0]->entry->key[0] > calCell->entry->key[0]){ //looks at the first letter
            // insert calCell at head
            for(int i=0; i<4;i++){
                calCell->levels[i] = cal->head[i];
                cal->head[i] = calCell;
            }
        }
        else if(cal->head[0]->entry->key[0] == calCell->entry->key[0]){
            replaceLetter(calCell,cal->head[0],cal);
        }
        else{
            int count_lvl = 3;
            for (int i = 0; i < 4; i++) {
                if(i!=3){
                    printf("%c----%c\n",cal->head[0]->entry->key[i],calCell->entry->key[i]);
                }
                if (i == 3 || test != 0||cal->head[0]->entry->key[i] < calCell->entry->key[i] ) {
                    cal->head[0]->levels[count_lvl] = calCell;
                    test--;
                }
                count_lvl--;
            }
        }
        return;
    }
    else{
        cal_cell *temp = cal->head[3];
        cal_cell *prev = NULL; // for insertion
        int key_count = 0;
        for(int i = 3; i>-1;i--){ //to check at each level of keys
            printf("i == %d\n",i);
            if(i==0){ // if i==0 we will always put it next independent of the rest
                calCell->levels[i] =prev->levels[i];
                prev->levels[i] = calCell;
                return;
            }
            printf("in while\n");
            //don't forget the test so that it stays in the correct letter
            if(i==3){
                while (calCell->entry->key[key_count] >= temp->entry->key[key_count] &&
                       temp->entry->key[0] < calCell->entry->key[0]) {
                    printf("entered while i==3\n");
                    prev = temp;
                    temp = temp->levels[i];
                    if (temp == NULL) {
                        break;
                    }
                }
            }
            else {
                if(test==0 || temp == NULL&& i==1){
                    temp = prev;
                }
                else {
                    temp = prev->levels[i];
                }
                if(temp == NULL){printf("temp NULL\n");};//temp = prev;}
                while (temp->entry->key[0] < calCell->entry->key[0] || calCell->entry->key[key_count] > temp->entry->key[key_count] ) {
                    printf("entered while\n");
                    prev = temp;
                    temp = temp->levels[i];
                    if (temp == NULL) {
                        //put next
                        //no need to check if prev == NULL because of the second if at the start
                        break;
                    }
                }
            }
            printf("out while\n");

            if(temp == NULL){printf("temp NULL\n");}
            if(prev== NULL){
                printf("prev NULL\n");
                prev = cal->head[0];
            }
            if (i ==3 && calCell->entry->key[0] < prev->entry->key[0]){
                //replace the letter in level 3
                if(temp == cal->head[0]){
                    replaceLetter(calCell,cal->head[0],cal);
                    return;
                }

                printf("replaceLetter function\n");
                replaceLetter(calCell,prev->levels[i],cal);
                printf("replacement done\n");
                return;
            }
            else if(prev->levels[0]->entry->key[0] == calCell->entry->key[0]){
                replaceLetter(calCell,prev->levels[0],cal);
                return;
            }

            if(temp == NULL && calCell->entry->key[0] > prev->entry->key[0]){
                    calCell->levels[i] = prev->levels[i];
                    prev->levels[i] = calCell;
                    test--;
            }

            else if(test !=0 || prev->entry->key[key_count] > calCell->entry->key[key_count]) { // to prevent the case of same letter
                if(i==2 && test!=0 && temp->levels[i]!=NULL){
                    calCell->levels[i] = temp->levels[i];
                    prev->levels[i]->levels[i] = calCell;
                }
                else {
                    calCell->levels[i] = prev->levels[i];
                    prev->levels[i] = calCell;
                }
                test--;
            }

            else{
                if(test == 0 && prev->entry->key[key_count] != calCell->entry->key[key_count]) {
                    calCell->levels[i] = temp;
                    prev->levels[i] = calCell;
                    test--;
                }
            }

            key_count++; //because keys are inverse to i

            DisplayCalendar(cal);
        }
    }
    // asigning lvl max to the cell
}

void DisplayCalendar(calendar* cal){
    cal_cell * temp;
    for(int i=0; i<4;i++){
        temp =cal->head[0];
        printf("level[%d]",i);
        while(temp != NULL){
            printf("[%c]-->",temp->entry->key[0]);
            temp = temp->levels[i];
        }
        printf("NULL\n");
    }
}
void GetString(char * surname,char * key_tab){
    for(int i = 0 ; surname[i] != '\0' ; i++) {
        if ('A' <= surname[i] && surname[i] <= 'Z' ) {
            surname[i] += 32;
        }
    }
    key_tab[0] = surname[0];
    key_tab[1] = surname[1];
    key_tab[2] = surname[2];

}

cal_cell * SearchContactOptimized(calendar * cal,char * key_tab){
    int found;
    int key_count =0;
    cal_cell * temp = cal->head[0];
    cal_cell * prev = NULL;
    for(int i = 3;i>-1;i--){
        found =0;
        while(found ==0){
            if(temp == NULL || temp->entry->key[i] == key_tab[key_count]){
                found++;
            }
            else{
                prev = temp;
                temp = temp->levels[i];
            }
        }
        if(temp == NULL && i == 1){
            printf("Contact not found\n");
            return NULL;
        }
        else if(temp == NULL && i > 1){
            temp = prev->levels[i-1];
        }
        key_count++;
    }
    printf("Contact found\n");
    return temp;
}

cal_cell * SearchContactClassic(calendar * cal,char * key_tab){
    cal_cell *temp = cal->head[0];
    while(temp->entry->key[0] != key_tab[0] &&
            temp->entry->key[1] != key_tab[1] &&
            temp->entry->key[2] != key_tab[2]){
        if(temp == NULL){
            printf("Contact not found\n");
            return NULL;
        }
        temp = temp->levels[0];

    }
    printf("Contact found\n");
    return temp;
}

void insertCellClassic(cal_cell * newCell,calendar * cal){
    char* key_tab = newCell->entry->key;
    cal_cell *temp = cal->head[0];
    cal_cell *prev = NULL;
    while(temp->entry->key[0] <= key_tab[0] &&
          temp->entry->key[1] <= key_tab[1] &&
          temp->entry->key[2] <= key_tab[2]){
        prev = temp;
        temp = temp->levels[0];
        if(temp == NULL){
            break;
        }
    }
    //we will only use this function to test at level 0 for a one dimensionned list
    newCell->levels[0] = prev->levels[0];
    prev->levels[0] = newCell;
}