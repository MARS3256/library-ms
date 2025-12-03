#ifndef SCHEDULER_H
#define SCHEDULER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#define MAX_REQUESTS 100

// request from a simulated user
typedef struct {
    int userId;
    int bookId;
    char action;         // 'B' borrow, 'R' return
    int priority;        // lower = higher priority
#ifdef _WIN32
    LARGE_INTEGER arrival;
    LARGE_INTEGER start;
    LARGE_INTEGER finish;
#else
    struct timespec arrival;
    struct timespec start;
    struct timespec finish;
#endif
} Request;

// queue helpers
void addRequest(Request r);
int pendingRequests(void);

// scheduling algorithms
void runFCFS(void);              // first-come first-served
void runRoundRobin(int quantum); // time-slice in ms
void runPriority(void);          // by priority field

#endif // SCHEDULER_H
