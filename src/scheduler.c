#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#include "scheduler.h"
#include "analytics.h"
#include "fileio.h"
#include "sync.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
// no unistd.h on Windows
#else
#include <unistd.h>
#endif

static Request queue[MAX_REQUESTS];
static int queueSize = 0;

// helper: get current time
#ifdef _WIN32
static void now(LARGE_INTEGER *ts)
{
    QueryPerformanceCounter(ts);
}
#else
static void now(struct timespec *ts)
{
    clock_gettime(CLOCK_MONOTONIC, ts);
}
#endif

// add request to queue
void addRequest(Request r)
{
    if (queueSize >= MAX_REQUESTS) return;
    now(&r.arrival);
    queue[queueSize++] = r;
}

int pendingRequests(void)
{
    return queueSize;
}

// simulate processing a request (just sleeps briefly)
static void processRequest(Request *r)
{
    now(&r->start);
#ifdef _WIN32
    Sleep(1); // 1ms work
#else
    usleep(1000); // 1ms work
#endif
    logTransaction(r->userId, r->bookId, r->action);
    now(&r->finish);
    recordMetrics(*r);
}

// FCFS: process in arrival order
void runFCFS(void)
{
    for (int i = 0; i < queueSize; i++) {
        processRequest(&queue[i]);
    }
    queueSize = 0;
}

// Round-Robin: cycle through requests with time quantum
void runRoundRobin(int quantum)
{
    int done = 0;
    int remaining[MAX_REQUESTS];
    for (int i = 0; i < queueSize; i++) remaining[i] = quantum;

    while (done < queueSize) {
        for (int i = 0; i < queueSize; i++) {
            if (remaining[i] <= 0) continue;
            now(&queue[i].start);
#ifdef _WIN32
            Sleep((DWORD)quantum); // scaled sleep in ms
#else
            usleep((unsigned)quantum * 100); // scaled sleep
#endif
            remaining[i] = 0;
            logTransaction(queue[i].userId, queue[i].bookId, queue[i].action);
            now(&queue[i].finish);
            recordMetrics(queue[i]);
            done++;
        }
    }
    queueSize = 0;
}

// compare by priority for qsort
static int cmpPriority(const void *a, const void *b)
{
    return ((Request *)a)->priority - ((Request *)b)->priority;
}

// Priority: sort then process
void runPriority(void)
{
    qsort(queue, (size_t)queueSize, sizeof(Request), cmpPriority);
    for (int i = 0; i < queueSize; i++) {
        processRequest(&queue[i]);
    }
    queueSize = 0;
}
