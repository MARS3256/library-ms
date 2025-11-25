/*
Library Management System
-------------------------
Made by: Muhammad As-Adur Rahman Sajid (233014037)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearInputBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Discard the input
    }
}

void showTitle()
{
    system("cls");
    printf("C 233014037, Muhammad As-Adur Rahman Sajid\n");
    printf("Library Management System\n");
    printf("--------------------------\n");
}

void proceed()
{
    printf("Press enter to continue...");
    getchar();
}

struct Book
{
    int id;
    char name[50];
    char author[50];
    int year;
};

struct Book books[100];
int numberOfBooks = 0;

void fixBookdetails(int index)
{

    books[index].name[0] = toupper(books[index].name[0]);       // Capitalize the first letter
    books[index].name[strcspn(books[index].name, "\n")] = '\0'; // Remove the newline character
    books[index].author[0] = toupper(books[index].author[0]);
    books[index].author[strcspn(books[index].author, "\n")] = '\0';
}

void addBooks()
{
    showTitle();
    int inputs;
    printf("Enter number of books to add: ");
    scanf("%d", &inputs);
    clearInputBuffer();

    for (int i = numberOfBooks; i < inputs; i++)
    {
        showTitle();
        printf("Enter details for Book %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &books[i].id);
        clearInputBuffer(); // Clear the input buffer for unwanted /n
        printf("Name: ");
        fgets(books[i].name, 50, stdin);
        printf("Author: ");
        fgets(books[i].author, 50, stdin);
        printf("Year: ");
        scanf("%d", &books[i].year);
        clearInputBuffer();
        fixBookdetails(i);
    }
    numberOfBooks += inputs;
}

void listAllBooks()
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

struct Book findBookbyID(int id)
{
    showTitle();
    struct Book book;
    int i, j;

    for (i = 0; i < numberOfBooks; i++)
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

void findBooksbyName(char name[])
{
    int j = 0;
    for (int i = 0; i < numberOfBooks; i++)
    {
        if (strstr(books[i].name, name) != NULL)
        {
            j++;
            printf("%d. Name: %s\n", j, books[i].name);
            printf("ID: %d\n", books[i].id);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("\n");
        }
    }
    printf("%d book(s) found.\n", j);
    proceed();
}

void findBooksbyAuthor(char author[])
{
    int j = 0;
    for (int i = 0; i < numberOfBooks; i++)
    {
        if (strstr(books[i].author, author) != NULL)
        {
            j++;
            printf("%d. Name: %s\n", j, books[i].name);
            printf("ID: %d\n", books[i].id);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("\n");
        }
    }
    printf("%d book(s) found.\n", j);
    proceed();
}

void findBooksbyYear(int year)
{
    int j = 0;
    for (int i = 0; i < numberOfBooks; i++)
    {
        if (books[i].year == year)
        {
            j++;
            printf("%d. Name: %s\n", j, books[i].name);
            printf("ID: %d\n", books[i].id);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("\n");
        }
    }
    printf("%d book(s) found.\n", j);
    proceed();
}

void printBookDetails(struct Book Book)
{
    printf("ID: %d\n", Book.id);
    printf("Name: %s\n", Book.name);
    printf("Year: %d\n", Book.year);
    printf("Author: %s\n", Book.author);
    proceed();
}

void searchBook()
{
    showTitle();
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Author\n");
    printf("4. Year\n");
    printf("Choice: ");
    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice)
    {
    case 1:
    {
        showTitle();
        int id;
        printf("Enter ID: ");
        scanf("%d", &id);
        clearInputBuffer();
        printBookDetails(findBookbyID(id));
    }
    break;
    case 2:
    {
        showTitle();
        char name[50];
        printf("Enter name: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove the newline character
        findBooksbyName(name);
    }
    break;
    case 3:
    {
        showTitle();
        char author[50];
        printf("Enter author: ");
        fgets(author, 50, stdin);
        author[strcspn(author, "\n")] = '\0'; // Remove the newline character
        findBooksbyAuthor(author);
    }
    break;
    case 4:
    {

        showTitle();
        int year;
        printf("Enter year: ");
        scanf("%d", &year);
        clearInputBuffer();
        findBooksbyYear(year);
    }
    }
}

void main()
{
    do
    {
        showTitle();
        printf("1. Add Books\n");
        printf("2. List All Books\n");
        printf("3. Find Book\n");
        printf("4. Exit\n");
        printf("Choice: ");
        int option;
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            addBooks();
            break;
        case 2:
            listAllBooks();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            return;
        }
    } while (1);
}