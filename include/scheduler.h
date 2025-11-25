#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <time.h>

#define MAX_REQUESTS 100

// request from a simulated user
typedef struct {
    int userId;
    int bookId;
    char action;         // 'B' borrow, 'R' return
    int priority;        // lower = higher priority
    struct timespec arrival;
    struct timespec start;
    struct timespec finish;
} Request;

// queue helpers
void addRequest(Request r);
int pendingRequests(void);

// scheduling algorithms
void runFCFS(void);              // first-come first-served
void runRoundRobin(int quantum); // time-slice in ms
void runPriority(void);          // by priority field

#endif // SCHEDULER_H
