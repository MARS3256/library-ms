// action.c - Action sequence implementations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "action.h"
#include "book.h"
#include "member.h"
#include "sync.h"
#include "fileio.h"

// get high resolution time in ns
static long long getTimeNs(void) {
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart * 1000000000LL) / freq.QuadPart;
}

// convert ns to ms for display
static double nsToMs(long long ns) {
    return (double)ns / 1000000.0;
}

// get action type name
const char* getActionTypeName(int type) {
    switch (type) {
        case ACTION_APPROVE: return "APPROVE";
        case ACTION_RETURN:  return "RETURN";
        case ACTION_ISSUE:   return "ISSUE";
        case ACTION_REQUEST: return "REQUEST";
        default: return "UNKNOWN";
    }
}

// perform approve request action
static long long doApprove(int actionIndex, long long simTime, FILE *logFile) {
    long long totalBT = 0;
    double simTimeMs = nsToMs(simTime);
    int subAction = 0;
    double cumulativeFinish = simTimeMs;
    
    // find all requested books
    int requested[MAX_BOOKS];
    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].state == STATE_REQUESTED) {
            requested[count++] = i;
        }
    }
    
    if (count == 0) {
        fprintf(logFile, "[%.2f ms] APPROVE: No pending requests\n", simTimeMs);
        return 100;
    }
    
    for (int i = 0; i < count; i++) {
        if (getRandomBool()) continue;
        
        long long startTime = getTimeNs();
        subAction++;
        
        int idx = requested[i];
        int approve = getRandomBool();
        
        int mIdx = findMemberIndexById(books[idx].memberId);
        char memberName[50] = "Unknown";
        if (mIdx >= 0) {
            strcpy(memberName, members[mIdx].name);
        }
        
        acquireLock();
        if (approve) {
            books[idx].state = STATE_BORROWED;
            printf("[%.2f ms] Approved: %s to %s\n", simTimeMs, books[idx].name, memberName);
            fprintf(logFile, "[%.2f ms] APPROVED: %s to member %s\n", simTimeMs, books[idx].name, memberName);
        } else {
            books[idx].state = STATE_AVAILABLE;
            books[idx].memberId = 0;
            printf("[%.2f ms] Rejected: %s request from %s\n", simTimeMs, books[idx].name, memberName);
            fprintf(logFile, "[%.2f ms] REJECTED: %s request from member %s\n", simTimeMs, books[idx].name, memberName);
        }
        releaseLock();
        saveBooksOnly();
        
        long long endTime = getTimeNs();
        long long subBT = endTime - startTime;
        totalBT += subBT;
        cumulativeFinish += nsToMs(subBT);
        fprintf(logFile, "Action %d.%d completed - BT: %.2f ms, Finish: %.2f ms\n",
            actionIndex + 1, subAction, nsToMs(subBT), cumulativeFinish);
    }
    
    return totalBT > 0 ? totalBT : 100;
}

// perform return book action
static long long doReturn(int actionIndex, long long simTime, FILE *logFile) {
    long long totalBT = 0;
    double simTimeMs = nsToMs(simTime);
    int subAction = 0;
    double cumulativeFinish = simTimeMs;
    
    // find all borrowed books
    int borrowed[MAX_BOOKS];
    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].state == STATE_BORROWED) {
            borrowed[count++] = i;
        }
    }
    
    if (count == 0) {
        fprintf(logFile, "[%.2f ms] RETURN: No borrowed books\n", simTimeMs);
        return 100;
    }
    
    for (int i = 0; i < count; i++) {
        if (getRandomBool()) continue;
        
        long long startTime = getTimeNs();
        subAction++;
        
        int idx = borrowed[i];
        int mIdx = findMemberIndexById(books[idx].memberId);
        char memberName[50] = "Unknown";
        if (mIdx >= 0) {
            strcpy(memberName, members[mIdx].name);
        }
        
        acquireLock();
        books[idx].state = STATE_AVAILABLE;
        books[idx].memberId = 0;
        releaseLock();
        saveBooksOnly();
        
        printf("[%.2f ms] Returned: %s from %s\n", simTimeMs, books[idx].name, memberName);
        fprintf(logFile, "[%.2f ms] RETURNED: %s from member %s\n", simTimeMs, books[idx].name, memberName);
        
        long long endTime = getTimeNs();
        long long subBT = endTime - startTime;
        totalBT += subBT;
        cumulativeFinish += nsToMs(subBT);
        fprintf(logFile, "Action %d.%d completed - BT: %.2f ms, Finish: %.2f ms\n",
            actionIndex + 1, subAction, nsToMs(subBT), cumulativeFinish);
    }
    
    return totalBT > 0 ? totalBT : 100;
}

// perform direct issue action - uses semaphore for critical section
static long long doIssue(int actionIndex, long long simTime, FILE *logFile) {
    long long totalBT = 0;
    double simTimeMs = nsToMs(simTime);
    double cumulativeFinish = simTimeMs;
    
    // find all available books
    int available[MAX_BOOKS];
    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].state == STATE_AVAILABLE) {
            available[count++] = i;
        }
    }
    
    if (count == 0) {
        fprintf(logFile, "[%.2f ms] ISSUE: No available books\n", simTimeMs);
        return 100;
    }
    
    if (memberCount == 0) {
        fprintf(logFile, "[%.2f ms] ISSUE: No members\n", simTimeMs);
        return 100;
    }
    
    // pick random book
    int bookIdx = available[getRandomInt(0, count - 1)];
    
    // simulate multiple requests for same book
    int requests = getRandomInt(1, 3);
    
    for (int r = 0; r < requests; r++) {
        long long startTime = getTimeNs();
        
        int memberIdx = getRandomInt(0, memberCount - 1);
        
        acquireLock();
        if (books[bookIdx].state == STATE_AVAILABLE) {
            books[bookIdx].state = STATE_BORROWED;
            books[bookIdx].memberId = members[memberIdx].id;
            releaseLock();
            saveBooksOnly();
            
            printf("[%.2f ms] Issued: %s to %s\n", simTimeMs, books[bookIdx].name, members[memberIdx].name);
            fprintf(logFile, "[%.2f ms] ISSUED: %s to member %s (ID: %d)\n", 
                simTimeMs, books[bookIdx].name, members[memberIdx].name, members[memberIdx].id);
        } else {
            releaseLock();
            printf("[%.2f ms] Rejected issue: %s already taken\n", simTimeMs, books[bookIdx].name);
            fprintf(logFile, "[%.2f ms] REJECTED ISSUE: %s already taken\n", simTimeMs, books[bookIdx].name);
        }
        
        long long endTime = getTimeNs();
        long long subBT = endTime - startTime;
        totalBT += subBT;
        cumulativeFinish += nsToMs(subBT);
        fprintf(logFile, "Action %d.%d completed - BT: %.2f ms, Finish: %.2f ms\n",
            actionIndex + 1, r + 1, nsToMs(subBT), cumulativeFinish);
    }
    
    return totalBT;
}

// perform new request action - uses semaphore for critical section
static long long doRequest(int actionIndex, long long simTime, FILE *logFile) {
    long long totalBT = 0;
    double simTimeMs = nsToMs(simTime);
    double cumulativeFinish = simTimeMs;
    
    // find all available books
    int available[MAX_BOOKS];
    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].state == STATE_AVAILABLE) {
            available[count++] = i;
        }
    }
    
    if (count == 0) {
        fprintf(logFile, "[%.2f ms] REQUEST: No available books\n", simTimeMs);
        return 100;
    }
    
    if (memberCount == 0) {
        fprintf(logFile, "[%.2f ms] REQUEST: No members\n", simTimeMs);
        return 100;
    }
    
    // pick random book
    int bookIdx = available[getRandomInt(0, count - 1)];
    
    // simulate multiple requests for same book
    int requests = getRandomInt(1, 3);
    
    for (int r = 0; r < requests; r++) {
        long long startTime = getTimeNs();
        
        int memberIdx = getRandomInt(0, memberCount - 1);
        
        acquireLock();
        if (books[bookIdx].state == STATE_AVAILABLE) {
            books[bookIdx].state = STATE_REQUESTED;
            books[bookIdx].memberId = members[memberIdx].id;
            releaseLock();
            saveBooksOnly();
            
            printf("[%.2f ms] Request: %s by %s\n", simTimeMs, books[bookIdx].name, members[memberIdx].name);
            fprintf(logFile, "[%.2f ms] REQUESTED: %s by member %s (ID: %d)\n", 
                simTimeMs, books[bookIdx].name, members[memberIdx].name, members[memberIdx].id);
        } else {
            releaseLock();
            printf("[%.2f ms] Rejected request: %s not available\n", simTimeMs, books[bookIdx].name);
            fprintf(logFile, "[%.2f ms] REJECTED REQUEST: %s not available\n", simTimeMs, books[bookIdx].name);
        }
        
        long long endTime = getTimeNs();
        long long subBT = endTime - startTime;
        totalBT += subBT;
        cumulativeFinish += nsToMs(subBT);
        fprintf(logFile, "Action %d.%d completed - BT: %.2f ms, Finish: %.2f ms\n",
            actionIndex + 1, r + 1, nsToMs(subBT), cumulativeFinish);
    }
    
    return totalBT;
}

// perform action and return burst time in ns
long long performAction(int index, FILE *logFile) {
    if (index < 0 || index >= actionCount) return 0;
    
    long long simTime = actions[index].arrivalTime;
    int type = actions[index].type;
    
    switch (type) {
        case ACTION_APPROVE: return doApprove(index, simTime, logFile);
        case ACTION_RETURN:  return doReturn(index, simTime, logFile);
        case ACTION_ISSUE:   return doIssue(index, simTime, logFile);
        case ACTION_REQUEST: return doRequest(index, simTime, logFile);
        default: return 100;
    }
}
