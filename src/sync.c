// sync.c - Simple semaphore-based critical section lock (FCFS)
#include "sync.h"

#ifdef _WIN32
HANDLE dataLock;

void initLock(void) {
    // binary semaphore (1 = available, 0 = locked)
    dataLock = CreateSemaphore(NULL, 1, 1, NULL);
}

void destroyLock(void) {
    CloseHandle(dataLock);
}

void acquireLock(void) {
    // FCFS: processes wait in queue order
    WaitForSingleObject(dataLock, INFINITE);
}

void releaseLock(void) {
    ReleaseSemaphore(dataLock, 1, NULL);
}

#else
sem_t dataLock;

void initLock(void) {
    sem_init(&dataLock, 0, 1);
}

void destroyLock(void) {
    sem_destroy(&dataLock);
}

void acquireLock(void) {
    sem_wait(&dataLock);
}

void releaseLock(void) {
    sem_post(&dataLock);
}
#endif
