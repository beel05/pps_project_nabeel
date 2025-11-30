// forecast.c
#include "item.h" //header file
 //logic 
//========================================================================================
//Function: moving_average                                                               *
//Purpose: Computes the simple moving average for the last "window" days                 *
//sales[] -> array of sales data                                                         *
//n       -> total number of days (size of array)                                        *
//  window -> number of days to include in the average                                   *
//Returns :                                                                              *
//  The average of the last 'window' number of sales values                              *
//Notes  :                                                                               *
//If window > n or window <= 0, function returns 0.                                      *
//=========================================================================================
double moving_average(double *sales, int n, int window) {
    if (window <= 0 || window > n) return 0.0;

    double sum = 0.0;
    int i;
    for (i = n - window; i < n; i++) {
        sum += sales[i];
    }
    return sum / window;
}

//Weighted moving average: weights 1,2,....,window(most recent has max weight)
double weighted_moving_average(double *sales, int n, int window) {
 if (window <= 0 || window > n) return 0.0;

 double weightedSum = 0.0;
 double weightTotal = 0.0;
 int i;
 int w = 1;
 
for (i = n - window; i < n; i++) {
    weightedSum += w * sales[i];
    weightTotal += w;
    w++;
    }
    return weightedSum / weightTotal;
}












