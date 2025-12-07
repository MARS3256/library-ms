// addBook.c - Add Book page
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "book.h"
#include "ui.h"
#include "sync.h"

void addBookPage(void) {
    showTitle();
    printf("Add New Book\n");
    printf("------------\n\n");
    
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        pressEnter();
        return;
    }
    
    Book newBook;
    
    // get unique ID
    while (1) {
        newBook.id = getIntInput("Book ID: ");
        if (isBookIdExists(newBook.id)) {
            printf("ID %d already exists. Try another.\n", newBook.id);
        } else {
            break;
        }
    }
    
    getStringInput("Book Name: ", newBook.name, sizeof(newBook.name));
    getStringInput("Author: ", newBook.author, sizeof(newBook.author));
    newBook.year = getIntInput("Year: ");
    
    // capitalize first letter
    if (newBook.name[0]) newBook.name[0] = toupper(newBook.name[0]);
    if (newBook.author[0]) newBook.author[0] = toupper(newBook.author[0]);
    
    // new books are available by default
    newBook.state = STATE_AVAILABLE;
    newBook.memberId = 0;
    
    if (confirmAction("Add this book?")) {
        acquireLock();
        books[bookCount++] = newBook;
        releaseLock();
        printf("Book added successfully.\n");
    } else {
        printf("Cancelled.\n");
    }
    
    pressEnter();
}
