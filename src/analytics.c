#include "analytics.h"
#include <stdio.h>
#include <string.h>

static double totalWait = 0;
static double totalTurnaround = 0;
static int count = 0;

#ifdef _WIN32
static LARGE_INTEGER perfFreq;
static int freqInit = 0;

// helper: diff two LARGE_INTEGER counters in ms
static double diffMs(LARGE_INTEGER start, LARGE_INTEGER end)
{
    if (!freqInit) {
        QueryPerformanceFrequency(&perfFreq);
        freqInit = 1;
    }
    return (double)(end.QuadPart - start.QuadPart) * 1000.0 / (double)perfFreq.QuadPart;
}
#else
// helper: diff two timespecs in ms
static double diffMs(struct timespec start, struct timespec end)
{
    double s = (double)(end.tv_sec - start.tv_sec) * 1000.0;
    double ns = (double)(end.tv_nsec - start.tv_nsec) / 1e6;
    return s + ns;
}
#endif

void recordMetrics(Request r)
{
    double wait = diffMs(r.arrival, r.start);
    double turnaround = diffMs(r.arrival, r.finish);
    totalWait += wait;
    totalTurnaround += turnaround;
    count++;
}

void printMetrics(void)
{
    if (count == 0) { printf("No requests processed.\n"); return; }
    printf("Requests: %d\n", count);
    printf("Avg wait time: %.2f ms\n", totalWait / count);
    printf("Avg turnaround: %.2f ms\n", totalTurnaround / count);
    printf("Throughput: %.2f req/s\n", count / (totalTurnaround / 1000.0));
}

void exportCSV(const char *path)
{
    FILE *fp = fopen(path, "a");
    if (!fp) return;
    if (count == 0) { fclose(fp); return; }
    fprintf(fp, "%d,%.2f,%.2f,%.2f\n",
            count,
            totalWait / count,
            totalTurnaround / count,
            count / (totalTurnaround / 1000.0));
    fclose(fp);
}

void resetMetrics(void)
{
    totalWait = 0;
    totalTurnaround = 0;
    count = 0;
}
