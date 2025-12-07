// book.c - Core book data and functions
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "book.h"
#include "member.h"

Book books[MAX_BOOKS];
int bookCount = 0;

// find book index by ID, returns -1 if not found
int findBookIndexById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) return i;
    }
    return -1;
}

// find books by name, returns count of matches
int findBooksByName(const char *name, int *results, int maxResults) {
    int count = 0;
    for (int i = 0; i < bookCount && count < maxResults; i++) {
        if (strstr(books[i].name, name) != NULL) {
            results[count++] = i;
        }
    }
    return count;
}

// find books by author, returns count of matches
int findBooksByAuthor(const char *author, int *results, int maxResults) {
    int count = 0;
    for (int i = 0; i < bookCount && count < maxResults; i++) {
        if (strstr(books[i].author, author) != NULL) {
            results[count++] = i;
        }
    }
    return count;
}

// check if book ID exists
int isBookIdExists(int id) {
    return findBookIndexById(id) != -1;
}

// get state name string
const char* getBookStateName(int state) {
    switch (state) {
        case STATE_AVAILABLE: return "AVAILABLE";
        case STATE_REQUESTED: return "REQUESTED";
        case STATE_BORROWED:  return "BORROWED";
        default: return "UNKNOWN";
    }
}

// print short book info (for lists)
void printBookShort(int index) {
    printf("Book Name: %s\n", books[index].name);
    printf("Author: %s\n", books[index].author);
    
    if (books[index].memberId > 0) {
        int mIdx = findMemberIndexById(books[index].memberId);
        if (mIdx >= 0) {
            printf("Member: %s\n", members[mIdx].name);
        }
    }
}

// print detailed book info
void printBookDetailed(int index) {
    printf("Name: %s\n", books[index].name);
    printf("ID: %d\n", books[index].id);
    printf("Author: %s\n", books[index].author);
    printf("Year: %d\n", books[index].year);
    printf("Status: %s\n", getBookStateName(books[index].state));
    
    if (books[index].memberId > 0) {
        int mIdx = findMemberIndexById(books[index].memberId);
        if (mIdx >= 0) {
            printf("Member: %s\n", members[mIdx].name);
            printf("Member ID: %d\n", members[mIdx].id);
            printf("Member Dept: %s\n", members[mIdx].dept);
        }
    }
}

// find books by year, returns count of matches
int findBooksByYear(int year, int *results, int maxResults) {
    int count = 0;
    for (int i = 0; i < bookCount && count < maxResults; i++) {
        if (books[i].year == year) {
            results[count++] = i;
        }
    }
    return count;
}
