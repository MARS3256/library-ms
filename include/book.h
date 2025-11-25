#ifndef BOOK_H
#define BOOK_H

#include <stddef.h>

#define MAX_BOOKS 100

typedef struct Book
{
    int id;
    char name[50];
    char author[50];
    int year;
} Book;

extern Book books[MAX_BOOKS];
extern int numberOfBooks;

void addBooks(void);
void listAllBooks(void);
Book findBookByID(int id);
void findBooksByName(const char *name);
void findBooksByAuthor(const char *author);
void findBooksByYear(int year);
void printBookDetails(Book book);
void fixBookDetails(int index);

#endif // BOOK_H
