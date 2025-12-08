// action.h - Simulation action definitions
#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>

#define MAX_ACTIONS 5000
#define TIME_MS_TO_NS 100000LL // .1 ms in ns

// action types
#define ACTION_APPROVE  1
#define ACTION_RETURN   2
#define ACTION_ISSUE    3
#define ACTION_REQUEST  4

// action structure
typedef struct Action {
    long long arrivalTime;  // AT in nanoseconds
    int type;               // 1-4 action type
} Action;

// action array
extern Action actions[MAX_ACTIONS];
extern int actionCount;

// action functions (action.c)
long long performAction(int index, FILE *logFile);
const char* getActionTypeName(int type);

// generator functions (generator.c)
int getRandomInt(int min, int max);
int getRandomBool(void);
void generateActions(long long timeLimit, int minTimeMs, int maxTimeMs, int maxRepeats);

// simulator functions (simulator.c)
void runSimulator(FILE *logFile, FILE *queueLog);

#endif
