#include "sync.h"
#include <stdio.h>

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
