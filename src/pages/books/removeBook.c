// removeBook.c - Remove Book page
#include <stdio.h>
#include "book.h"
#include "ui.h"
#include "sync.h"

void removeBookPage(void) {
    showTitle();
    printf("Remove Book\n");
    printf("-----------\n\n");
    
    if (bookCount == 0) {
        printf("No books to remove.\n");
        pressEnter();
        return;
    }
    
    int idx = findBook(1);
    
    if (idx < 0) {
        printf("No book selected.\n");
        pressEnter();
        return;
    }
    
    // show book details
    showTitle();
    printf("Book to remove:\n\n");
    printBookDetailed(idx);
    printf("\n");
    
    if (confirmAction("Remove this book?")) {
        acquireLock();
        for (int i = idx; i < bookCount - 1; i++) {
            books[i] = books[i + 1];
        }
        bookCount--;
        releaseLock();
        printf("Book removed successfully.\n");
    } else {
        printf("Cancelled.\n");
    }
    
    pressEnter();
}
