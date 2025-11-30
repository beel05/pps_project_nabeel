000000000000// forecast.c
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



for (i = n - window; i < n; i++) {
    weightedSum += w * sales[i];
    weightTotal += w;
    w++;
    }
    return weightedSum / weightTotal;
}





