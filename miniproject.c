#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct {
    double profit;
    double risk;
    double price;
    char name[20];
} Stock;

void knapsack(Stock stocks[], int n, double budget, int years, int num_stocks, char risk_type[]) {
    double total_investment = 0.0;
    double total_future_value = 0.0;
    double total_expected_return = 0.0;
    int selected_count = 0, i, j, year;
    double min_return = 0.0, max_return = 0.0;
    double budget_const=budget;
    // Determine the risk range
    if (strcmp(risk_type, "high") == 0) {
        min_return = 0.20;
        max_return = 0.40;
    } else if (strcmp(risk_type, "low") == 0) {
        min_return = 0.05;
        max_return = 0.15;
    } else if (strcmp(risk_type, "medium") == 0) {
        min_return = 0.15;
        max_return = 0.20;
    } else {
        printf("Invalid risk type. Use 'low', 'medium', or 'high'.\n");
        return;
    }

    // Sort stocks based on profit-to-risk ratio within the risk type range
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (stocks[j].profit >= min_return && stocks[j].profit <= max_return &&
                stocks[j + 1].profit >= min_return && stocks[j + 1].profit <= max_return) {
                double ratio1 = stocks[j].profit / stocks[j].risk;
                double ratio2 = stocks[j + 1].profit / stocks[j + 1].risk;
                if (ratio1 < ratio2) {
                    Stock temp = stocks[j];
                    stocks[j] = stocks[j + 1];
                    stocks[j + 1] = temp;
                }
            }
        }
    }

    printf("\nSelected Stocks:\n");
    for (i = 0; i < n && selected_count < num_stocks; i++) {
        if (stocks[i].profit >= min_return && stocks[i].profit <= max_return) {
            if (budget >= stocks[i].price) {
                budget -= stocks[i].price;
                total_investment += stocks[i].price;
                double future_value = stocks[i].price * pow(1 + stocks[i].profit, years);
                total_future_value += future_value;
                total_expected_return += stocks[i].profit;
                printf("Stock: %s, Price: %.2f, Expected Return: %.2f%%, Risk: %.2f%%\n", 
                       stocks[i].name, stocks[i].price, stocks[i].profit * 100, stocks[i].risk * 100);
                selected_count++;
            } else {
                double fraction = budget / stocks[i].price;
                double future_value = stocks[i].price * fraction * pow(1 + stocks[i].profit, years);
                total_future_value += future_value;
                total_investment += stocks[i].price * fraction;
                total_expected_return += stocks[i].profit * fraction;
                printf("Stock: %s (Fraction), Price: %.2f, Expected Return: %.2f%%, Risk: %.2f%%\n", 
                       stocks[i].name, stocks[i].price * fraction, stocks[i].profit * 100, stocks[i].risk * 100);
                budget = 0;
                selected_count++;
            }
        }
    }
    // Calculate average expected return as the average CAGR of selected companies
    double avg_expected_return = (selected_count > 0) ? (total_expected_return / selected_count) : 0;

    printf("\nTotal Investment: %.2f\n", budget_const);
    printf("Average Expected Return: %.2f%%\n", avg_expected_return * 100);

    // Calculate the expected amount for each year
    printf("\nYearly Expected Amounts:\n");
    for (year = 1; year <= years; year++) {
        double expected_amount = total_investment * pow(1 + avg_expected_return, year);

        double final = (budget_const*expected_amount)/total_investment	;

        printf("Year %d: %.2f\n", year, final);
    }
}

int main() {
    int n = 40;
    Stock stocks[] = {
        {0.12, 0.20, 200, "TCS"},
        {0.15, 0.30, 500, "Reliance"},
        {0.10, 0.25, 300, "HDFC"},
        {0.08, 0.15, 150, "ICICI"},
        {0.14, 0.22, 400, "Infosys"},
        {0.11, 0.18, 250, "SBI"},
        {0.13, 0.28, 350, "Wipro"},
        {0.16, 0.35, 600, "HCL"},
        {0.09, 0.21, 180, "Axis"},
        {0.07, 0.17, 120, "Maruti"},
        {0.13, 0.22, 350, "Bajaj"},
        {0.14, 0.25, 420, "L&T"},
        {0.10, 0.18, 220, "Adani"},
        {0.12, 0.20, 300, "Bharti"},
        {0.15, 0.30, 550, "ITC"},
        {0.11, 0.24, 280, "Hindalco"},
        {0.09, 0.27, 310, "Tech Mahindra"},
        {0.14, 0.31, 640, "Power Grid"},
        {0.08, 0.20, 150, "ONGC"},
        {0.13, 0.19, 280, "Hero MotoCorp"},
        {0.22, 0.35, 750, "Tesla"},
        {0.25, 0.40, 800, "Amazon"},
        {0.20, 0.30, 700, "Netflix"},
        {0.23, 0.38, 720, "Alphabet"},
        {0.18, 0.25, 680, "Facebook"},
        {0.21, 0.32, 740, "Microsoft"},
        {0.19, 0.29, 690, "Apple"},
        {0.24, 0.37, 760, "NVIDIA"},
        {0.26, 0.42, 820, "AMD"},
        {0.17, 0.23, 660, "Intel"},
        {0.27, 0.45, 850, "Qualcomm"},
        {0.28, 0.47, 870, "Samsung"},
        {0.16, 0.22, 640, "Cisco"},
        {0.29, 0.48, 890, "Sony"},
        {0.15, 0.20, 620, "Panasonic"},
        {0.20, 0.33, 700, "Oracle"},
        {0.18, 0.28, 680, "SAP"},
        {0.21, 0.36, 740, "Salesforce"},
        {0.19, 0.31, 690, "IBM"},
        {0.17, 0.26, 660, "Dell"}
    };

    double budget;
    int years, num_stocks;
    char risk_type[10];

    printf("Enter your investment amount: ");
    scanf("%lf", &budget);

    printf("Enter number of years: ");
    scanf("%d", &years);

    printf("Enter number of stocks needed in your portfolio: ");
    scanf("%d", &num_stocks);

    printf("Enter risk type (low, medium, high): ");
    scanf("%s", risk_type);

    knapsack(stocks, n, budget, years, num_stocks, risk_type);

    return 0;
}
