// findBook.c - Find Book (reusable for search & select)
#include <stdio.h>
#include <string.h>
#include "book.h"
#include "ui.h"

// search books, returns selected index or -1
// if selectMode=1: allows selection from results
// if selectMode=0: just displays results
int findBook(int selectMode) {
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Author\n");
    printf("4. Year\n\n");
    
    int choice = getIntInput("Choice: ");
    int results[MAX_BOOKS];
    int count = 0;
    
    switch (choice) {
        case 1: {
            int id = getIntInput("Enter Book ID: ");
            int idx = findBookIndexById(id);
            if (idx >= 0) {
                showTitle();
                printf("Book Found:\n\n");
                printBookDetailed(idx);
                if (selectMode) return idx;
            } else {
                printf("Book with ID %d not found.\n", id);
            }
            return -1;
        }
        case 2: {
            char name[50];
            getStringInput("Enter Book Name: ", name, sizeof(name));
            count = findBooksByName(name, results, MAX_BOOKS);
            break;
        }
        case 3: {
            char author[50];
            getStringInput("Enter Author: ", author, sizeof(author));
            count = findBooksByAuthor(author, results, MAX_BOOKS);
            break;
        }
        case 4: {
            int year = getIntInput("Enter Year: ");
            count = findBooksByYear(year, results, MAX_BOOKS);
            break;
        }
        default:
            printf("Invalid option.\n");
            return -1;
    }
    
    if (count == 0) {
        printf("No books found.\n");
        return -1;
    }
    
    // show results
    showTitle();
    printf("Found %d book(s):\n\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d. %s (ID: %d) by %s [%d]\n", i + 1,
            books[results[i]].name, books[results[i]].id,
            books[results[i]].author, books[results[i]].year);
    }
    
    if (!selectMode) return -1;
    
    // select from results
    int sel = getIntInput("\nSelect (0 to cancel): ");
    if (sel < 1 || sel > count) return -1;
    
    return results[sel - 1];
}

// page wrapper for menu
void findBookPage(void) {
    showTitle();
    printf("Find Book\n");
    printf("---------\n\n");
    
    findBook(0);  // display only mode
    pressEnter();
}

