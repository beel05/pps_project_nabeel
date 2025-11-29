// forecast.c
#include "item.h"
 //logic

//Computer moving average over the last "Window" days from the first n days
double moving_average(double *sales, int n, int window) {
    if (window <= 0 || window > n) return 0.0;

    double sum = 0.0;
    int i;
    for (i = n - window; i < n; i++) {
        sum += sales[i];
    }
    return sum / window;
}

// Weighted moving average: weights 1,2,...,window (most recent has max weight)
double weighted_moving_average(double *sales, int n, int window) {
    if (window <= 0 || window > n) return 0.0;

    double weightedSum = 0.0;
    double weightTotal = 0.0;
    int i;
    int w = 1;

for (i = n - window; i< n; i++) {
    weightedSum += w * sales[i];
    weightTotal += w;
    w++;
    }
    return weightedSum / weightTotal;
}



