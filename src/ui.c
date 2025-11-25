#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"
#include "book.h"

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void showTitle(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    
    printf("Library Management System\n");
    printf("--------------------------\n");
}

void proceed(void)
{
    printf("Press enter to continue...");
    getchar();
}

void searchBook(void)
{
    showTitle();
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Author\n");
    printf("4. Year\n");
    printf("Choice: ");
    int choice;
    if (scanf("%d", &choice) != 1)
    {
        clearInputBuffer();
        printf("Invalid choice.\n");
        proceed();
        return;
    }
    clearInputBuffer();

    switch (choice)
    {
    case 1:
    {
        showTitle();
        int id;
        printf("Enter ID: ");
        if (scanf("%d", &id) != 1)
        {
            clearInputBuffer();
            printf("Invalid ID.\n");
            proceed();
            return;
        }
        clearInputBuffer();
        Book book = findBookByID(id);
        printBookDetails(book);
        break;
    }
    case 2:
    {
        showTitle();
        char name[50];
        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        findBooksByName(name);
        break;
    }
    case 3:
    {
        showTitle();
        char author[50];
        printf("Enter author: ");
        fgets(author, sizeof(author), stdin);
        author[strcspn(author, "\n")] = '\0';
        findBooksByAuthor(author);
        break;
    }
    case 4:
    {
        showTitle();
        int year;
        printf("Enter year: ");
        if (scanf("%d", &year) != 1)
        {
            clearInputBuffer();
            printf("Invalid year.\n");
            proceed();
            return;
        }
        clearInputBuffer();
        findBooksByYear(year);
        break;
    }
    default:
        printf("Unknown option.\n");
        proceed();
        break;
    }
}
