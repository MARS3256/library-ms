#include "sync.h"
#include <stdio.h>

#ifdef _WIN32
CRITICAL_SECTION catalogLock;
HANDLE logSem;

void initLocks(void)
{
    InitializeCriticalSection(&catalogLock);
    logSem = CreateSemaphore(NULL, 1, 1, NULL); // binary semaphore
}

void destroyLocks(void)
{
    DeleteCriticalSection(&catalogLock);
    CloseHandle(logSem);
}

void acquireCatalog(void)
{
    EnterCriticalSection(&catalogLock);
}

void releaseCatalog(void)
{
    LeaveCriticalSection(&catalogLock);
}

void acquireLog(void)
{
    WaitForSingleObject(logSem, INFINITE);
}

void releaseLog(void)
{
    ReleaseSemaphore(logSem, 1, NULL);
}
#else
pthread_mutex_t catalogLock;
sem_t logSem;

void initLocks(void)
{
    pthread_mutex_init(&catalogLock, NULL);
    sem_init(&logSem, 0, 1); // binary semaphore
}

void destroyLocks(void)
{
    pthread_mutex_destroy(&catalogLock);
    sem_destroy(&logSem);
}

void acquireCatalog(void)
{
    pthread_mutex_lock(&catalogLock);
}

void releaseCatalog(void)
{
    pthread_mutex_unlock(&catalogLock);
}

void acquireLog(void)
{
    sem_wait(&logSem);
}

void releaseLog(void)
{
    sem_post(&logSem);
}
#endif
