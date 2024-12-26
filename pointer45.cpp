#include <iostream>

using namespace std;

int main() {
    // Declaring pointers to different data types
    int *ptrInt;
    double *ptrDouble;
    char *ptrChar;

    // Dynamic memory allocation
    ptrInt = new int;
    ptrDouble = new double;
    ptrChar = new char;

    // Assigning values to pointers
    *ptrInt = 42;
    *ptrDouble = 3.14;
    *ptrChar = 'A';

    // Dereferencing pointers to access values
    cout << "Value of ptrInt: " << *ptrInt << endl;
    cout << "Value of ptrDouble: " << *ptrDouble << endl;
    cout << "Value of ptrChar: " << *ptrChar << endl;

    // Pointer arithmetic
    int arr[] = {1, 2, 3, 4, 5};
    int *ptrArr = arr;

    cout << "First element of array: " << *ptrArr << endl;
    ptrArr++;
    cout << "Second element of array: " << *ptrArr << endl;

    // Pointer comparison
    if (ptrInt == ptrDouble) {
        cout << "ptrInt and ptrDouble point to the same memory location." << endl;
    } else {
        cout << "ptrInt and ptrDouble point to different memory locations." << endl;
    }

    // Function pointers
    int (*funcPtr)(int, int);
    funcPtr = add; // Assuming add is a function that takes two integers and returns their sum

    int result = funcPtr(3, 5);
    cout << "Result of function call: " << result << endl;

    // Array of pointers
    int *arrPtrs[3];
    for (int i = 0; i < 3; i++) {
        arrPtrs[i] = new int;
        *arrPtrs[i] = i * 10;
    }

    for (int i = 0; i < 3; i++) {
        cout << "Value of arrPtrs[" << i << "]: " << *arrPtrs[i] << endl;
    }

    // Deallocating dynamically allocated memory
    delete ptrInt;
    delete ptrDouble;
    delete ptrChar;

    for (int i = 0; i < 3; i++) {
        delete arrPtrs[i];
    }

    return 0;
}