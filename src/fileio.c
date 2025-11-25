#include "fileio.h"
#include "sync.h"
#include <stdio.h>
#include <time.h>

// save catalog to text file
void saveCatalog(const char *path)
{
    acquireCatalog();
    FILE *fp = fopen(path, "w");
    if (!fp) { releaseCatalog(); return; }
    fprintf(fp, "%d\n", numberOfBooks);
    for (int i = 0; i < numberOfBooks; i++) {
        fprintf(fp, "%d|%s|%s|%d\n",
                books[i].id, books[i].name, books[i].author, books[i].year);
    }
    fclose(fp);
    releaseCatalog();
}

// load catalog from text file
void loadCatalog(const char *path)
{
    acquireCatalog();
    FILE *fp = fopen(path, "r");
    if (!fp) { releaseCatalog(); return; }
    if (fscanf(fp, "%d\n", &numberOfBooks) != 1) {
        fclose(fp); releaseCatalog(); return;
    }
    if (numberOfBooks > MAX_BOOKS) numberOfBooks = MAX_BOOKS;
    for (int i = 0; i < numberOfBooks; i++) {
        fscanf(fp, "%d|%49[^|]|%49[^|]|%d\n",
               &books[i].id, books[i].name, books[i].author, &books[i].year);
    }
    fclose(fp);
    releaseCatalog();
}

// append transaction to log file
void logTransaction(int userId, int bookId, char action)
{
    acquireLog();
    FILE *fp = fopen("data/transactions.log", "a");
    if (!fp) { releaseLog(); return; }
    time_t now = time(NULL);
    fprintf(fp, "%ld,user%d,book%d,%c\n", now, userId, bookId, action);
    fclose(fp);
    releaseLog();
}
