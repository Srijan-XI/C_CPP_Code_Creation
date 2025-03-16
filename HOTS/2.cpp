#include <iostream>
#include <algorithm>
using namespace std;

int knapsack(int capacity, int weights[], int values[], int n) {
    int dp[n + 1][capacity + 1];

    for(int i = 0; i <= n; i++) {
        for(int w = 0; w <= capacity; w++) {
            if(i == 0 || w == 0)
                dp[i][w] = 0;
            else if(weights[i-1] <= w)
                dp[i][w] = max(values[i-1] + dp[i-1][w-weights[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][capacity];
}

int main() {
    int n, capacity;
    
    cout << "Enter number of items: ";
    cin >> n;
    
    int values[n], weights[n];
    
    cout << "Enter values and weights:\n";
    for(int i = 0; i < n; i++) {
        cin >> values[i] >> weights[i];
    }
    
    cout << "Enter knapsack capacity: ";
    cin >> capacity;
    
    cout << "Maximum value: " << knapsack(capacity, weights, values, n);
    return 0;
}
