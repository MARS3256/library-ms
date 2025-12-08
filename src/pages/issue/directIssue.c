// directIssue.c - Direct issue book to member page
#include <stdio.h>
#include "book.h"
#include "member.h"
#include "ui.h"
#include "sync.h"
#include "fileio.h"

void directIssuePage(void) {
    showTitle();
    printf("Direct Issue\n");
    printf("------------\n\n");
    
    if (bookCount == 0) {
        printf("No books available.\n");
        pressEnter();
        return;
    }
    
    if (memberCount == 0) {
        printf("No members registered.\n");
        pressEnter();
        return;
    }
    
    // select book using search
    printf("-- Select Book --\n\n");
    int bookIdx = findBook(1);
    
    if (bookIdx < 0) {
        printf("No book selected.\n");
        pressEnter();
        return;
    }
    
    // check book state
    if (books[bookIdx].state != STATE_AVAILABLE) {
        showTitle();
        printf("Book is currently %s.\n", getBookStateName(books[bookIdx].state));
        if (books[bookIdx].memberId > 0) {
            int mIdx = findMemberIndexById(books[bookIdx].memberId);
            if (mIdx >= 0) {
                printf("Issued to: %s (ID: %d)\n", members[mIdx].name, members[mIdx].id);
            }
        }
        pressEnter();
        return;
    }
    
    // show book info
    showTitle();
    printf("Selected Book:\n");
    printBookDetailed(bookIdx);
    printf("\n");
    
    // select member using search
    printf("-- Select Member --\n\n");
    int memberIdx = findMember(1);
    
    if (memberIdx < 0) {
        printf("No member selected.\n");
        pressEnter();
        return;
    }
    
    // show member info
    showTitle();
    printf("Issue Book:\n");
    printBookDetailed(bookIdx);
    printf("\nTo Member:\n");
    printMemberDetailed(memberIdx);
    printf("\n");
    
    if (confirmAction("Issue this book to this member?")) {
        acquireLock();
        books[bookIdx].state = STATE_BORROWED;
        books[bookIdx].memberId = members[memberIdx].id;
        releaseLock();
        saveBooksOnly();
        printf("Book issued successfully.\n");
    } else {
        printf("Cancelled.\n");
    }
    
    pressEnter();
}
