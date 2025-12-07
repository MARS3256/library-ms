#ifndef SYNC_H
#define SYNC_H

// simple semaphore-based critical section lock
// FCFS order guaranteed by OS scheduler

#ifdef _WIN32
#include <windows.h>
extern HANDLE dataLock;  // binary semaphore for data access
#else
#include <semaphore.h>
extern sem_t dataLock;
#endif

void initLock(void);
void destroyLock(void);
void acquireLock(void);
void releaseLock(void);

#endif
