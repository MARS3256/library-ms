#ifndef BOOK_H
#define BOOK_H

#define MAX_BOOKS 100

// book states
#define STATE_AVAILABLE 0
#define STATE_REQUESTED 1
#define STATE_BORROWED  2

typedef struct Book {
    int id;
    char name[50];
    char author[50];
    int year;
    int state;      // 0=AVAILABLE, 1=REQUESTED, 2=BORROWED
    int memberId;   // 0 if available, else member ID
} Book;

extern Book books[MAX_BOOKS];
extern int bookCount;

// core book functions (book.c)
int findBookIndexById(int id);
int findBooksByName(const char *name, int *results, int maxResults);
int findBooksByAuthor(const char *author, int *results, int maxResults);
int findBooksByYear(int year, int *results, int maxResults);
int isBookIdExists(int id);
void printBookShort(int index);
void printBookDetailed(int index);
const char* getBookStateName(int state);

// find book functions (findBook.c)
int findBook(int selectMode);   // selectMode=1 for selection, 0 for display

#endif
