// stats.c
#include <math.h>
#include "item.h"

// Mean Absolute Percentage Error (MAPE) in %
double compute_mape(double *actual, double *forecast, int n) {
    if (n <= 0) return 0.0;

    double sum = 0.0;
    int i, count = 0;

    for (i = 0; i < n; i++) {
        if (actual[i] != 0) {
            sum += fabs((actual[i] - forecast[i]) / actual[i]) * 100.0;
            count++;
        }
    }
    if (count == 0) return 0.0;
    return sum / count;
}

// Standard deviation of sales (sample std dev)
double compute_stddev(double *sales, int n) {
    if (n <= 1) return 0.0;

    double sum = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        sum += sales[i];
    }
    double mean = sum / n;

    double var = 0.0;
    for (i = 0; i < n; i++) {
        double diff = sales[i] - mean;
        var += diff * diff;
    }
    var /= (n - 1);      // sample variance

    return sqrt(var);
}
