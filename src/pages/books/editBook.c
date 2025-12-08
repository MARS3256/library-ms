// editBook.c - Edit Book page
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "book.h"
#include "ui.h"
#include "sync.h"
#include "fileio.h"

void editBookPage(void) {
    showTitle();
    printf("Edit Book\n");
    printf("---------\n\n");
    
    if (bookCount == 0) {
        printf("No books to edit.\n");
        pressEnter();
        return;
    }
    
    int idx = findBook(1);
    
    if (idx < 0) {
        printf("No book selected.\n");
        pressEnter();
        return;
    }
    
    showTitle();
    printf("Editing Book (ID: %d)\n", books[idx].id);
    printf("Use 0 to skip a field\n\n");
    
    char input[50];
    
    // edit name
    printf("Current Name: %s\n", books[idx].name);
    getStringInput("New Name: ", input, sizeof(input));
    if (strlen(input) > 0 && strcmp(input, "0") != 0) {
        acquireLock();
        strcpy(books[idx].name, input);
        if (books[idx].name[0]) {
            books[idx].name[0] = toupper(books[idx].name[0]);
        }
        releaseLock();
    }
    
    // edit author
    printf("\nCurrent Author: %s\n", books[idx].author);
    getStringInput("New Author: ", input, sizeof(input));
    if (strlen(input) > 0 && strcmp(input, "0") != 0) {
        acquireLock();
        strcpy(books[idx].author, input);
        if (books[idx].author[0]) {
            books[idx].author[0] = toupper(books[idx].author[0]);
        }
        releaseLock();
    }
    
    // edit year
    printf("\nCurrent Year: %d\n", books[idx].year);
    printf("New Year (0 to skip): ");
    int year = getIntInput("");
    if (year != 0) {
        acquireLock();
        books[idx].year = year;
        releaseLock();
    }
    
    saveBooksOnly();
    printf("\nBook updated successfully.\n");
    pressEnter();
}
