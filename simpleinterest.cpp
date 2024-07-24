// Calculate Simple Interest
#include <iostream>
using namespace std;

int main() {
    double principal, rate, time, simpleInterest;

    cout << "Enter the principal amount: ";
    cin >> principal;

    cout << "Enter the rate of interest per year (in %): ";
    cin >> rate;

    cout << "Enter the time (in years): ";
    cin >> time;

    simpleInterest = (principal * rate * time) / 100;

    cout << "The simple interest is: " << simpleInterest << endl;
}
