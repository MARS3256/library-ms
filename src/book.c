#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "book.h"
#include "ui.h"

Book books[MAX_BOOKS];
int numberOfBooks = 0;

void fixBookDetails(int index)
{
    if (books[index].name[0] != '\0')
    {
        books[index].name[0] = (char)toupper((unsigned char)books[index].name[0]);
    }
    books[index].name[strcspn(books[index].name, "\n")] = '\0';

    if (books[index].author[0] != '\0')
    {
        books[index].author[0] = (char)toupper((unsigned char)books[index].author[0]);
    }
    books[index].author[strcspn(books[index].author, "\n")] = '\0';
}

// check if ID already exists
static int idExists(int id)
{
    for (int i = 0; i < numberOfBooks; i++) {
        if (books[i].id == id) return 1;
    }
    return 0;
}

void addBooks(void)
{
    showTitle();
    int requested;
    printf("Enter number of books to add: ");
    if (scanf("%d", &requested) != 1)
    {
        clearInputBuffer();
        printf("Invalid input.\n");
        proceed();
        return;
    }
    clearInputBuffer();

    if (requested <= 0)
    {
        printf("Nothing to add.\n");
        proceed();
        return;
    }

    if (numberOfBooks >= MAX_BOOKS)
    {
        printf("Library is full.\n");
        proceed();
        return;
    }

    int availableSlots = MAX_BOOKS - numberOfBooks;
    if (requested > availableSlots)
    {
        printf("Only %d slot(s) available. Adding what we can.\n", availableSlots);
        requested = availableSlots;
        proceed();
    }

    for (int i = numberOfBooks; i < numberOfBooks + requested; i++)
    {
        showTitle();
        printf("Enter details for Book %d:\n", i + 1);
        
        // get unique ID
        int id;
        printf("ID: ");
        while (1) {
            if (scanf("%d", &id) != 1) {
                clearInputBuffer();
                printf("Invalid ID. Try again: ");
                continue;
            }
            clearInputBuffer();
            if (idExists(id)) {
                printf("ID %d already exists. Try again: ", id);
                continue;
            }
            break;
        }
        books[i].id = id;

        printf("Name: ");
        fgets(books[i].name, sizeof(books[i].name), stdin);

        printf("Author: ");
        fgets(books[i].author, sizeof(books[i].author), stdin);

        printf("Year: ");
        while (scanf("%d", &books[i].year) != 1)
        {
            clearInputBuffer();
            printf("Invalid year. Try again: ");
        }
        clearInputBuffer();

        fixBookDetails(i);
    }

    numberOfBooks += requested;
}

void listAllBooks(void)
{
    showTitle();
    printf("Number of Books: %d\n\n", numberOfBooks);
    for (int i = 0; i < numberOfBooks; i++)
    {
        printf("%d. Name: %s\n", i + 1, books[i].name);
        printf("ID: %d\n", books[i].id);
        printf("Author: %s\n", books[i].author);
        printf("Year: %d\n", books[i].year);
        printf("\n");
    }
    clearInputBuffer();
    proceed();
}

Book findBookByID(int id)
{
    Book book;
    for (int i = 0; i < numberOfBooks; i++)
    {
        if (books[i].id == id)
        {
            book = books[i];
            return book;
        }
    }

    printf("Book with ID %d not found.\n", id);
    book.id = id;
    strcpy(book.name, "Not found");
    strcpy(book.author, "Not found");
    book.year = 0;
    return book;
}

void findBooksByName(const char *name)
{
    int found = 0;
    for (int i = 0; i < numberOfBooks; i++)
    {
        if (strstr(books[i].name, name) != NULL)
        {
            found++;
            printf("%d. Name: %s\n", found, books[i].name);
            printf("ID: %d\n", books[i].id);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("\n");
        }
    }
    printf("%d book(s) found.\n", found);
    proceed();
}

void findBooksByAuthor(const char *author)
{
    int found = 0;
    for (int i = 0; i < numberOfBooks; i++)
    {
        if (strstr(books[i].author, author) != NULL)
        {
            found++;
            printf("%d. Name: %s\n", found, books[i].name);
            printf("ID: %d\n", books[i].id);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("\n");
        }
    }
    printf("%d book(s) found.\n", found);
    proceed();
}

void findBooksByYear(int year)
{
    int found = 0;
    for (int i = 0; i < numberOfBooks; i++)
    {
        if (books[i].year == year)
        {
            found++;
            printf("%d. Name: %s\n", found, books[i].name);
            printf("ID: %d\n", books[i].id);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("\n");
        }
    }
    printf("%d book(s) found.\n", found);
    proceed();
}

void printBookDetails(Book book)
{
    printf("ID: %d\n", book.id);
    printf("Name: %s\n", book.name);
    printf("Year: %d\n", book.year);
    printf("Author: %s\n", book.author);
    proceed();
}
