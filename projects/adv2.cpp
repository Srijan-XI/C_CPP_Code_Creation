#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Converter {
public:
    int binaryToDecimal(long long binary);
    long long decimalToBinary(int decimal);
    long long decimalToOctal(int decimal);
    int hexToDecimal(const string& hex);
    string decimalToHex(int decimal);
    int octalToDecimal(long long octal);
};

class Calculator {
public:
    float add(float a, float b);
    float subtract(float a, float b);
    float multiply(float a, float b);
    float divide(float a, float b);
};

int main() {
    int mainChoice;
    Converter converter;
    Calculator calculator;

    cout << "Main Menu:\n1. Calculator\n2. Number Conversion\nEnter your choice: ";
    cin >> mainChoice;

    if (mainChoice == 1) {
        int calcChoice;
        float num1, num2;

        cout << "\nCalculator Menu:\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\nEnter your choice: ";
        cin >> calcChoice;

        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter second number: ";
        cin >> num2;

        switch (calcChoice) {
            case 1: cout << "Result: " << calculator.add(num1, num2) << endl; break;
            case 2: cout << "Result: " << calculator.subtract(num1, num2) << endl; break;
            case 3: cout << "Result: " << calculator.multiply(num1, num2) << endl; break;
            case 4:
                if (num2 != 0) {
                    cout << "Result: " << calculator.divide(num1, num2) << endl;
                } else {
                    cout << "Error: Division by zero!" << endl;
                }
                break;
            default: cout << "Invalid choice!" << endl;
        }
    } else if (mainChoice == 2) {
        int convChoice;
        cout << "\nNumber Conversion Menu:\n1. Binary to Decimal\n2. Decimal to Binary\n3. Decimal to Octal\n4. Hexadecimal to Decimal\n5. Octal to Decimal\n6. Decimal to Hexadecimal\nEnter your choice: ";
        cin >> convChoice;

        switch (convChoice) {
            case 1: {
                long long binary;
                cout << "Enter a binary number: ";
                cin >> binary;
                cout << binary << " in binary = " << converter.binaryToDecimal(binary) << " in decimal" << endl;
                break;
            }
            case 2: {
                int decimal;
                cout << "Enter a decimal number: ";
                cin >> decimal;
                cout << decimal << " in decimal = " << converter.decimalToBinary(decimal) << " in binary" << endl;
                break;
            }
            case 3: {
                int decimal;
                cout << "Enter a decimal number: ";
                cin >> decimal;
                cout << decimal << " in decimal = " << converter.decimalToOctal(decimal) << " in octal" << endl;
                break;
            }
            case 4: {
                string hexNumber;
                cout << "Enter a hexadecimal number: ";
                cin >> hexNumber;
                cout << hexNumber << " in hexadecimal = " << converter.hexToDecimal(hexNumber) << " in decimal" << endl;
                break;
            }
            case 5: {
                long long octal;
                cout << "Enter an octal number: ";
                cin >> octal;
                cout << octal << " in octal = " << converter.octalToDecimal(octal) << " in decimal" << endl;
                break;
            }
            case 6: {
                int decimal;
                cout << "Enter a decimal number: ";
                cin >> decimal;
                cout << decimal << " in decimal = " << converter.decimalToHex(decimal) << " in hexadecimal" << endl;
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

int Converter::binaryToDecimal(long long binary) {
    int decimal = 0, base = 1;

    while (binary > 0) {
        int lastDigit = binary % 10; 
        binary /= 10; 
        decimal += lastDigit * base; 
        base *= 2; 
    }

    return decimal; 
}

long long Converter::decimalToBinary(int decimal) {
    long long binary = 0, base = 1;

    while (decimal > 0) { 
        int remainder = decimal % 2; 
        decimal /= 2; 
        binary += remainder * base; 
        base *= 10; 
    }

    return binary; 
}

long long Converter::decimalToOctal(int decimal) {
    long long octal = 0, base = 1;

    while (decimal > 0) { 
        int remainder = decimal % 8; 
        decimal /= 8; 
        octal += remainder * base; 
        base *= 10; 
    }

    return octal; 
}

int Converter::hexToDecimal(const string& hex) {
    int dec = 0;

    for (size_t i = 0; i < hex.length(); ++i) { 
        char c = toupper(hex[hex.length() - i - 1]);
        
        if (isdigit(c)) { 
            dec += (c - '0') * pow(16, i); 
        } else if (isalpha(c)) { 
            dec += (c - 'A' + 10) * pow(16, i); 
        }
    }

    return dec; 
}

int Converter::octalToDecimal(long long octal) {
    int dec = 0, base = 1;

    while (octal > 0) {
        int lastDigit = octal % 10; 
        octal /= 10; 
        dec += lastDigit * base; 
        base *= 8; 
    }

    return dec; 
}

string Converter::decimalToHex(int decimal) {
    if (decimal == 0)
        return "0";

    string hexValue;

    while (decimal > 0) {
        int remainder = decimal % 16;

        if (remainder < 10)
            hexValue += (remainder + '0');
        else
            hexValue += (remainder - 10 + 'A');

        decimal /= 16; 
    }

    reverse(hexValue.begin(), hexValue.end());
    
    return hexValue; 
}

float Calculator::add(float a, float b) { return a + b; }

float Calculator::subtract(float a, float b) { return a - b; }

float Calculator::multiply(float a, float b) { return a * b; }

float Calculator::divide(float a, float b) { return a / b; }
