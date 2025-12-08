// runSimulation.c - Simulation page
#include <stdio.h>
#include <time.h>
#include "ui.h"
#include "book.h"
#include "member.h"
#include "action.h"

// convert ms to ns
static long long msToNs(int ms) {
    return (long long)ms * 1000000LL;
}

// convert ns to ms for display
static double nsToMs(long long ns) {
    return (double)ns / 1000000.0;
}

void runSimulationPage(void) {
    showTitle();
    printf("FCFS Scheduling Simulation\n");
    printf("--------------------------\n\n");
    
    if (bookCount == 0) {
        printf("No books in catalog. Add some books first.\n");
        pressEnter();
        return;
    }
    
    if (memberCount == 0) {
        printf("No members registered. Add some members first.\n");
        pressEnter();
        return;
    }
    
    printf("Current Data:\n");
    printf("- Books: %d\n", bookCount);
    printf("- Members: %d\n\n", memberCount);
    
    printf("This simulation will:\n");
    printf("1. Generate random actions (Approve/Return/Issue/Request)\n");
    printf("2. Run FCFS scheduler with semaphore protection\n");
    printf("3. Update catalog.txt with real book state changes\n");
    printf("4. Log actions to simulation_log.txt\n");
    printf("5. Log queue states to queue_log.txt\n\n");
    
    int timeLimitMs = getIntInput("Enter time limit in ms (e.g. 5000): ");
    if (timeLimitMs <= 0) {
        printf("Invalid time limit.\n");
        pressEnter();
        return;
    }
    
    int minTimeMs = getIntInput("Min AT interval in ms (e.g. 100): ");
    if (minTimeMs <= 0) minTimeMs = 100;
    
    int maxTimeMs = getIntInput("Max AT interval in ms (e.g. 500): ");
    if (maxTimeMs <= 0 || maxTimeMs < minTimeMs) maxTimeMs = minTimeMs + 100;
    
    int maxRepeats = getIntInput("Max actions at same AT (e.g. 3): ");
    if (maxRepeats <= 0) maxRepeats = 3;
    
    long long timeLimitNs = msToNs(timeLimitMs);
    
    // open log files
    FILE *logFile = fopen("data/simulation_log.txt", "w");
    FILE *queueLog = fopen("data/queue_log.txt", "w");
    if (!logFile || !queueLog) {
        printf("Error: Cannot create log files.\n");
        if (logFile) fclose(logFile);
        if (queueLog) fclose(queueLog);
        pressEnter();
        return;
    }
    
    // write log headers
    time_t now = time(NULL);
    fprintf(logFile, "FCFS Simulation Log\n");
    fprintf(logFile, "Date: %s", ctime(&now));
    fprintf(logFile, "Time Limit: %d ms\n", timeLimitMs);
    fprintf(logFile, "Books: %d, Members: %d\n", bookCount, memberCount);
    
    fprintf(queueLog, "FCFS Queue State Log\n");
    fprintf(queueLog, "Date: %s", ctime(&now));
    fprintf(queueLog, "Time Limit: %d ms\n\n", timeLimitMs);
    
    printf("\nGenerating actions...\n");
    printf("Settings: AT interval %d-%d ms, max %d repeats\n", minTimeMs, maxTimeMs, maxRepeats);
    generateActions(timeLimitNs, minTimeMs, maxTimeMs, maxRepeats);
    
    // log generated actions
    fprintf(logFile, "\n========== GENERATED ACTIONS ==========\n");
    for (int i = 0; i < actionCount; i++) {
        fprintf(logFile, "Action %d: AT=%.2f ms, Type=%s\n", 
            i + 1, nsToMs(actions[i].arrivalTime), getActionTypeName(actions[i].type));
    }
    
    printf("\nStarting FCFS simulation...\n");
    printf("Actions will modify catalog.txt in real-time.\n\n");
    
    runSimulator(logFile, queueLog);
    
    fclose(logFile);
    fclose(queueLog);
    
    printf("\nLogs saved to:\n");
    printf("- data/simulation_log.txt\n");
    printf("- data/queue_log.txt\n");
    pressEnter();
}
