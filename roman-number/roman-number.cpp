#include <iostream>
#include <string>
using namespace std;

string intToRoman(int num) {

    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    string roman = "";
    for (int i = 0; i < 13; ++i) {
        while (num >= values[i]) {
            num -= values[i];
            roman += symbols[i];
        }
    }
    return roman;
}

int main() {
    int number;
    cout << "Enter a number: ";
    cin >> number;

    if (number <= 0 || number > 9999) {
        cout << "Number out of range. Please enter a number between 1 and 3999." << endl;
    } else {
        cout << "Roman numeral: " << intToRoman(number) << endl;
    }

    return 0;
}
