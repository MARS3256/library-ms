// fileio.c - Save/Load data functions
#include <stdio.h>
#include "fileio.h"
#include "book.h"
#include "member.h"
#include "sync.h"

// save books to file
void saveBooks(const char *path) {
    acquireLock();
    FILE *fp = fopen(path, "w");
    if (!fp) {
        printf("Error: Cannot save books file.\n");
        releaseLock();
        return;
    }
    
    fprintf(fp, "%d\n", bookCount);
    for (int i = 0; i < bookCount; i++) {
        fprintf(fp, "%d|%s|%s|%d|%d|%d\n",
            books[i].id, books[i].name, books[i].author,
            books[i].year, books[i].state, books[i].memberId);
    }
    fclose(fp);
    releaseLock();
    printf("Books saved successfully.\n");
}

// load books from file
void loadBooks(const char *path) {
    acquireLock();
    FILE *fp = fopen(path, "r");
    if (!fp) {
        releaseLock();
        return;
    }
    
    if (fscanf(fp, "%d\n", &bookCount) != 1) {
        fclose(fp);
        releaseLock();
        return;
    }
    
    if (bookCount > MAX_BOOKS) bookCount = MAX_BOOKS;
    
    for (int i = 0; i < bookCount; i++) {
        fscanf(fp, "%d|%49[^|]|%49[^|]|%d|%d|%d\n",
            &books[i].id, books[i].name, books[i].author,
            &books[i].year, &books[i].state, &books[i].memberId);
    }
    fclose(fp);
    releaseLock();
}

// save members to file
void saveMembers(const char *path) {
    acquireLock();
    FILE *fp = fopen(path, "w");
    if (!fp) {
        printf("Error: Cannot save members file.\n");
        releaseLock();
        return;
    }
    
    fprintf(fp, "%d\n", memberCount);
    for (int i = 0; i < memberCount; i++) {
        fprintf(fp, "%d|%s|%s\n",
            members[i].id, members[i].name, members[i].dept);
    }
    fclose(fp);
    releaseLock();
    printf("Members saved successfully.\n");
}

// load members from file
void loadMembers(const char *path) {
    acquireLock();
    FILE *fp = fopen(path, "r");
    if (!fp) {
        releaseLock();
        return;
    }
    
    if (fscanf(fp, "%d\n", &memberCount) != 1) {
        fclose(fp);
        releaseLock();
        return;
    }
    
    if (memberCount > MAX_MEMBERS) memberCount = MAX_MEMBERS;
    
    for (int i = 0; i < memberCount; i++) {
        fscanf(fp, "%d|%49[^|]|%3[^\n]\n",
            &members[i].id, members[i].name, members[i].dept);
    }
    fclose(fp);
    releaseLock();
}
