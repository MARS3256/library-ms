// generator.c - Random action generator
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "action.h"

Action actions[MAX_ACTIONS];
int actionCount = 0;

// get random int in range [min, max]
int getRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

// get random bool (0 or 1)
int getRandomBool(void) {
    return rand() % 2;
}

// generate list of actions with arrival times in ns
// minTimeMs/maxTimeMs: interval range in ms between arrivals
// maxRepeats: max actions at same arrival time
void generateActions(long long timeLimit, int minTimeMs, int maxTimeMs, int maxRepeats) {
    srand((unsigned int)time(NULL));
    actionCount = 0;
    
    long long currentTime = 0;
    
    while (currentTime < timeLimit && actionCount < MAX_ACTIONS - 5) {
        // random repeats at same arrival time
        int repeats = getRandomInt(1, maxRepeats);
        
        for (int i = 0; i < repeats && actionCount < MAX_ACTIONS; i++) {
            actions[actionCount].arrivalTime = currentTime;
            actions[actionCount].type = getRandomInt(1, 4);
            actionCount++;
        }
        
        // advance time by minTime-maxTime ms (converted to ns)
        currentTime += (long long)getRandomInt(minTimeMs, maxTimeMs) * TIME_MS_TO_NS;
    }
    
    printf("Generated %d actions (time range: 0-%.2f ms)\n", 
        actionCount, (double)timeLimit / 1000000.0);
}
