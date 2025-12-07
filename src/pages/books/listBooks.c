// listBooks.c - List All Books page
#include <stdio.h>
#include "book.h"
#include "ui.h"

void listBooksPage(void) {
    showTitle();
    printf("All Books\n");
    printf("---------\n\n");
    printf("Total Books: %d\n\n", bookCount);
    
    if (bookCount == 0) {
        printf("No books in the library.\n");
    } else {
        for (int i = 0; i < bookCount; i++) {
            printf("%d. %s\n", i + 1, books[i].name);
            printf("   ID: %d | Author: %s | Year: %d\n", 
                books[i].id, books[i].author, books[i].year);
            printf("   Status: %s\n\n", getBookStateName(books[i].state));
        }
    }
    
    pressEnter();
}
