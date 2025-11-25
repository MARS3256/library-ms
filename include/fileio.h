#ifndef FILEIO_H
#define FILEIO_H

#include "book.h"

// save/load catalog (text format)
void saveCatalog(const char *path);
void loadCatalog(const char *path);

// transaction log
void logTransaction(int userId, int bookId, char action);

#endif // FILEIO_H
