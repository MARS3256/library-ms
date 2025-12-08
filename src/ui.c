// ui.c - Common UI functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showTitle(void) {
    clearScreen();
    printf("Library Management System\n");
    printf("--------------------------\n\n");
}

void pressEnter(void) {
    printf("\nPress Enter to continue...");
    getchar();
}

// confirm action with y/n, returns 1 for yes, 0 for no
int confirmAction(const char *message) {
    printf("%s (y/n): ", message);
    char c = getchar();
    clearInputBuffer();
    return (c == 'y' || c == 'Y');
}

// get integer input with prompt
int getIntInput(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        clearInputBuffer();
        printf("Invalid input. \n%s", prompt);
    }
    clearInputBuffer();
    return value;
}

// get string input with prompt
void getStringInput(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
