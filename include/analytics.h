#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "scheduler.h"

// record completed request metrics
void recordMetrics(Request r);

// print summary to stdout
void printMetrics(void);

// export CSV for graphing
void exportCSV(const char *path);

// reset counters between runs
void resetMetrics(void);

#endif // ANALYTICS_H
