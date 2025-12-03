#ifndef SYNC_H
#define SYNC_H

#ifdef _WIN32
#include <windows.h>
extern CRITICAL_SECTION catalogLock;
extern HANDLE logSem;
#else
#include <pthread.h>
#include <semaphore.h>
extern pthread_mutex_t catalogLock;
extern sem_t logSem;
#endif

void initLocks(void);       // call once at startup
void destroyLocks(void);    // call before exit
void acquireCatalog(void);  // lock before catalog access
void releaseCatalog(void);  // unlock after catalog access
void acquireLog(void);      // wait on log semaphore
void releaseLog(void);      // post log semaphore

#endif // SYNC_H
