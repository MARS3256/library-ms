// manageBooks.c - Manage Books menu page
#include <stdio.h>
#include "ui.h"

// forward declarations
void findBookPage(void);
void listBooksPage(void);
void addBookPage(void);
void removeBookPage(void);
void editBookPage(void);

void manageBooksPage(void) {
    int choice;
    
    while (1) {
        showTitle();
        printf("Manage Books\n");
        printf("------------\n\n");
        printf("1. Find Book\n");
        printf("2. List All Books\n");
        printf("3. Add Book\n");
        printf("4. Remove Book\n");
        printf("5. Edit Book\n");
        printf("6. Back\n\n");
        
        choice = getIntInput("Choice: ");
        
        switch (choice) {
            case 1: findBookPage(); break;
            case 2: listBooksPage(); break;
            case 3: addBookPage(); break;
            case 4: removeBookPage(); break;
            case 5: editBookPage(); break;
            case 6: return;
            default:
                printf("Invalid option.\n");
                pressEnter();
        }
    }
}
