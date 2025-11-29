// item.h
#ifndef ITEM_H
#define ITEM_H

typedef struct {
    char name[50];//intialising 
    int days;    
    double *sales;      
double leadTime;    
} Item;


double moving_average(double *sales, int n, int window);
double weighted_moving_average(double *sales, int n, int window);


double compute_mape(double *actual, double *forecast, int n);
double compute_stddev(double *sales,int n);

#endif




