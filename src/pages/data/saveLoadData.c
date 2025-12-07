// saveLoadData.c - Save/Load data page
#include <stdio.h>
#include "fileio.h"
#include "ui.h"

#define BOOKS_FILE "data/catalog.txt"
#define MEMBERS_FILE "data/members.txt"

void saveLoadDataPage(void) {
    int choice;
    
    while (1) {
        showTitle();
        printf("Save/Load Data\n");
        printf("--------------\n\n");
        printf("1. Save All Data\n");
        printf("2. Load All Data\n");
        printf("3. Save Books Only\n");
        printf("4. Load Books Only\n");
        printf("5. Save Members Only\n");
        printf("6. Load Members Only\n");
        printf("7. Back\n\n");
        
        choice = getIntInput("Choice: ");
        
        switch (choice) {
            case 1:
                saveBooks(BOOKS_FILE);
                saveMembers(MEMBERS_FILE);
                printf("All data saved.\n");
                pressEnter();
                break;
            case 2:
                loadBooks(BOOKS_FILE);
                loadMembers(MEMBERS_FILE);
                printf("All data loaded.\n");
                pressEnter();
                break;
            case 3:
                saveBooks(BOOKS_FILE);
                pressEnter();
                break;
            case 4:
                loadBooks(BOOKS_FILE);
                printf("Books loaded.\n");
                pressEnter();
                break;
            case 5:
                saveMembers(MEMBERS_FILE);
                pressEnter();
                break;
            case 6:
                loadMembers(MEMBERS_FILE);
                printf("Members loaded.\n");
                pressEnter();
                break;
            case 7:
                return;
            default:
                printf("Invalid option.\n");
                pressEnter();
        }
    }
}
