// returnBook.c - Return borrowed book page
#include <stdio.h>
#include "book.h"
#include "member.h"
#include "ui.h"
#include "sync.h"
#include "fileio.h"

void returnBookPage(void) {
    showTitle();
    printf("Return Book\n");
    printf("-----------\n\n");
    
    // find all borrowed books
    int borrowed[MAX_BOOKS];
    int count = 0;
    
    for (int i = 0; i < bookCount; i++) {
        if (books[i].state == STATE_BORROWED) {
            borrowed[count++] = i;
        }
    }
    
    if (count == 0) {
        printf("No borrowed books.\n");
        pressEnter();
        return;
    }
    
    // list all borrowed books
    printf("Borrowed Books: %d\n\n", count);
    for (int i = 0; i < count; i++) {
        int idx = borrowed[i];
        printf("%d. ", i + 1);
        printBookShort(idx);
        printf("\n");
    }
    
    int choice = getIntInput("Select book to return (0 to cancel): ");
    if (choice < 1 || choice > count) {
        printf("Cancelled.\n");
        pressEnter();
        return;
    }
    
    int bookIdx = borrowed[choice - 1];
    
    // show detailed info
    showTitle();
    printf("Return Details\n");
    printf("--------------\n\n");
    printBookDetailed(bookIdx);
    printf("\n");
    
    if (confirmAction("Return this book?")) {
        acquireLock();
        books[bookIdx].state = STATE_AVAILABLE;
        books[bookIdx].memberId = 0;
        releaseLock();
        saveBooksOnly();
        printf("Book returned. Status set to AVAILABLE.\n");
    } else {
        printf("Cancelled.\n");
    }
    
    pressEnter();
}
