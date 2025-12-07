// approveRequests.c - Approve book requests page
#include <stdio.h>
#include "book.h"
#include "member.h"
#include "ui.h"
#include "sync.h"

void approveRequestsPage(void) {
    showTitle();
    printf("Approve Requests\n");
    printf("----------------\n\n");
    
    // find all requested books
    int requested[MAX_BOOKS];
    int count = 0;
    
    for (int i = 0; i < bookCount; i++) {
        if (books[i].state == STATE_REQUESTED) {
            requested[count++] = i;
        }
    }
    
    if (count == 0) {
        printf("No pending requests.\n");
        pressEnter();
        return;
    }
    
    // list all requested books
    printf("Pending Requests: %d\n\n", count);
    for (int i = 0; i < count; i++) {
        int idx = requested[i];
        printf("%d. ", i + 1);
        printBookShort(idx);
        printf("\n");
    }
    
    int choice = getIntInput("Select request (0 to cancel): ");
    if (choice < 1 || choice > count) {
        printf("Cancelled.\n");
        pressEnter();
        return;
    }
    
    int bookIdx = requested[choice - 1];
    
    // show detailed info
    showTitle();
    printf("Request Details\n");
    printf("---------------\n\n");
    printBookDetailed(bookIdx);
    printf("\n");
    
    if (confirmAction("Approve this request?")) {
        acquireLock();
        books[bookIdx].state = STATE_BORROWED;
        releaseLock();
        printf("Request approved. Book marked as BORROWED.\n");
    } else {
        printf("Cancelled.\n");
    }
    
    pressEnter();
}
