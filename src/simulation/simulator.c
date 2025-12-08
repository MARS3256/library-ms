// simulator.c - FCFS scheduler simulation
#include <stdio.h>
#include <stdlib.h>
#include "action.h"

// simple queue for FCFS
static int queue[MAX_ACTIONS];
static int queueSize = 0;
static int processed[MAX_ACTIONS] = {0};

// convert ns to ms for display
static double nsToMs(long long ns) {
    return (double)ns / 1000000.0;
}

// add to queue
static void enqueue(int index) {
    if (queueSize < MAX_ACTIONS) {
        queue[queueSize++] = index;
    }
}

// remove from front
static int dequeue(void) {
    if (queueSize == 0) return -1;
    int front = queue[0];
    for (int i = 0; i < queueSize - 1; i++) {
        queue[i] = queue[i + 1];
    }
    queueSize--;
    return front;
}

// log current queue state
static void logQueueState(FILE *queueLog, long long currentTime) {
    fprintf(queueLog, "[%.2f ms] [", nsToMs(currentTime));
    for (int i = 0; i < queueSize; i++) {
        fprintf(queueLog, "A%d", queue[i] + 1);
        if (i < queueSize - 1) fprintf(queueLog, ", ");
    }
    fprintf(queueLog, "]\n");
}

// run FCFS simulation
void runSimulator(FILE *logFile, FILE *queueLog) {
    if (actionCount == 0) {
        printf("No actions to simulate.\n");
        return;
    }
    
    // reset state
    queueSize = 0;
    for (int i = 0; i < actionCount; i++) {
        processed[i] = 0;
    }
    
    long long currentTime = 0;
    int actionIndex = 0;
    int completed = 0;
    long long totalBT = 0;
    long long totalWT = 0;
    
    fprintf(logFile, "\n========== FCFS SIMULATION START ==========\n\n");
    fprintf(queueLog, "========== QUEUE STATE LOG ==========\n\n");
    printf("\n========== FCFS SIMULATION START ==========\n\n");
    
    // add initial actions at time 0
    while (actionIndex < actionCount && actions[actionIndex].arrivalTime <= currentTime) {
        enqueue(actionIndex);
        processed[actionIndex] = 1;
        actionIndex++;
    }
    
    // log initial queue
    logQueueState(queueLog, currentTime);
    
    // process queue
    while (queueSize > 0 || actionIndex < actionCount) {
        // if queue empty, jump to next arrival
        if (queueSize == 0 && actionIndex < actionCount) {
            currentTime = actions[actionIndex].arrivalTime;
            while (actionIndex < actionCount && actions[actionIndex].arrivalTime <= currentTime) {
                enqueue(actionIndex);
                processed[actionIndex] = 1;
                actionIndex++;
            }
            logQueueState(queueLog, currentTime);
        }
        
        if (queueSize == 0) break;
        
        // get next action from queue
        int idx = dequeue();
        
        // calculate waiting time
        long long waitTime = currentTime - actions[idx].arrivalTime;
        if (waitTime < 0) waitTime = 0;
        totalWT += waitTime;
        
        // log action start (display in ms)
        fprintf(logFile, "Action %d (%s) - AT: %.2f ms, Start: %.2f ms, WT: %.2f ms\n",
            idx + 1, getActionTypeName(actions[idx].type), 
            nsToMs(actions[idx].arrivalTime), nsToMs(currentTime), nsToMs(waitTime));
        
        // perform action and get burst time
        long long bt = performAction(idx, logFile);
        totalBT += bt;
        currentTime += bt;
        completed++;
        
        fprintf(logFile, "Action %d completed - BT: %.2f ms, Finish: %.2f ms\n\n",
            idx + 1, nsToMs(bt), nsToMs(currentTime));
        
        // add new arrivals to queue
        while (actionIndex < actionCount && actions[actionIndex].arrivalTime <= currentTime) {
            if (!processed[actionIndex]) {
                enqueue(actionIndex);
                processed[actionIndex] = 1;
            }
            actionIndex++;
        }
        
        // log queue after processing
        logQueueState(queueLog, currentTime);
    }
    
    // print statistics
    printf("\n========== SIMULATION COMPLETE ==========\n\n");
    fprintf(logFile, "\n========== SIMULATION COMPLETE ==========\n\n");
    
    double avgBT = (completed > 0) ? (double)totalBT / completed : 0;
    double avgWT = (completed > 0) ? (double)totalWT / completed : 0;
    
    // display in ms, store in ns
    printf("Total Actions: %d\n", completed);
    printf("Total Burst Time: %.2f ms (%lld ns)\n", nsToMs(totalBT), totalBT);
    printf("Total Waiting Time: %.2f ms (%lld ns)\n", nsToMs(totalWT), totalWT);
    printf("Average Burst Time: %.2f ms\n", nsToMs((long long)avgBT));
    printf("Average Waiting Time: %.2f ms\n", nsToMs((long long)avgWT));
    
    fprintf(logFile, "Total Actions: %d\n", completed);
    fprintf(logFile, "Total Burst Time: %.2f ms (%lld ns)\n", nsToMs(totalBT), totalBT);
    fprintf(logFile, "Total Waiting Time: %.2f ms (%lld ns)\n", nsToMs(totalWT), totalWT);
    fprintf(logFile, "Average Burst Time: %.2f ms\n", nsToMs((long long)avgBT));
    fprintf(logFile, "Average Waiting Time: %.2f ms\n", nsToMs((long long)avgWT));
};
