/*
Library Management System
-------------------------
Made by: 
Muhammad As-Adur Rahman Sajid (233014037)

Simple OS Lab Project with:
- FCFS scheduling
- Critical section lock using semaphore
*/

#include <stdio.h>
#include "ui.h"
#include "sync.h"
#include "fileio.h"

// page function declarations
void manageBooksPage(void);
void manageMembersPage(void);
void issueBooksPage(void);
void saveLoadDataPage(void);

int main(void) {
    // initialize semaphore lock
    initLock();
    
    // load existing data
    loadBooks("data/catalog.txt");
    loadMembers("data/members.txt");
    
    int choice;
    
    while (1) {
        showTitle();
        printf("1. Manage Books\n");
        printf("2. Manage Members\n");
        printf("3. Issue Books\n");
        printf("4. Save/Load Data\n");
        printf("5. Exit\n\n");
        
        choice = getIntInput("Choice: ");
        
        switch (choice) {
            case 1:
                manageBooksPage();
                break;
            case 2:
                manageMembersPage();
                break;
            case 3:
                issueBooksPage();
                break;
            case 4:
                saveLoadDataPage();
                break;
            case 5:
                // save before exit
                saveBooks("data/catalog.txt");
                saveMembers("data/members.txt");
                destroyLock();
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid option.\n");
                pressEnter();
        }
    }
}
