// issueBooks.c - Issue Books menu page
#include <stdio.h>
#include "ui.h"

// forward declarations
void approveRequestsPage(void);
void returnBookPage(void);
void directIssuePage(void);

void issueBooksPage(void) {
    int choice;
    
    while (1) {
        showTitle();
        printf("Issue Books\n");
        printf("-----------\n\n");
        printf("1. Approve Requests\n");
        printf("2. Return Book\n");
        printf("3. Direct Issue\n");
        printf("4. Back\n\n");
        
        choice = getIntInput("Choice: ");
        
        switch (choice) {
            case 1: approveRequestsPage(); break;
            case 2: returnBookPage(); break;
            case 3: directIssuePage(); break;
            case 4: return;
            default:
                printf("Invalid option.\n");
                pressEnter();
        }
    }
}
