#include <iostream>

using namespace std;

int main() {
    float costPrice,sellingPrice;

    cout << "Enter the cost price: ";
    cin >> costPrice;
    cout << "Enter the selling price: ";
    cin >> sellingPrice;

    if (sellingPrice > costPrice) {
        float profit = sellingPrice - costPrice;
        float profitPercentage = (profit / costPrice) * 100;
        cout << "Profit: " << profit << endl;
        cout << "Profit Percentage: " << profitPercentage << "%" << endl;
    }
    else if (sellingPrice < costPrice) {
        float loss = costPrice - sellingPrice;
        float lossPercentage = (loss / costPrice) * 100;
        cout << "Loss: " << loss << endl;
        cout << "Loss Percentage: " << lossPercentage << "%" << endl;
    }
    else {
        cout << "Net Zero" << endl;
    }


}
