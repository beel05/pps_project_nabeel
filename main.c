// main.c
#include <stdio.h>   
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "item.h"

//start
int main(void) {
    Item item;
    int i;
    int window;
    int currentStock;

    printf("=== Inventory Forecasting Tool ===\n\n");

    // Get item name
    printf("Enter item name: ");
    fgets(item.name, sizeof(item.name), stdin);
    item.name[strcspn(item.name, "\n")] = '\0'; 
    // remove newline

    // Number of days of historical data
    printf("Enter number of days of historical sales data: ");
    scanf("%d", &item.days);

    if (item.days <= 0) {
        printf("Number of days must be positive.\n");
        return 0;
    }

    // Allocate memory for sales
    item.sales = (double *)malloc(item.days * sizeof(double));
    if (item.sales == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    // Input historical sales
    printf("Enter sales for each day:\n");
    for (i = 0; i < item.days; i++) {
        printf("Day %d: ", i + 1);
        scanf("%lf", &item.sales[i]);
    }

    // Lead time
    printf("Enter lead time (in days): ");
    scanf("%lf", &item.leadTime);

    // Current stock
    printf("Enter current stock level: ");
    scanf("%d", &currentStock);

    // Forecast window
    printf("Enter forecast window (n-day moving average): ");
    scanf("%d", &window);

    if (window <= 0 || window > item.days) {
        printf("Invalid window size. Using window = %d (all available data).\n", item.days);
        window = item.days;
    }

    // Compute forecasts for next period
    double maForecast = moving_average(item.sales, item.days, window);
    double wmaForecast = weighted_moving_average(item.sales, item.days, window);

    printf("\n=== Forecasts for next period (day %d+1) ===\n", item.days);
    printf("Simple %d-day Moving Average Forecast: %.2f\n", window, maForecast);
    printf("Weighted %d-day Moving Average Forecast: %.2f\n", window, wmaForecast);

    // OPTIONAL: Compare methods with MAPE over history (where possible)
    int histForecastCount = item.days - window;
    if (histForecastCount > 0) {
        double *maHistForecasts = (double *)malloc(histForecastCount * sizeof(double));
        double *wmaHistForecasts = (double *)malloc(histForecastCount * sizeof(double));

        if (maHistForecasts != NULL && wmaHistForecasts != NULL) {
            int t;
            for (t = window; t < item.days; t++) {
                maHistForecasts[t - window] = moving_average(item.sales, t, window);
                wmaHistForecasts[t - window] = weighted_moving_average(item.sales, t, window);
            }

            double mapeMA = compute_mape(&item.sales[window], maHistForecasts, histForecastCount);
            double mapeWMA = compute_mape(&item.sales[window], wmaHistForecasts, histForecastCount);

            printf("\n=== Method Comparison (MAPE over history) ===\n");
            printf("MA  MAPE: %.2f%%\n", mapeMA);
            printf("WMA MAPE: %.2f%%\n", mapeWMA);

            free(maHistForecasts);
            free(wmaHistForecasts);
        }
    }

    // Choose one forecast as primary (e.g., weighted MA)
    double forecast = wmaForecast;

    // Compute safety stock (simple approximation using demand variability)
    double sigma = compute_stddev(item.sales, item.days);
    double serviceFactor = 1.65; // ~95% service level
    double safetyStock = serviceFactor * sigma * sqrt(item.leadTime);

    // Compute reorder level: demand during lead time + safety stock
    double reorderLevel = forecast * item.leadTime + safetyStock;

    // Compute order quantity suggestion
    double orderQty = 0.0;
    if (currentStock < reorderLevel) {
        orderQty = reorderLevel - currentStock;
    }

    // Expected days until stock-out
    double daysUntilStockOut = 0.0;
    if (forecast > 0.0) {
        daysUntilStockOut = currentStock / forecast;
    }

    // Suggested reorder time (in days from now)
    double reorderIn = daysUntilStockOut - item.leadTime;
    if (reorderIn < 0) {
        reorderIn = 0; // reorder immediately
    }

    printf("\n=== Inventory Recommendations for item: %s ===\n", item.name);
    printf("Lead time (days): %.2f\n", item.leadTime);
    printf("Safety stock (approx): %.2f units\n", safetyStock);
    printf("Reorder level: %.2f units\n", reorderLevel);
    printf("Current stock: %d units\n", currentStock);
    printf("Suggested order quantity: %.0f units\n", ceil(orderQty));
    printf("Expected days until stock-out: %.1f days\n", daysUntilStockOut);
    printf("Suggested reorder time: in %.1f days (0 = reorder now)\n", reorderIn);

    // Clean up
    free(item.sales);

    printf("\n=== End of Forecast ===\n");
    return 0;
}



