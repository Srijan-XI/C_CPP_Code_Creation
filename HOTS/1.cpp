#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int profit;
    float ratio;
};

void calculateRatio(vector<Item>& items) {
    for (auto& item : items) {
        item.ratio = static_cast<float>(item.profit) / item.weight;
    }
}

void sortItems(vector<Item>& items) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });
}

float solveFractionalKnapsack(vector<Item>& items, int capacity) {
    float totalProfit = 0.0f;

    for (auto& item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            totalProfit += item.profit;
        } else {
            float fraction = static_cast<float>(capacity) / item.weight;
            totalProfit += item.profit * fraction;
            break;
        }
    }

    return totalProfit;
}

int main() {
    int n = 3;
    int capacity = 60;

    vector<Item> items = {
        {10, 100, 0.0f},
        {40, 280, 0.0f},
        {20, 120, 0.0f}
    };

    calculateRatio(items);
    sortItems(items);

    float totalProfit = solveFractionalKnapsack(items, capacity);

    cout << "Total Profit: " << totalProfit << endl;

    return 0;
}
